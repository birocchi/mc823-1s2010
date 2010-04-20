//Bibliotecas comuns
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include "defines.h"

//Bibliotecas para manipulacao de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#define QTDE_CONEXOES 10 // número máximo de possíveis conexões pendentes na fila

char buffer[TAM_BUFFER];     

char mensagem[TAM_MENSAGEM] = "Servidor diz: Pare de me encher o saco!";

int main() {
	int bytes_enviados;  // Quantidade de bytes que foram enviados com sucesso
	int bytes_recebidos; // Quantidade de bytes que foram recebidos com sucesso
  
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

  
	//Espera por alguem que queira se conectar
	listen(listen_socketfd, QTDE_CONEXOES);
	printf("Esperando alguma conexao...\n");
  
	/* Threads Time! */
	/* TODO */
	/* loop infinito que aceita as conexões dos clientes */


	/* Aceitação de uma única conexão, por enquanto... */
	struct sockaddr_storage client_addr;
	socklen_t addr_size;

	// Aceita a conexao e utiliza o socket para conexoes, deixando o socket de escuta livre
	connect_socketfd = accept(listen_socketfd, (struct sockaddr *)&client_addr, &addr_size);
	printf("Conexao aceita!\n");
  
	while(TRUE){
		bytes_recebidos = recv(connect_socketfd, buffer, TAM_BUFFER, 0);
		printf("%s\n",buffer);
		bytes_enviados = send(connect_socketfd, mensagem, strlen(mensagem), 0);
		close(connect_socketfd);
		break;
	}

  
	return(0);
}
