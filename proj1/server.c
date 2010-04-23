// Bibliotecas comuns
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include "defines.h"

// Biblioteca para threads
#include <pthread.h>

// Bibliotecas para manipulacao de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#define QTDE_CONEXOES 10 // número máximo de possíveis conexões pendentes na fila
#define PTHREAD_THREADS_MAX 10  /* valor maximo de threads simultaneas */

char buffer[TAM_BUFFER];     

char mensagem[TAM_MENSAGEM] = "Servidor diz: Pare de me encher o saco!";



/**************************************************************/
/******[inicio] Funções que implementam os casos de uso  ******/

void server_lista_todos_completo() {
  /* TODO */
  return;
}

void server_lista_todos() {
  /* TODO */
  return;
}

void server_reg_completo() {
  /* TODO */
  return;
}

void server_reg_sinopse() {
  /* TODO */
  return;
}

void server_reg_media() {
  /* TODO */
  return;
}

void server_reg_avalia() {
  /* TODO */
  return;
}

/*******[fim] Funções que implementam os casos de uso  ********/
/**************************************************************/


char recv_option(connect_socketfd) {
	char opt;
	int n = 0;

	while (n != sizeof(char)) {
		n = recv(connect_socketfd, &opt, sizeof(char), 0);
	}

	return(opt);
}


void *trata_conexao (void *socket) {
  int connect_socketfd;
	//  int bytes_recebidos, bytes_enviados;

	char option;

	/* cast pra dizer que é um ap pra int, e *(...) pra de-referenciar */
  connect_socketfd = *((int *)socket);

	/* recebe a opção enviada pelo cliente. */
	option = recv_option(connect_socketfd);
	
	printf("opção enviada pelo cliente: %c\n", option);

	/* Verificação do caso de saída e chamadas para cada caso específico */
	while(option != SAIR) {
      
    switch(option) {
			
    case LISTAR_TODOS_COMPLETO:
      server_lista_todos_completo();
      break;
    case LISTAR_TODOS:
      server_lista_todos();
      break;
    case REG_COMPLETO:
      server_reg_completo();
      break;
    case REG_SINOPSE:
      server_reg_sinopse();
      break;
    case REG_MEDIA:
      server_reg_media();
      break;
    case REG_AVALIAR:
      server_reg_avalia();
      break;
		}

		/* recebe a opção enviada pelo cliente. */
		option = recv_option(connect_socketfd);
	 	printf("opção enviada pelo cliente: %c\n", option);
  }
	
	printf("Thread diz: terminei! Fechando o socket...\n");
	close(connect_socketfd);
  pthread_exit(NULL);
}

int main() {

  //  int bytes_enviados;  // Quantidade de bytes que foram enviados com sucesso
  //int bytes_recebidos; // Quantidade de bytes que foram recebidos com sucesso
  
  int listen_socketfd, connect_socketfd; // Sockets de escuta e de conexao

  int status;
  struct addrinfo opcoes;
  struct addrinfo *servinfo;  // Informações do meu endereço

  memset(&opcoes, 0, sizeof(opcoes)); // zera a estrutura
  opcoes.ai_family = AF_INET;         // IPv4
  opcoes.ai_socktype = SOCK_STREAM;   // TCP stream sockets
  opcoes.ai_flags = AI_PASSIVE;       // fill in my IP for me

  status = getaddrinfo(NULL, SERVER_PORT_STR, &opcoes, &servinfo);
  if (status != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  // cria o socket TCP de escuta
  listen_socketfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  printf("Socket TCP de escuta criado!\n");
  
  //Atribui a porta utilizada ao socket de escuta
  status = bind(listen_socketfd, servinfo->ai_addr, servinfo->ai_addrlen); 
  if (status == -1) {
    fprintf(stderr, "error on binding the socket to a port\n");
    exit(1);
  }
  freeaddrinfo(servinfo); // libera a estrutura de informações do servidor

  /* Atribui o socket como ouvinte das conexões. */
  listen(listen_socketfd, QTDE_CONEXOES);

  /* Threads Time! */
  pthread_t thread; //s[QTDE_CONEXOES]; /* TODO: multi-thread, man! */
  //int i, available_thrs[QTDE_CONEXOES];

  struct sockaddr_storage client_addr;
  socklen_t addr_size;

  //void *exit_status;

  while(TRUE) {
    /* Aceitação da conexão. */
		printf("Esperando alguma conexao...\n");
    connect_socketfd = accept(listen_socketfd, (struct sockaddr *)&client_addr, &addr_size);
    if (connect_socketfd == -1){
      printf("Problema na conexão.\n");
      continue; /* Desiste dessa conexão e volta a tentar conectar a outro. */
    }
    printf("Conexao aceita!\n");
    
    /* Inicia uma thread e passa o connect_socketfd pra ela. */
    printf("Main diz: vou passar para a thread o socket %d.\n", connect_socketfd);
    /* i = get_av_thr(); */
    //i = 0;
    pthread_create(&thread, NULL, trata_conexao, (void *)&connect_socketfd);

    /* Espera a thread terminar */
    /*pthread_join(thread, &exit_status);*/

  }


  
  return(0);
}
