/*********************************************************************/
/*************************** Cliente *********************************/

/* Função auxiliar que retorna o socketfd da conexão com o servidor */
int client_get_connection(char **argv);

/* Função auxiliar de envio da opção para o servidor */
void client_send_option(int socketfd, char opt);

/* Le o número de filmes passado no próximo parâmetro da stream */
int client_get_n_filmes(int socket);

/* Copia a str de filme da stream */
void client_get_filme_str(int socket, char *f_str);


/*************************** Cliente *********************************/
/*********************************************************************/



/*********************************************************************/
/**************************** Server *********************************/

/* Recebe a opção da stream */
char server_recv_option(int connect_socketfd);

/**************************** Server *********************************/
/*********************************************************************/



/*********************************************************************/
/***************************** Geral *********************************/

/* Envia (ou tenta enviar) um caractere para o buffer de saída */
int udp_socket_push_char(int socket, char c);














/* Envia um caractere para a stream */
void socket_push_char(int socket, char c);

/* Retira um caractere da stream */
char socket_pop_char(int socket);

/* Envia um buffer para a stream */
void socket_push_buffer(int socket, int n, char *buffer);

/* Retira um buffer da stream */
void socket_pop_buffer(int socket, int n, char *buffer);


/***************************** Geral *********************************/
/*********************************************************************/
