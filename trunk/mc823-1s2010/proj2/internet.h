/* Funções para auxiliar nas operações com os sockets  */

/* Retorna o socketfd da "conexão" com o servidor */
/* Note que como estamos usando datagram_socket (UDP),
   essa conexão funciona apenas como uma configuração. */
int client_get_connection(char **argv);

/* Envia um buffer por datagrama (UDP) */
int client_udp_push_buffer (int socket, char *buffer, int n);

/* Recebe o datagrama enviado pelo servidor. 
   Implementa o time-out com o uso do select() 
   Retorna -1 caso tenha esgotado o timeout. */
int client_udp_pop_buffer (int socket, char *buffer, int n);

