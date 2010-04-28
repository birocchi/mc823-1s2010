// Bibliotecas comuns
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include "defines.h"
#include "internet.h"
#include "data_access.h"

// Biblioteca para threads
#include <pthread.h>

// Bibliotecas para manipulacao de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#define QTDE_CONEXOES 10 // número máximo de possíveis conexões pendentes na fila
#define PTHREAD_THREADS_MAX 10  /* valor maximo de threads simultaneas */


/* Variável global que armazena o status para cada thread
   TRUE: significa que ela está disponível;
   FALSE: significa que ela não está disponível.
*/
int available_thrs[QTDE_CONEXOES];


/**************************************************************/
/******[inicio] Funções que implementam os casos de uso  ******/

/* ## 1 ## */
void server_lista_todos_completo(int socket) {

  /*
    Esta função envia ao cliente uma sequencia de caracteres no formato:
    n_filmes@str_filme1@str_filme2@...@
  */

  /* Envio do numero de filmes */
  int n_filmes, n, i;
  char n_filmes_str[10]; /* max: 999999999@ */

  n_filmes = da_get_n_filmes();
  sprintf(n_filmes_str, "%d@", n_filmes);

  n = 0;
  while (n < strlen(n_filmes_str)) {
    n = send(socket, n_filmes_str, strlen(n_filmes_str), 0);
  }

  /* Agora, para cada filme, envia sua string crua. */
  char **registros;
  int *tam_reg;
  registros = (char **)malloc(n_filmes*sizeof(char *));
  tam_reg = (int *)malloc(n_filmes*sizeof(int));
  da_get_raw_strings(registros, tam_reg, n_filmes);

  for (i = 0; i < n_filmes; i++) {
    n = 0;
    socket_push_buffer(socket, tam_reg[i], registros[i]);
    free(registros[i]);
  }
  free(registros);
  free(tam_reg);

  return;
}

/* ## 2 ## */
void server_lista_todos(int socket) {
  /* O servidor faz exatamente a mesma coisa para a 
   listagem parcial. Todas informações são passadas
   para o cliente, mas este só imprime algumas delas. */
  server_lista_todos_completo(socket);
  return;
}

/* ## 3 ## */
void server_reg_completo(int socket) {
  
  /* servidor lê o ID que está sendo passado */
  char c, id_procurado[TAM_REG_ID]; /* 20 */
  int i = 0, tam_reg;

  /* leitura do ID pesquisado pelo cliente */
  c = socket_pop_char(socket);
  while (c!='@') {
    id_procurado[i] = c;
    c = socket_pop_char(socket);
    i++;
  }
  id_procurado[i] = '\0';

  int id;
  id = atoi(id_procurado);

  printf("  id requisitado: %d\n", id);

  /* Função que faz a busca.
     Retorna 1 se n encontrou nenhum filme.
     Caso contrário, aloca a memória e seta o filme. */
  
  char f_str[TAM_MAX_REG];

  /* se não encontrou nenhum filme, envia erro ao cliente */
  if (da_get_filme_by_id(f_str, id, &tam_reg) == 1) {
    socket_push_char(socket, '#');
    return;
  }

  /* se encontrou... */
  /* envia caractere de confirmação */
  socket_push_char(socket, '%');
  
  /* envia o filme */
  socket_push_buffer(socket, tam_reg, f_str);

  return;
}

/* ## 4 ## */
void server_reg_sinopse(int socket) {
  /* TODO */
  return;
}

/* ## 5 ## */
void server_reg_media(int socket) {
  /* TODO */
  return;
}

/* ## 6 ## */
void server_reg_avalia(int socket) {
  /* TODO */
  return;
}

/*******[fim] Funções que implementam os casos de uso  ********/
/**************************************************************/


/* Implementa o comportamento de cada thread */
void *trata_conexao (void *a) {
  
  int connect_socketfd;
  int t;

  char option;

  /* cast pra dizer que é um ap pra thread_attr */
  connect_socketfd = ((thread_attr *)a)->connect_socket;
  t = ((thread_attr *)a)->thr_index;

  /* recebe a opção enviada pelo cliente. */
  option = server_recv_option(connect_socketfd);
	
  printf("opção enviada pelo cliente: %c\n", option);

  /* Verificação do caso de saída e chamadas para cada caso específico */
  while(option != SAIR) {
      
    switch(option) {
			
    case LISTAR_TODOS_COMPLETO:
      server_lista_todos_completo(connect_socketfd);
      break;
    case LISTAR_TODOS:
      server_lista_todos(connect_socketfd);
      break;
    case REG_COMPLETO:
      server_reg_completo(connect_socketfd);
      break;
    case REG_SINOPSE:
      server_reg_sinopse(connect_socketfd);
      break;
    case REG_MEDIA:
      server_reg_media(connect_socketfd);
      break;
    case REG_AVALIAR:
      server_reg_avalia(connect_socketfd);
      break;
    }

    /* recebe a opção enviada pelo cliente. */
    option = server_recv_option(connect_socketfd);
    printf("opção enviada pelo cliente: %c\n", option);
  }
	
  printf("Thread %d diz: terminei! Fechando o socket %d...\n", t, connect_socketfd);
  close(connect_socketfd);

  /* thread seta o valor do vetor de disponíveis para TRUE novamente */
  available_thrs[t] = TRUE;

  pthread_exit(NULL);
}

int main() {

  int listen_socketfd, connect_socketfd; // Sockets de escuta e de conexao

  int status;
  struct addrinfo opcoes;
  struct addrinfo *servinfo;  // Informações do meu endereço

  memset(&opcoes, 0, sizeof(opcoes)); // zera a estrutura
  opcoes.ai_family = AF_INET;         // IPv4
  opcoes.ai_socktype = SOCK_STREAM;   // TCP
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
  //  pthread_t thread;
  pthread_t threads[QTDE_CONEXOES];
  int i, t;

  /* Inicializa o vetor de threds disponíveis */
  for (i = 0; i < QTDE_CONEXOES; i++) available_thrs[i] = TRUE;

  struct sockaddr_storage client_addr;
  socklen_t addr_size;

  while(TRUE) {
    /* Aceitação da conexão. */
    printf("Esperando alguma conexao...\n");
    connect_socketfd = accept(listen_socketfd, (struct sockaddr *)&client_addr, &addr_size);
    if (connect_socketfd == -1){
      printf("Problema na conexão.\n");
      continue; /* Desiste dessa conexão e volta a tentar conectar a outro. */
    }
    printf("Conexao aceita!\n");
    
    /* Seleciona a primeira thread disponível */
    /* t recebe o indice da primeira thread disponível */
    t = -1;
    for (i = 0; i < QTDE_CONEXOES; i++) {
      if (available_thrs[i]==TRUE) {
	t = i; break;
      }
    }
    
    /* caso não haja nenhuma thread disponível, fecha a conexão e volta a ouvir */
    if (t == -1) { 
      printf("Não há thread disponível para aceitar a conexão.\n");
      close(connect_socketfd); continue;
    }

    /* Inicia a thread e passa o connect_socketfd pra ela. */
    available_thrs[t] = FALSE; /* agora essa thread não está disponível */
    printf("Main diz: vou passar para a thread o socket %d.\n", connect_socketfd);
    /* inicializa o atributo a passar para a thread */
    thread_attr a;
    a.connect_socket = connect_socketfd;
    a.thr_index = t;
    pthread_create(&threads[t], NULL, trata_conexao, (void *)&a);

  }

  
  return(0);
}
