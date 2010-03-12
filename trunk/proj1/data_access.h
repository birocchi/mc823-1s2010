#define TAM_MAX_TIT 30
#define TAM_MAX_SIN 900
#define TAM_MAX_SALA 20
#define TAM_MAX_HOR 20

#define INT 10

typedef struct {
	int id;
	char titulo[TAM_MAX_TIT];
	char sinopse[TAM_MAX_SIN];
	char sala[TAM_MAX_SALA];
	char horarios[TAM_MAX_HOR];

	struct filme *prox_filme; /* NULL caso seja um único filme ou o último da lista */
} filme;

/* 'da' refere-se a data access (para facilitar depois pra chamar as funções) */

/* Função que retorna um filme a partir de um id */
int da_get_filme_by_id(filme *f_ret, int id);

/* Função responsável por fazer um parse da string lida do arquivo para um filme */
int da_str_to_filme(filme *f_ret, int *tam_reg, char *f_str);


