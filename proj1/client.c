//Bibliotecas comuns
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>   //Para usar o gethostbyname
#include "data_access.h"
#include "defines.h"
#include "internet.h"

//Bibliotecas para manipulacao de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <sys/time.h>
#include <time.h>

/* Função auxiliar para tratamento de entrada */
char read_option() {
  /* considera os possiveis erros e só sai quando o usuario
     digitar um caractere válido */

  char c, aux;

  while(TRUE) {

    /* Mensagem com as opções... */
    system("clear");
    printf("Escolha uma entre as opções e tecle Enter:\n");
    printf("(opções com (*) requererão o id do filme)\n");
    printf(" [1] Listar todas as informações de todos os filmes.\n");
    printf(" [2] Listar id e título de todos os filmes.\n");
    printf(" [3] Listar todas as informações de um filme. (*)\n");
    printf(" [4] Mostrar a sinopse de um filme. (*)\n");
    printf(" [5] Mostrar a avaliação de um filme. (*)\n");
    printf(" [6] Avaliar um filme! (*)\n");
    printf(" [7] Sair\n  ");

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

/* ## 1 ## */
void client_lista_todos_completo(int socketfd) {
  /* 
     Não é necessário enviar mais informações ao servidor, apenas
     aguardar um retorno.
     O formato desse retorno será:
     n_filmes@str_do_filme1@str_do_filme2@str_do_filme3@
  */

  int n_filmes, i;
  char filme_str[TAM_MAX_REG]; /* 1024 */
  filme *lista_filmes, *f, *last_f;
	
  /* Leitura do número de filmes retornado pelo servidor */
  n_filmes = client_get_n_filmes(socketfd);

  if (n_filmes == 0) {
    printf("Não há filmes no servidor!\n");
    printf("Tecle Enter para continuar...");
    getchar();
    return;
  }
  printf("Número de filmes encontrados: %d\n\n", n_filmes);

  for (i = 0; i < n_filmes; i++) {

    int tam_filme;
		
    /* Le a string do filme */
    client_get_filme_str(socketfd, filme_str);

    /* Aloca a estrutura para guardar o filme */
    f = (filme *)malloc(sizeof(filme));
    da_str_to_filme(f, &tam_filme, filme_str);

    /* Seta a lista dos filmes */
    if (i==0){ /* primeiro filme */
      lista_filmes = f;
    }
    else {
      last_f->prox_filme = f; /* concatena o filme à lista */
    }
    last_f = f; /* atualiza o apontador para o último filme */
  }
	
  /* para cada filme na lista, chama da_print_full_info(f) */
  for (f = lista_filmes; f != NULL; f = (filme *)f->prox_filme) {
    da_print_full_info(f);
    printf("\n-------------------------\n");
  }
	
  /* libera a memória dos filmes */
  da_free_all(lista_filmes);

  //printf("Tecle Enter para continuar...");
  //getchar();

  return;
}

/* ## 2 ## */
void client_lista_todos(int socketfd) {

  /* Cliente praticamente igual para a listagem completa. */
  int n_filmes, i;
  char filme_str[TAM_MAX_REG]; /* 1024 */
  filme *lista_filmes, *f, *last_f;
	
  n_filmes = client_get_n_filmes(socketfd);

  if (n_filmes == 0) { printf("Não há filmes no servidor!\n");
    printf("Tecle Enter para continuar..."); getchar(); return;
  }
  printf("Número de filmes encontrados: %d\n\n", n_filmes);

  for (i = 0; i < n_filmes; i++) {

    int tam_filme;
    client_get_filme_str(socketfd, filme_str);
    f = (filme *)malloc(sizeof(filme));
    da_str_to_filme(f, &tam_filme, filme_str);
    if (i==0) { lista_filmes = f;} else { last_f->prox_filme = f; }
    last_f = f; /* atualiza o apontador para o último filme */
  }
	
  /* para cada filme na lista, chama da_print_partial_info(f) */
  for (f = lista_filmes; f != NULL; f = (filme *)f->prox_filme) {
    da_print_partial_info(f);
    printf("\n-------------------------\n");
  }
	
  da_free_all(lista_filmes);
  printf("Tecle Enter para continuar..."); getchar();
  return;
}

/* ## 3 ## */
void client_reg_completo(int socketfd) {

  char c, id_procurado[TAM_REG_ID]; /* 20 */
  int i = 0;

  /* Leitura do id procurado (digito p/ dig.) */
  printf("ID do filme: ");
  c = getchar();
  while (c!='\n') { id_procurado[i] = c; i++; c = getchar(); }
  id_procurado[i] = '@'; /* coloca um @ para finalizar o id */

  /* envia o id procurado ao servidor */
  socket_push_buffer(socketfd, i+1, id_procurado);

  /* leitura da resposta do servidor */
  do {
    c = socket_pop_char(socketfd);
  } while(c == '\0'); /* limpa a stream */
  
  /* Caso não tenha encontrado nenhum filme */
  if (c == '#') {
    printf("\nFilme não encontrado.\n");
  } else {
    /* recebe a str do filme encontrado */
    char f_str[TAM_MAX_REG];
    i = 0;
    c = socket_pop_char(socketfd);
    while(c != '\0') { 
      f_str[i] = c;
      c = socket_pop_char(socketfd);
      i++;
    }

    /* monta a estrutura de filme */
    filme f;
    int tam_reg;
    da_str_to_filme(&f, &tam_reg, f_str);

    /* Imprime resultado da pesquisa */
    printf("Filme encontrado!\n\n");
    da_print_full_info(&f);
  }

  printf("\nAperte Enter para continuar...");
  getchar();

  return;
}

/* ## 4 ## */
void client_reg_sinopse(int socketfd) {

  /* Cópia do caso de uso para a listagem completa de um filme, 
     diferenciando apenas a impressão dos dados.*/
  
  char c, id_procurado[TAM_REG_ID]; int i = 0;

  printf("ID do filme: "); c = getchar();
  while (c!='\n') { id_procurado[i] = c; i++; c = getchar(); }
  id_procurado[i] = '@'; /* coloca um @ para finalizar o id */

  socket_push_buffer(socketfd, i+1, id_procurado);

  do { c = socket_pop_char(socketfd);
  } while(c == '\0'); /* limpa a stream */
  
  if (c == '#') { printf("\nFilme não encontrado.\n"); }
  else {
    char f_str[TAM_MAX_REG];
    i = 0; c = socket_pop_char(socketfd);
    while(c != '\0') { 
      f_str[i] = c; 
      c = socket_pop_char(socketfd);
      i++;
    }

    filme f; int tam_reg;
    da_str_to_filme(&f, &tam_reg, f_str);

    printf("Filme encontrado!\n\n");
    printf("Sinopse: %s\n", f.sinopse);
  }

  printf("\nAperte Enter para continuar...");
  getchar();

  return;
}

/* ## 5 ## */
void client_reg_media(int socketfd) {

  /* Cópia do caso de uso para a listagem completa de um filme, 
     diferenciando apenas a impressão dos dados.*/

  char c, id_procurado[TAM_REG_ID]; int i = 0;

  printf("ID do filme: "); c = getchar();
  while (c!='\n') { id_procurado[i] = c; i++; c = getchar(); }
  id_procurado[i] = '@'; /* coloca um @ para finalizar o id */

  socket_push_buffer(socketfd, i+1, id_procurado);

  do { c = socket_pop_char(socketfd);
  } while(c == '\0'); /* limpa a stream */
  
  if (c == '#') { printf("\nFilme não encontrado.\n"); }
  else {
    char f_str[TAM_MAX_REG];
    i = 0; c = socket_pop_char(socketfd);
    while(c != '\0') { 
      f_str[i] = c; 
      c = socket_pop_char(socketfd);
      i++;
    }

    filme f; int tam_reg;
    da_str_to_filme(&f, &tam_reg, f_str);

    printf("Filme encontrado!\n\n");
    printf("Média: %3.2f (%d avaliações)\n", f.media, f.n_aval);
  }

  printf("\nAperte Enter para continuar...");
  getchar();

  return;
}

/* ## 6 ## */
void client_reg_avalia(int socketfd) {

  char c, id_avaliar[TAM_REG_ID] /*20*/, nota[7];
  int i, j;

  /* Leitura do id do filme para avaliar e nota */
  printf("ID do filme a avaliar: ");
  i = 0; c = getchar();
  while (c!='\n') { id_avaliar[i] = c; i++; c = getchar(); }
  id_avaliar[i] = '@'; /* coloca um @ para finalizar o id */
  printf("Nota [formato: abc.de]: ");
  j = 0; c = getchar();
  while (c!='\n') { nota[j] = c; j++; c = getchar(); }
  nota[j] = '@'; /* coloca um @ para finalizar a nota*/

  /* envia o id e a nota ao servidor */
  socket_push_buffer(socketfd, i+1, id_avaliar);
  socket_push_buffer(socketfd, j+1, nota);

  /* leitura da resposta do servidor */
  do {
    c = socket_pop_char(socketfd);
  } while(c == '\0'); /* limpa a stream */
  
  /* Caso não tenha encontrado nenhum filme */
  if (c == '#') {
    printf("\nFilme não encontrado.\n");
  } else {
    printf("\nAvaliação realizada com sucesso!\n");
  }

  printf("\nAperte Enter para continuar...");
  getchar();

  return;
}

/*******[fim] Funções que implementam os casos de uso  ********/
/**************************************************************/



int main(int argc, char** argv) {

  struct timeval tv1, tv2, tvres;
  long double total_time;

  /* Caso não haja o nome do servidor, da um erro */
  if (argc != 2) {
    fprintf(stderr, "uso: ./client <nome do servidor>\n");
    exit(1);
  }
	
  /* Estabelece a conexão com o servidor */
  int socketfd; //Socket de conexao
  socketfd = client_get_connection(argv);

  /* Loop da interface e chamadas para as funções que implementam cada 
     uso do sistema. */
  char c;
		
  c = read_option();
    
  /* Envia a opção escolhida ao servidor (mesmo se for Sair) */
  client_send_option(socketfd, c);

  while(c != SAIR) {
      
    switch(c) {
	
    case LISTAR_TODOS_COMPLETO:
//      gettimeofday(&tv1, NULL); /* lê o t1 */
      client_lista_todos_completo(socketfd);
      //gettimeofday(&tv2, NULL); /* lê o t2 */
      //timersub(&tv2, &tv1, &tvres); /* resposta = t2 - t1 */
      //total_time = tvres.tv_sec*1000000 + tvres.tv_usec; /* resposta em micro-segundos */
      /* manda o tempo para a saída padrão de erro: coleta para um arquivo (via shell) */
      //fprintf(stderr, "%.0Lf\n", (long double) total_time );
      break;
    case LISTAR_TODOS:
      client_lista_todos(socketfd);
      break;
    case REG_COMPLETO:
      client_reg_completo(socketfd);
      break;
    case REG_SINOPSE:
      client_reg_sinopse(socketfd);
      break;
    case REG_MEDIA:
      client_reg_media(socketfd);
      break;
    case REG_AVALIAR:
      client_reg_avalia(socketfd);
      break;
			
    }
    
    c = read_option();
    client_send_option(socketfd, c);

  }
	
  close(socketfd); // fecha a conexão com o servidor
  return(0);

}
