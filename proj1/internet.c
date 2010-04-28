#include "internet.h"
#include "defines.h"
#include "data_access.h"
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
  socket_push_char(socketfd, opt);
  return;
}

/* Le o número de filmes passado no próximo parâmetro da stream */
int client_get_n_filmes(int socket) {

  char str[10], c;
  int i = 0;

  /* Preenche uma str com os numeros até chegar o '@' */
  c = socket_pop_char(socket);
  while (c != '@') {
    str[i] = c;
    i++;
    c = socket_pop_char(socket);
  }
  str[i] = '\0';
	
  return(atoi(str));
}

/* Copia a str de filme da stream */
void client_get_filme_str(int socket, char *f_str) {
	
  int i, tam_reg;
  char c, tam_reg_str[TAM_REG_ID];

  /* leitura do tamanho do registro */
  i = 0;
  c = socket_pop_char(socket);
  while (c != '@') {
    //f_str[i] = c;
    tam_reg_str[i] = c;
    i++;
    c = socket_pop_char(socket);
  }
  //f_str[i] = '@';
  tam_reg_str[i] = '\0';

  tam_reg = atoi(tam_reg_str);

  /* Sei o tamanho do registro e sei até onde já li; vou ler o resto */
  tam_reg = tam_reg - i -1; /* numero de caracteres restantes */
  int n = 0;
  char buffer[TAM_MAX_ATR];
  while (n < (tam_reg-1)) {
    n += recv(socket, &buffer[n], (tam_reg - n), 0);
  }
  buffer[n] = '\0';
	
  /* por fim, concatena as strings já lidas, copiando para a str de retorno */
  sprintf(f_str, "%s%s", tam_reg_str, buffer);
	
  return;
}

/*************************** Cliente *********************************/
/*********************************************************************/


/*********************************************************************/
/**************************** Server *********************************/

/* Recebe a opção da stream */
char server_recv_option(int connect_socketfd) {
  return(socket_pop_char(connect_socketfd));
}


/**************************** Server *********************************/
/*********************************************************************/


/*********************************************************************/
/***************************** Geral *********************************/

/* Envia um caractere para a stream */
void socket_push_char(int socket, char c) {
  int n = 0;
	
  while (n != sizeof(char)) {
    n = send(socket, &c, sizeof(char), 0);
  }

  return;
}

/* Retira um caractere da stream */
char socket_pop_char(int socket) {
  char c;
  int n = 0;

  while (n != sizeof(char)) {
    n = recv(socket, &c, sizeof(char), 0);
  }

  return(c);
}


/* Envia um buffer para a stream */
void socket_push_buffer(int socket, int n, char *buffer) {
  /* 
     Entradas:
     n - número de caracteres a serem escritos;
     buffer - buffer de onde se lê.
  */

  int i = 0;
  
  while(i < (n-1)) {
    printf("Envio de stream começando pelo caractere: %d.\n", i);
    i += send(socket, &buffer[i], (n - i), 0);
    printf("Enviei %d...\n", i);
  }

  return;
}

/* Retira um buffer da stream */
void socket_pop_buffer(int socket, int n, char *buffer) {
  /* 
     Entradas:
     n - número de caracteres a serem lidos;
     buffer - buffer de leitura.
  */

  int i = 0;

  /* Vai acumulando o valor dos bytes já lidos, e enquanto não
   chega ao fim, continua lendo... */
  while(i < (n-1)) {
    i += recv(socket, &buffer[i], (n - i), 0);
    printf("\nRecebi: %d.\n", i);
  }

  return;
}

/***************************** Geral *********************************/
/*********************************************************************/
