#include <stdio.h>
#include <stdlib.h>
#include "data_access.h"

#define SAIR 's'
#define LISTAR_TODOS_COMPLETO 'a'
#define LISTAR_TODOS 'b'
#define REG_COMPLETO 'c'
#define REG_SINOPSE 'd'
#define REG_MEDIA 'e'
#define REG_AVALIAR 'f'

#define TRUE 1

char read_option() {
  /* considera os possiveis erros e só sai quando o usuario
     digitar um caractere válido */

  char c, aux;

  while(TRUE) {

    /* Mensagem com as opções... */
		system("clear");
    printf("Escolha uma entre as opções e tecle Enter:\n");
    printf("(opções com (*) requererão o id do filme)\n");
    printf(" (a) Listar todas as informações de todos os filmes.\n");
    printf(" (b) Listar id e título de todos os filmes.\n");
    printf(" (c) Listar todas as informações de um filme. (*)\n");
    printf(" (d) Mostrar a sinopse de um filme. (*)\n");
    printf(" (e) Mostrar a avaliação de um filme. (*)\n");
    printf(" (f) Avaliar um filme! (*)\n");
    printf(" (s) Sair\n  ");

    c = getchar(); aux = getchar();
    if((c==SAIR || c==LISTAR_TODOS_COMPLETO || c==LISTAR_TODOS ||
	c==REG_COMPLETO || c==REG_SINOPSE || c==REG_MEDIA ||
	c==REG_AVALIAR) && aux=='\n') {
      /* se a opcao lida é válida e o próximo caractere foi Enter, 
	 retorna o caractere válido digitado*/
      return(c);
    } else {
      /* caso contrário, 'come' todo o resto da linha e volta às msgs */
      if(aux != '\n') { while(getchar()!='\n'); }
    }
  } /* fim do while */

}


/**************************************************************/
/******[inicio] Funções que implementam os casos de uso  ******/
/**************************************************************/
void client_lista_todos_completo() {
  /* faz uma consulta ao servidor, coletando TODAS as infos de 
     TODOS os filmes */

  /* para cada filme f, chama da_print_full_info(f) */

  /* TODO */
  return;
}

void client_lista_todos() {
  /* também pega todas as infos de todos os filmes */

  /* para cada filme f, chama da_print_parcial(f) */
  /* TODO */
  return;
}

void client_reg_completo() {
  /* TODO */
  return;
}

void client_reg_sinopse() {
  /* TODO */
  return;
}

void client_reg_media() {
  /* TODO */
  return;
}

void client_reg_avalia() {
  /* TODO */
  return;
}

/**************************************************************/
/*******[fim] Funções que implementam os casos de uso  ********/
/**************************************************************/



int main() {

  char c;

  c = read_option(); 

  while(c != SAIR) {

    switch(c) {

    case LISTAR_TODOS_COMPLETO:
      client_lista_todos_completo();
      break;
    case LISTAR_TODOS:
      client_lista_todos();
      break;
    case REG_COMPLETO:
      client_reg_completo();
      break;
    case REG_SINOPSE:
      client_reg_sinopse();
      break;
    case REG_MEDIA:
      client_reg_media();
      break;
    case REG_AVALIAR:
      client_reg_avalia();
      break;

    default:
      /* teoricamente, nunca é pra entrar aqui, pois c já
	 foi filtrado em read_option */
      c = read_option();
      break;
    }

    c = read_option();
  }
	
  return(0);

}
