//Bibliotecas comuns
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>   //Para usar o gethostbyname
#include "data_access.h"
#include "defines.h"

//Bibliotecas para manipulacao de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

char buffer[TAM_BUFFER];     

char mensagem[TAM_MENSAGEM] = "Cliente diz: Senhor, me da uma esmola?!";


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


void send_option(int socketfd, char opt) {
	int n = 0;

	while (n != sizeof(char)) {
		send(socketfd, &opt, sizeof(char), 0);
	}

	return;
}


/**************************************************************/
/******[inicio] Funções que implementam os casos de uso  ******/

void client_lista_todos_completo(int socketfd) {
  /* faz uma consulta ao servidor, coletando TODAS as infos de 
     TODOS os filmes */

  /* para cada filme f, chama da_print_full_info(f) */

  /* TODO */
  return;
}

void client_lista_todos(int socketfd) {
  /* também pega todas as infos de todos os filmes */

  /* para cada filme f, chama da_print_parcial(f) */
  /* TODO */
  return;
}

void client_reg_completo(int socketfd) {
  /* TODO */
  return;
}

void client_reg_sinopse(int socketfd) {
  /* TODO */
  return;
}

void client_reg_media(int socketfd) {
  /* TODO */
  return;
}

void client_reg_avalia(int socketfd) {
  /* TODO */
  return;
}

/*******[fim] Funções que implementam os casos de uso  ********/
/**************************************************************/



int main(int argc, char** argv) {

  /* Caso não haja o nome do servidor, da um erro */
  if (argc != 2) {
    fprintf(stderr, "uso: ./client <nome do servidor>\n");
    exit(1);
  }
	
	/* Estabelece a conexão com o servidor */
	int socketfd; //Socket de conexao
	socketfd = client_get_connection(argv);


	/* TESTE da conexão */
	/*int bytes_recebidos, bytes_enviados;
  while(TRUE){
    bytes_enviados = send(socketfd, mensagem, strlen(mensagem), 0);
    bytes_recebidos = recv(socketfd, buffer, TAM_BUFFER, 0);
    if(bytes_recebidos == 0) //Se o servidor encerrou a conexao,sai do loop
      break;
    bytes_recebidos = 0;
    printf("%s\n",buffer);
	}*/
  

	/* Loop da interface e chamadas para as funções que implementam cada 
	 uso do sistema. */
  char c;
		
  c = read_option();
    
	/* Envia a opção escolhida ao servidor (mesmo se for Sair) */
	send_option(socketfd, c);

  while(c != SAIR) {
      
    switch(c) {
	
    case LISTAR_TODOS_COMPLETO:
      client_lista_todos_completo(socketfd);
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
		send_option(socketfd, c);

  }
	

	close(socketfd); // fecha a conexão com o servidor

  return(0);

}
