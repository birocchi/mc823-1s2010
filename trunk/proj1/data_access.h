typedef struct {
	int id;
	char *titulo;
	char *sinopse;
	char *sala;
	char *horarios;

	struct filme *prox_filme; /* NULL caso seja um único filme ou o último da lista */
} filme;

/* 'da' refere-se a data access (para facilitar depois pra chamar as funções) */

/* Função que retorna um filme a partir de um id */
int da_get_filme_by_id(filme *f_ret, int id);

/* Função responsável por fazer um parse da string lida do arquivo para um filme */
int da_str_to_filme(filme *f_ret, char *f_str);


