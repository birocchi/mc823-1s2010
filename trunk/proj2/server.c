// Bibliotecas comuns
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include "defines.h"
#include "internet.h"
#include "data_access.h"
#include <signal.h>

// Bibliotecas para manipulacao de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>



/**************************************************************/
/******************* Variáveis Globais ************************/

/* Como o servidor só se comunicará por um socket, e com um 
   cliente de cada vez, essas variáveis podem ser globais, o que
   facilita sua utilização em funções auxiliares. */

/* Socket único do servidor */
int socketfd;

/* Variáveis para guardar informações do endereço do cliente */
struct sockaddr_storage client_addr;
size_t client_addr_len = sizeof(client_addr); /* necessário */

/* Variável para guardar a msg enviada pelo cliente */
char request[27];


/******************* Variáveis Globais ************************/
/**************************************************************/



/**************************************************************/
/******[inicio] Funções que implementam os casos de uso  ******/

/* ## 1 ## */
void server_lista_todos_completo() {
  
  /* Envia ao cliente:
   * -> um datagrama com número N de filmes
   * -> N datagramas: 1 para cada filme (string crua)
   */
  
  char n_filmes_str[10];
  int n_filmes, i;

  n_filmes = da_get_n_filmes();
  sprintf(n_filmes_str, "%09d", n_filmes);
  sendto(socketfd, n_filmes_str, 10, 0, (struct sockaddr *)
	 &client_addr, client_addr_len);
	
  /* Cada datagrama será montado com um vetor de caracteres de tamanho
     fixo. Esta é uma limitação necessária para o UDP */  
  char filme_str[TAM_MAX_REG];

  /* Para cada filme no arquivo... */
  for (i=1 ; i<=n_filmes ; i++) {
    
    /* seta o vetor com o i-ésimo filme no arquivo */
    da_get_raw_str(i, filme_str);

    /* envia o datagrama com o filme ao cliente */
    sendto(socketfd, filme_str, TAM_MAX_REG, 0, (struct sockaddr *)
	   &client_addr, client_addr_len);
  }
  
  return;
}

/* ## 2 ## */
void server_lista_todos() {
  /* Faz exatamente o mesmo procedimento que para a listagem 
     completa: todas as info são passadas ao cliente. */
  server_lista_todos_completo();
  return;
}

/* ## 3 ## */
void server_reg_completo() {
  
  /* leitura do id procurado */
  char id_str[21];
  int i, id;

  for (i=1; i<21; i++) { id_str[i-1] = request[i]; }
  id_str[20] = '\0'; id = atoi(id_str);
  printf("  id requisitado: %d\n", id);


  /* Realiza a busca. */
  char f_str[TAM_MAX_REG];
  int status, tam_reg;

  /* Retorna 1 se não encontrar nenhum filme. */  
  status = da_get_filme_by_id(f_str, id, &tam_reg);

  /* se não encontrou nenhum filme... */
  if (status == 1) {
    /* seta o código de erro na mensagem que irá para o cliente */
    f_str[0] = '#';
  }

  /* envia o filme (ou código de erro) ao cliente */
  sendto(socketfd, f_str, TAM_MAX_REG, 0, (struct sockaddr *)
	 &client_addr, client_addr_len);

  return;
}

/* ## 4 ## */
void server_reg_sinopse() {
  /* Neste caso, o servidor faz exatamente o mesmo
   * que na listagem completa de um registro:
   * 1- Recebe o registro procurado;
   * 2- Faz a busca;
   * 3- Se não encontrar o filme, retorna o caractere '#'
   * 4- Se encontrar, retorna a string crua do filme
   */
  server_reg_completo();
  return;
}

/* ## 5 ## */
void server_reg_media() {
  /* Neste caso, o servidor faz exatamente o mesmo
   * que na listagem completa de um registro:
   * 1- Recebe o registro procurado;
   * 2- Faz a busca;
   * 3- Se não encontrar o filme, retorna o caractere '#'
   * 4- Se encontrar, retorna a string crua do filme
   */
  server_reg_completo();
  return;
}

/* ## 6 ## */
void server_reg_avalia() {

  /* leitura do id procurado */
  char id_str[21];
  int i, id;

  for (i=1; i<21; i++) { id_str[i-1] = request[i]; }
  id_str[20] = '\0'; id = atoi(id_str);
  printf("  id requisitado: %d\n", id);

  /* leitura da nota */
  char nota_str[7];
  float nota;
  for (i=21; i<=26; i++) { nota_str[i-21] = request[i]; }
  nota_str[6] = '\0'; nota = atof(nota_str);
  printf("  nota enviada: %06.2f", nota);

  /*
   * Função que realiza a avaliação:
   * Retorna 1 se o filme não existe.
   * Retorna 0 se ocorreu tudo bem.
   */
  /* Nota: Esta função não requer mais exclusão mútua, pois o 
     servidor agora é iterativo e só um processo/thread pode
     querer escrever no arquivo por vez. */
  int status;
  status = da_avalia_filme(id, nota); 

  /* 
   * Prepara o caractere de resposta:
   * Caso o filme não exista, responde '#'
   * Caso contrário, confirma a avaliação com '%'
   */
  char resposta;
  if (status == 1) { resposta = '#'; }
  else { resposta = '%'; }

  /* envia um datagrama com apenas um caractere, o de resposta */
  sendto(socketfd, &resposta, 1, 0, (struct sockaddr *)
	 &client_addr, client_addr_len);
  
  return;
}

/*******[fim] Funções que implementam os casos de uso  ********/
/**************************************************************/





/* Trata o sinal de interrupção */
void trata_SIGINT(int sig) {
  printf("\nEncerrando o servidor...\n");
  close(socketfd);
  exit(0);
}



int main() {
  
  signal(SIGINT,trata_SIGINT);
  
  int status;
  struct addrinfo opcoes;
  struct addrinfo *servinfo; // Informações do meu endereço
  
  memset(&opcoes, 0, sizeof(opcoes)); // zera a estrutura
  opcoes.ai_family = AF_INET;         // IPv4
  opcoes.ai_socktype = SOCK_DGRAM;    // UDP datagram sockets
  opcoes.ai_flags = AI_PASSIVE;       // fill in my IP for me

  status = getaddrinfo(NULL, SERVER_PORT_STR, &opcoes, &servinfo);
  if (status != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  /* Cria o socket e o associa a uma porta */
  socketfd = socket(servinfo->ai_family, servinfo->ai_socktype, 
		    servinfo->ai_protocol);
 
  status = bind(socketfd, servinfo->ai_addr, servinfo->ai_addrlen);
  if (status == -1) {
    fprintf(stderr, "error on binding the socket to a port\n");
    exit(1);
  }
  freeaddrinfo(servinfo);
  printf("Socket UDP criado!\n");
  

  /* Loop infinito de recebimento e tratamento das mensagens */
  while (TRUE) {
    printf("Aguardando request...\n");

    /* Esta função bloqueia o servidor até que chegue um pacote. 
       O endereço do cliente é setado! */
    status = recvfrom(socketfd, request, 27, 0, (struct sockaddr *)
		      &client_addr, (socklen_t *) &client_addr_len);

    printf("Opção recebida: %c\n", request[0]);
    
    /* "O que vc quer, cliente?!" */
    switch(request[0]) {
      
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

    /* volta ao início do loop principal */

  }


  /* Processo servidor executa em loop infinito */
}
