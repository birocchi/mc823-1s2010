/***********************************************************/
/********************** Cliente ****************************/

/* Retorna o socketfd da "conexão" com o servidor */
/* Note que como estamos usando datagram_socket (UDP),
	 essa conexão funciona apenas como uma configuração. */
/* OK */int client_get_connection(char **argv);

/* Envia um buffer por datagrama (UDP) */
/* OK */int client_udp_push_buffer (int socket, char *buffer, int n);

/* Recebe o datagrama enviado pelo servidor. 
   Implementa o time-out com o uso do select() 
   Retorna -1 caso tenha esgotado o timeout. */
/* OK */int client_udp_pop_buffer (int socket, char *buffer, int n);


/* Le o número de filmes passado no próximo parâmetro da stream */
/* ? */int client_get_n_filmes(int socket);

/* Copia a str de filme da stream */
/* ? */void client_get_filme_str(int socket, char *f_str);




/********************** Cliente ****************************/
/***********************************************************/



/***********************************************************/
/*********************** Server ****************************/


/*********************** Server ****************************/
/***********************************************************/
