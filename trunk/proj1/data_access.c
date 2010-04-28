#include <stdio.h>
#include <stdlib.h>
#include "data_access.h"

int da_str_to_filme (filme *f_ret, int *tam_reg, char *f_str) {
  /* Entrada: string crua lida do arquivo, a partir do início de um registro */
  /* Saída: - setup da struct filme passada por referência 
     - tamanho do registro no arquivo
     - valor numérico para erros */
	

  /* Formato do registro no arquivo */
  /* Como há atributos de texto, é difícil manter os registros com tamanho constante no arq */
  /* Assim, uma ideia é usar separadores entre os atributos, assim como manter o tamanho do registro */
  /* 
     int tam_total_do_reg (incluindo todos os separadores do registro)
     int id, int avaliacoes, float media [TAMANHO FIXO NO ARQUIVO!], string titulo, string sinopse, 
     string sala, string horarios.
     Separador: @
     Ex: 75@1@0@0@Rei Leão@Filme assim assim assado@Kinoplex - sala 10@12h40, 15h, 17h20@
     (contando tudo, incluindo os caracteres de tam_total_do_reg e os separadores)

     Esse esquema do número de caracteres num campo é pra possibilitar a busca entre os registros.
  */

  char str[TAM_MAX_ATR]; /* string fixa bem grande pra comportar qq atributo */

  int i = 0; /* índice de acesso de f_str */
  int j = 0; /* indice para montagem da string  */

  /* tamanho do registro */
  while(f_str[i]!='@') {
    str[j] = f_str[i];
    i++; j++;
  }
  str[j] = '\0';
  *tam_reg = atoi(str);

  /* id */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; }
  str[j] = '\0'; 
  f_ret->id = atoi(str);

  /* numero de avaliações */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; }
  str[j] = '\0';
  f_ret->n_aval = atoi(str);
	
  /* média */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; }
  str[j] = '\0';
  f_ret->media = atof(str);
	
  /* titulo */
  i++; j = 0;
  while(f_str[i]!='@') {
    str[j] = f_str[i];
    i++; j++;
  }
  str[j] = '\0';
  /* aloca a string dinamicamente */
  f_ret->titulo = (char *)malloc((j+1)*sizeof(char));
  sprintf(f_ret->titulo, "%s", str);

  /* Blocos de código similares ao de cima, só que comprimidos  */
  /* sinopse */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i];	i++; j++;	} str[j] = '\0';
  f_ret->sinopse = (char *)malloc((j+1)*sizeof(char));
  sprintf(f_ret->sinopse, "%s", str);

  /* sala */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; } str[j] = '\0';
  f_ret->sala = (char *) malloc((j+1)*sizeof(char));
  sprintf(f_ret->sala, "%s", str);

  /* horarios */
  i++; j = 0;
  while(f_str[i]!='@' && f_str[i]!='\0') { str[j] = f_str[i]; i++; j++; } str[j] = '\0';
  f_ret->horarios = (char *) malloc((j+1)*sizeof(char));
  sprintf(f_ret->horarios, "%s", str);

  /* next - lembra dele? :) */
  f_ret->prox_filme = NULL;

  return(0);
}


void da_print_full_info(filme *f) {
  printf("Id: %d\n", f->id);
  printf("Titulo: %s\n", f->titulo);
  printf("Sinopse: %s\n", f->sinopse);
  printf("Sala: %s\n", f->sala);
  printf("Horários: %s\n", f->horarios);
  printf("Média: %3.2f (%d avaliações)\n", f->media, f->n_aval);
  return;
}

void da_print_partial_info(filme *f) {
  printf("Id: %d\n", f->id);
  printf("Titulo: %s\n", f->titulo);
  return;
}


void da_free_strs(filme *f) {
  free(f->titulo);
  free(f->sinopse);
  free(f->sala);
  free(f->horarios);
  return;
}


int da_free_all(filme *f) {
  /* Esta função desaloca todos os filmes que estiverem na lista, e
     retorna o número desses filmes que foram desalocados.
     A lista precisa ser resolvida de trás pra frente, por isso 
     está sendo usada recursão. */

  int i;

  da_free_strs(f);

  /* Condição de parada (último filme) */
  if(f->prox_filme == NULL) {
    free(f);
    return(0); /* retorna, inicializando contador */
  }

  /* Chamada recursiva */
  i = da_free_all((filme *)f->prox_filme); /* cast pro -Wall n reclamar */

  /* Resolvida a recursão, libera a struct e retorna */
  free(f);
  return(i);

}
	



