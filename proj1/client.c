//Bibliotecas comuns
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>   //Para usar o gethostbyname
#include "data_access.h"

//Bibliotecas para manipulacao de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORTA_SERVIDOR 3490  // A porta em que o servidor escuta

#define TAM_BUFFER 200       // Tamanho do Buffer de recepcao de mensagens
char buffer[TAM_BUFFER];     

#define TAM_MENSAGEM 200     //Tamanho do Buffer de envio de Mensagens
char mensagem[TAM_MENSAGEM] = "Cliente diz: Senhor, me da uma esmola?!";

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



int main(int argc, char** argv) {
	
  //#####################################################//
	
	int bytes_enviados;  // Quantidade de bytes que foram enviados com sucesso
	int bytes_recebidos; // Quantidade de bytes que foram recebidos com sucesso
	
	int connect_socketfd; //Socket de conexao
	
	struct hostent *servidor;         // Struct para ler corretamente de argv[1] atraves de gethostbyname()
	struct sockaddr_in servidor_addr; // Informacao do endereco do servidor
  
	//Caso não haja o nome do servidor, da um erro
	if (argc != 2) {
		fprintf(stderr,"uso: nome do servidor\n");
		exit(1);
	}
  
	servidor = gethostbyname(argv[1]);
  
	connect_socketfd = socket(PF_INET, SOCK_STREAM, 0);
		
	servidor_addr.sin_family = AF_INET;
	servidor_addr.sin_port = htons(PORTA_SERVIDOR);  // Porta em "short,network byte order", ver ":$man htons"
	servidor_addr.sin_addr = *((struct in_addr *)servidor->h_addr); //Endereco IP do servidor
	memset(&(servidor_addr.sin_zero), '\0', 8); // Por definicao, zerar o vetor sin_zero
  
	connect(connect_socketfd, (struct sockaddr *)&servidor_addr, sizeof(struct sockaddr));
  
	while(TRUE){
		bytes_enviados = send(connect_socketfd, mensagem, strlen(mensagem), 0);
		bytes_recebidos = recv(connect_socketfd, buffer, TAM_BUFFER, 0);
		if(bytes_recebidos == 0) //Se o servidor encerrou a conexao,sai do loop
			break;
		bytes_recebidos = 0;
		printf("%s\n",buffer);
	}
  
	close(connect_socketfd);
	
  //#####################################################//

  /*char c;
		
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

    }

    c = read_option();
  }*/
	
  return(0);

}
