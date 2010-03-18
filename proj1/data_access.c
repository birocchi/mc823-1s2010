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
	(*f_ret).id = atoi(str);

	/* numero de avaliações */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; }
  str[j] = '\0';
  (*f_ret).n_aval = atoi(str);
	
	/* média */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; }
  str[j] = '\0';
  (*f_ret).media = atof(str);
	
  /* titulo */
  i++; j = 0;
  while(f_str[i]!='@') {
    str[j] = f_str[i];
    i++; j++;
  }
  str[j] = '\0';
  /* aloca a string dinamicamente */
  (*f_ret).titulo = (char *)malloc((j+1)*sizeof(char));
  sprintf((*f_ret).titulo, "%s", str);

  /* Blocos de código similares ao de cima, só que comprimidos  */
  /* sinopse */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i];	i++; j++;	} str[j] = '\0';
  (*f_ret).sinopse = (char *)malloc((j+1)*sizeof(char));
  sprintf((*f_ret).sinopse, "%s", str);

  /* sala */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; } str[j] = '\0';
  (*f_ret).sala = (char *) malloc((j+1)*sizeof(char));
  sprintf((*f_ret).sala, "%s", str);

  /* horarios */
  i++; j = 0;
  while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; } str[j] = '\0';
  (*f_ret).horarios = (char *) malloc((j+1)*sizeof(char));
  sprintf((*f_ret).horarios, "%s", str);

  /* next - lembra dele? :) */
  (*f_ret).prox_filme = NULL;

  return(0);
}


void da_print_infos(filme *f) {
  printf("Id: %d\n", (*f).id);
  printf("Titulo: %s\n", (*f).titulo);
  printf("Sinopse: %s\n", (*f).sinopse);
  printf("Sala: %s\n", (*f).sala);
  printf("Horários: %s\n", (*f).horarios);
  return;
}

void da_free_strs(filme *f) {
  free((*f).titulo);
  free((*f).sinopse);
  free((*f).sala);
  free((*f).horarios);
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
	if((*f).prox_filme == NULL) {
		free(f);
		return(0); /* retorna, inicializando contador */
	}

	/* Chamada recursiva */
	i = da_free_all((filme *)(*f).prox_filme); /* cast pro -Wall n reclamar */

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

	/* TODO */

	return(0);
}



int main() {

  filme *f;
  int id = 1;
	int n_filmes_desalocados;


	/* Exemplos de uso das funções */
  if((da_get_filme_by_id(&f, id)) == 0) {
    da_print_infos(f);
		n_filmes_desalocados = da_free_all(f);
  } else {
    printf("Filme não encontrado!\n");
  }

  return(0);
}
