#include "internet.h"
#include "defines.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


/*********************************************************************/
/*************************** Cliente *********************************/

/* Função auxiliar que retorna o socketfd da conexão com o servidor */
int client_get_connection(char **argv) {

  int status, socketfd;
  struct addrinfo opcoes;
  struct addrinfo *servinfo;  // will point to the results

  memset(&opcoes, 0, sizeof(opcoes)); // zera a estrutura
  opcoes.ai_family = AF_INET;         // IPv4
  opcoes.ai_socktype = SOCK_STREAM;   // TCP stream sockets
  opcoes.ai_flags = AI_PASSIVE;       // fill in my IP for me

  status = getaddrinfo(argv[1], SERVER_PORT_STR, &opcoes, &servinfo);
  if (status != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

	/* cria o socket com os parâmetros setados */
  socketfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	/* faz a conexão com o socket do servidor */
  connect(socketfd, servinfo->ai_addr, servinfo->ai_addrlen);

  freeaddrinfo(servinfo); // libera a estrutura de informações do servidor
	return(socketfd);

}

/* Função auxiliar de envio da opção para o servidor */
void client_send_option(int socketfd, char opt) {
	int n = 0;
	while (n != sizeof(char))
		n = send(socketfd, &opt, sizeof(char), 0);
	return;
}

/* Le o número de filmes passado no próximo parâmetro da stream */
int client_get_n_filmes(int socket) {
	/* Preenche uma str com os numeros até chegar o '@' */
	
	return(2);
}

/*************************** Cliente *********************************/
/*********************************************************************/


/*********************************************************************/
/**************************** Server *********************************/

/* Recebe a opção da stream */
char server_recv_option(int connect_socketfd) {
	char opt;
	int n = 0;

	while (n != sizeof(char)) {
		n = recv(connect_socketfd, &opt, sizeof(char), 0);
	}

	return(opt);
}


/**************************** Server *********************************/
/*********************************************************************/

