//Bibliotecas comuns
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

//Bibliotecas para manipulacao de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#define QTDE_CONEXOES 10 // número máximo de conexoes pendentes na fila

char buffer[TAM_BUFFER];     

char mensagem[TAM_MENSAGEM] = "Servidor diz: Pare de me encher o saco!";

int main()
{
    int bytes_enviados;  // Quantidade de bytes que foram enviados com sucesso
    int bytes_recebidos; // Quantidade de bytes que foram recebidos com sucesso
  
    int listen_socketfd, connect_socketfd; // Sockets de escuta e de conexao
    
    struct sockaddr_in meu_addr;    // Informacoes do meu endereco
    struct sockaddr_in cliente_addr; // Informacoes do endereco dos clientes
    int tam_endereco = sizeof(struct sockaddr_in); //Tamanho de um endereco
    
    listen_socketfd = socket(PF_INET, SOCK_STREAM, 0); // Cria o socket TCP de escuta
    printf("Socket TCP de escuta criado!\n");
    
    meu_addr.sin_family = AF_INET;
    meu_addr.sin_port = htons(SERVER_PORT);  // Porta em "short,network byte order", ver ":$man htons"
    meu_addr.sin_addr.s_addr = INADDR_ANY;  // INADDR_ANY = Descubra o meu endereço IP
    memset(&(meu_addr.sin_zero), '\0', 8);  // Por definicao, zerar o vetor sin_zero
    
    bind(listen_socketfd, (struct sockaddr *)&meu_addr, sizeof(struct sockaddr)); //Atribui a porta utilizada ao socket de escuta
    printf("Socket atribuido a porta: %d\n",meu_addr.sin_port);
    
    listen(listen_socketfd, QTDE_CONEXOES); //Espera por alguem que queira se conectar
    printf("Esperando alguma conexao...\n");
    
    connect_socketfd = accept(listen_socketfd, (struct sockaddr *)&cliente_addr, &tam_endereco); //Aceita a conexao e utiliza o socket para conexoes, deixando o socket de escuta livre
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
