#define TRUE 1
#define FALSE 0

#define LISTAR_TODOS_COMPLETO '1'
#define LISTAR_TODOS '2'
#define REG_COMPLETO '3'
#define REG_SINOPSE '4'
#define REG_MEDIA '5'
#define REG_AVALIAR '6'
#define SAIR '7'


// A Porta em que o servidor escuta
#define SERVER_PORT 50000
#define SERVER_PORT_STR "50000"

// Tamanho do Buffer de recepcao de mensagens
#define TAM_BUFFER 200

// Tamanho do Buffer de envio de Mensagens
#define TAM_MENSAGEM 200

// Tempo limite de espera por resposta do servidor, em MICRO seg
#define TIMEOUT 50000 /* 50000us = 50ms */

// Estrutura para definir o atributo a ser passado para a thread
typedef struct {
  int connect_socket;
  int thr_index;
} thread_attr ;
