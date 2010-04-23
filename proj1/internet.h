/*********************************************************************/
/*************************** Cliente *********************************/

/* Função auxiliar que retorna o socketfd da conexão com o servidor */
int client_get_connection(char **argv);

/* Função auxiliar de envio da opção para o servidor */
void client_send_option(int socketfd, char opt);

/* Le o número de filmes passado no próximo parâmetro da stream */
int client_get_n_filmes(int socket);


/*************************** Cliente *********************************/
/*********************************************************************/



/*********************************************************************/
/**************************** Server *********************************/

/* Recebe a opção da stream */
char server_recv_option(int connect_socketfd);

/**************************** Server *********************************/
/*********************************************************************/
