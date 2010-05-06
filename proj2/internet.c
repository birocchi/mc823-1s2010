//Bibliotecas comuns
#include "internet.h"
#include "defines.h"
#include "data_access.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

//Bibliotecas para manipulacao de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

//Bibliotecas para analise de tempo
#include <sys/time.h>
#include <time.h>


/***********************************************************/
/********************** Cliente ****************************/

/* Retorna o socketfd da conexão com o servidor */
int client_get_connection(char **argv) {

  int status, socketfd;
  struct addrinfo opcoes;
  struct addrinfo *servinfo;  // will point to the results

  memset(&opcoes, 0, sizeof(opcoes)); // zera a estrutura
  opcoes.ai_family = AF_INET;         // IPv4
  opcoes.ai_socktype = SOCK_DGRAM;    // UDP datagram sockets
  opcoes.ai_flags = AI_PASSIVE;       // fill in my IP for me

  status = getaddrinfo(argv[1], SERVER_PORT_STR, &opcoes, &servinfo);
  if (status != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", 
						gai_strerror(status));
    exit(1);
  }

  /* cria o socket com os parâmetros setados */
  socketfd = socket(servinfo->ai_family, servinfo->ai_socktype, 
										servinfo->ai_protocol);

  /* faz a conexão com o socket do servidor */
  status = connect(socketfd, servinfo->ai_addr, servinfo->ai_addrlen);

  /* Caso dê algum erro na conexão, pára o cliente */
  if (status == -1){
    fprintf(stderr, "Problema na conexão.\n");
    exit(1);
  }
	
	/* libera a estrutura de informações do servidor */
  freeaddrinfo(servinfo);
  return(socketfd);

}


/* Envia um buffer por datagrama (UDP) */
int client_udp_push_buffer (int socket, char *buffer, int n) {
  
  /*
     Entradas:
     n - número de caracteres a serem escritos;
     buffer - buffer de onde se lê.
  */

  int i = 0;
  while (i == 0) {
    i = send(socket, buffer, n, 0);
  }
  return(i);
}

/********************** Cliente ****************************/
/***********************************************************/



/***********************************************************/
/*********************** Server ****************************/


/*********************** Server ****************************/
/***********************************************************/