/* Função a ser chamada pelo SERVIDOR! */
int da_get_filme_by_id(filme **f_ret, int id) {

  /* Função responsável por acessar o arquivo dos registros,
     buscar o filme com o id igual ao passado como argumento,
     e retornar o resultado da busca
     Saídas: 0 *f_ret aponta p/ o filme encontrado
     1 - código de retorno que indica que nada foi encontrado
  */

  int tam_reg, id_reg;
  long int cursor = 0; /* indice de leitura do arquivo */
  char buffer[TAM_MAX_REG]; /* 1kB */
  FILE *arq;

  arq = fopen("filmes.dat", "r");

  while(fscanf(arq, "%d@%d@", &tam_reg, &id_reg) != EOF) {
    /* registro encontrado */
    if(id_reg == id) {
      /* aloca a estrutura para guardar o filme */
			*f_ret = (filme *)malloc(sizeof(filme));
      /* caminha no arquivo até o inicio do registro */
      fseek(arq, cursor, SEEK_SET);
      fgets(buffer, TAM_MAX_REG, arq);
      da_str_to_filme(*f_ret, &tam_reg, buffer);
      fclose(arq);
      return(0);
    } else {
      cursor += tam_reg;
      fseek(arq, cursor, SEEK_SET);
    }
  } /* só vai sair do while se não encontrar o filme */

  fclose(arq);
  
  return(1);

}


/* Função a ser chamada pelo SERVIDOR! */
int da_get_todos_filmes(filme **filmes_ret) {
  /* Esta função lê o arquivo, instancia uma struct filme para cada registro,
     concatena as structs, e retorna o resultado para o usuário.
     O valor de retorno é um inteiro que representa ou o número de registros lidos,
     ou -1 para erro.
  */

  FILE *arq;
  int tam_reg, i = 0;
  long int cursor = 0; /* indice de leitura do arquivo */
  char buffer[TAM_MAX_REG]; /* 1kB */
  filme *f; /* apontador principal que vai guardar cada um dos registros */

  arq = fopen("filmes.dat", "r");


  /* Enquanto houver registros no arquivo */
  while(fscanf(arq, "%d@", &tam_reg) != EOF) {
    /* Para cada registro, aloca a memória para a struct, seta o registro
     a partir da string lida, seta o cursor do arquivo p/ o próximo */
    i++;
    f = (filme *)malloc(sizeof(filme));
    if(i == 1) {
      /* Início da lista (primeiro registro) */
      *filmes_ret = f;
    }

    fseek(arq, cursor, SEEK_SET); /* pula p/ o inicio do registro */
    fgets(buffer, TAM_MAX_REG, arq); /* lê a string crua no buffer */
    da_str_to_filme(f, &tam_reg, buffer); /* abriga o filme na struct */

    cursor += tam_reg; /* ajuste para a leitura do próximo reg no arq */

    f = (filme *)f->prox_filme; /* atualiza o apontador */
  }

  f = NULL; /* último registro da lista */
  
  fclose(arq);
  
  return(i);
}


/* Retorna o número de filmes no arquivo */
int da_get_n_filmes() {

  FILE *arq;
  int tam_reg, i = 0;
  long int cursor = 0; /* indice de leitura do arquivo */

  arq = fopen("filmes.dat", "r");

  /* Enquanto houver registros no arquivo */
  while(fscanf(arq, "%d@", &tam_reg) != EOF) {
    i++;
    fseek(arq, cursor, SEEK_SET); /* pula p/ o inicio do registro */
    cursor += tam_reg; /* ajuste para a leitura do próximo reg no arq */
  }
  
  fclose(arq);
  
  return(i-1);
	
}

/* Retorna uma matriz com os registros todos em formato string pura */
void da_get_raw_strings (char **registros, int *tam_registros, int n_registros) {
	/* registros já é um vetor de apontadores pra strings, 
	 cujo tamanho é o número de registros no arquivo. */
  FILE *arq;
  int tam_reg, i = 0;
  long int cursor = 0; /* indice de leitura do arquivo */

  arq = fopen("filmes.dat", "r");

  /* Enquanto houver registros no arquivo */
  while(fscanf(arq, "%d@", &tam_reg) != EOF) {
    /* Para cada registro, aloca e seta a string */
    registros[i] = (char *)malloc((tam_reg+1) * sizeof(char));
    fseek(arq, cursor, SEEK_SET); /* volta p/ o inicio do registro */
    fgets(registros[i], tam_reg, arq); /* lê a string crua */

    tam_registros[i] = tam_reg; /* seta também os tamanhos dos registros */

    cursor += tam_reg; /* ajuste para a leitura do próximo reg */
		
    i++;
  }
  
  fclose(arq);
  
  return;
}
