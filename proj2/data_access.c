#include <stdio.h>
#include <stdlib.h>
#include "data_access.h"

/* Retorna o i-ésimo filme do arquivo */
void da_get_raw_str (int index, char *f_str) {
  
  FILE *arq;
  int tam_reg, i = 0;
  long int cursor = 0; /* indice de leitura do arquivo */

  arq = fopen("filmes.dat", "r");

  /* Enquanto houver registros no arquivo */
  while(fscanf(arq, "%d@", &tam_reg) != EOF) {
    i++;
    fseek(arq, cursor, SEEK_SET); /* pula p/ o inicio do registro */

    /* caso seja o filme procurado, seta a string de retorno */
    if (i == index) {
      fgets(f_str, tam_reg, arq);
      break;
    }

    /* ajuste para a leitura do próximo reg no arq */
    cursor += tam_reg; 
  }
  
  fclose(arq);
  
  return;
}

/* Faz um parse da string lida do arquivo para um filme */
int da_str_to_filme (filme *f_ret, int *tam_reg, char *f_str) {
  /* Entrada: string crua de um filme lida do arquivo */
  /* Saída:
     - setup da struct filme passada por referência 
     - tamanho do registro no arquivo
     - valor numérico para erros */

  /* Formato do registro no arquivo */
  /* Como há atributos de texto, é difícil manter os registros 
     com tamanho constante no arq. Assim, uma ideia é usar 
     separadores entre os atributos */

  /* [tam][id][aval][media][tit][sinopse][sala][horarios]
     int tam_total_do_reg (incluindo todos os separadores), 
     int id, int avaliacoes, float media [TAMANHO FIXO NO ARQUIVO!], 
     string titulo, string sinopse, string sala, string horarios.
     Separador: @
  */

  char str[TAM_MAX_ATR]; /* comporta qq atributo */

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

  /* Blocos de código similares ao de cima, comprimidos */
  /* sinopse */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; } 
  str[j] = '\0'; 
  f_ret->sinopse = (char *)malloc((j+1)*sizeof(char));
  sprintf(f_ret->sinopse, "%s", str);

  /* sala */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; }
  str[j] = '\0';
  f_ret->sala = (char *) malloc((j+1)*sizeof(char));
  sprintf(f_ret->sala, "%s", str);

  /* horarios */
  i++; j = 0;
  while(f_str[i]!='@' && f_str[i]!='\0') { 
    str[j] = f_str[i]; i++; j++; 
  } 
  str[j] = '\0';
  f_ret->horarios = (char *) malloc((j+1)*sizeof(char));
  sprintf(f_ret->horarios, "%s", str);

  /* next - lembra dele? :) */
  f_ret->prox_filme = NULL;

  return(0);
}


/* Imprime as informações já formatadas de um filme */
void da_print_full_info(filme *f) {
  printf("Id: %d\n", f->id);
  printf("Titulo: %s\n", f->titulo);
  printf("Sinopse: %s\n", f->sinopse);
  printf("Sala: %s\n", f->sala);
  printf("Horários: %s\n", f->horarios);
  printf("Média: %06.2f (%d avaliações)\n", 
	 f->media, f->n_aval);
  return;
}

/* Imprime as informações já formatadas de um filme */
void da_print_partial_info(filme *f) {
  printf("Id: %d\n", f->id);
  printf("Titulo: %s\n", f->titulo);
  return;
}


/* Libera as strings alocadas dinamicamente */
void da_free_strs(filme *f) {
  free(f->titulo);
  free(f->sinopse);
  free(f->sala);
  free(f->horarios);
  return;
}


int da_free_all(filme *f) {
  /* Esta função desaloca todos os filmes que estiverem na 
     lista, e retorna o número desses filmes que foram desa-
     locados. A lista precisa ser resolvida de trás pra 
     frente, por isso está sendo usada recursão. */

  int i;

  da_free_strs(f);

  /* Condição de parada (último filme) */
  if(f->prox_filme == NULL) {
    free(f);
    return(0); /* retorna, inicializando contador */
  }

  /* Chamada recursiva */
  /* cast pro -Wall n reclamar */
  i = da_free_all((filme *)f->prox_filme);

  /* Resolvida a recursão, libera a struct e retorna */
  free(f);
  return(i);
}
	

/* Função que retorna um filme a partir de um id */
int da_get_filme_by_id(char *f_str, int id, int *tamanho) {

  /* Função responsável por acessar o arquivo dos registros,
     buscar o filme com o id igual ao passado como argumento,
     e retornar o resultado da busca
     Saídas: 0 - filme encontrado (setado em f_str)
     1 - código de retorno que indica que nada foi encontrado
  */

  int tam_reg, id_reg;
  long int cursor = 0; /* indice de leitura do arquivo */
  FILE *arq;

  arq = fopen("filmes.dat", "r");

  while(fscanf(arq, "%d@%d@", &tam_reg, &id_reg) != EOF) {
    /* registro encontrado */
    if(id_reg == id) {
      /* caminha no arquivo até o inicio do registro */
      fseek(arq, cursor, SEEK_SET);
      fgets(f_str, tam_reg, arq);
      *tamanho = tam_reg;
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


/* Retorna o número de filmes no arquivo */
int da_get_n_filmes() {

  FILE *arq;
  int tam_reg, i = 0;
  long int cursor = 0; /* indice de leitura do arquivo */

  arq = fopen("filmes.dat", "r");

  /* Enquanto houver registros no arquivo */
  while(fscanf(arq, "%d@", &tam_reg) != EOF) {
    i++;
    /* pula p/ o inicio do registro */
    fseek(arq, cursor, SEEK_SET); 

    /* ajuste para a leitura do próximo reg no arq */
    cursor += tam_reg; 
  }
  
  fclose(arq);
  
  return(i-1);
	
}

/* Atualiza o arquivo com a nova avaliação */
int da_avalia_filme(int id, float nota) {
  /* Retorno
     1 - O filme com o id passado não existe
     0 - Atualização efetuada.
  */

  int tam_reg, id_reg, n_aval;
  float media;
  long int cursor = 0; /* indice de leitura do arquivo */
  FILE *arq;

  /* abre o arquivo com permissão para escrita */
  arq = fopen("filmes.dat", "r+");

  while(fscanf(arq, "%d@%d@%d@%f@", &tam_reg, &id_reg, 
	       &n_aval, &media) != EOF) {
    /* registro encontrado */
    if(id_reg == id) {
      /* Cálculo da nova média para o filme */
      float nova_media;
      nova_media = (media*n_aval + nota)/(n_aval+1);
      
      /* caminha no arquivo até o início do n de avaliações */
      fseek(arq, -(2/*@s*/ + TAM_MEDIA + TAM_N_AVALIACOES), 
	    SEEK_CUR);

      /* Atualização dos valores: n de avaliações e média */
      fprintf(arq, "%04d@%06.2f@", n_aval+1, nova_media);

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
