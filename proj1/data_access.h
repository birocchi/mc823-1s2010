#define TAM_MAX_REG 1024 /* 1kB */
#define TAM_MAX_TIT 30
#define TAM_MAX_SIN 900
#define TAM_MAX_SALA 20
#define TAM_MAX_HOR 20

#define TAM_MAX_ATR 900

#define TAM_REG_ID 20 /* tamanho max dos digitos do tamanho do registro e do id */

#define TAM_MEDIA 6 /* abc.de (valor de 0 a 100, com 2 dígitos decimais) */

#define TAM_N_AVALIACOES 4 /* cada filme pode ter até 9999 avaliações */

typedef struct {
  int id;
  char *titulo;
  char *sinopse;
  char *sala;
  char *horarios;
  
  int n_aval; /* número de avaliações */
  float media;
  
  struct filme *prox_filme; /* NULL caso seja um único filme ou o último da lista */
} filme;

/* 'da' refere-se a data access (para facilitar depois pra chamar as funções) */

/* Função responsável por fazer um parse da string lida do arquivo para um filme */
int da_str_to_filme(filme *f_ret, int *tam_reg, char *f_str);

/* Libera as strings alocadas dinamicamente */
void da_free_strs(filme *f);




/******* Funções a serem chamadas externamente (API) ********/

/* Imprime as informações já formatadas de um filme */
void da_print_full_info(filme *f);

/* Imprime as informações já formatadas de um filme */
void da_print_partial_info(filme *f);

/* Função que retorna um filme a partir de um id */
int da_get_filme_by_id(char *f_str, int id, int *tamanho);

/* Libera toda a memória alocada para o(s) filme(s) (strings e struct) 
 - retorna o numero de filmes desalocados */
int da_free_all(filme *f);

/* Seta uma lista com todos os filmes no arquivo */
int da_get_todos_filmes(filme **filmes);

/* Retorna o número de filmes no arquivo */
int da_get_n_filmes();

/* Retorna uma matriz com os registros todos em formato string pura */
void da_get_raw_strings (char **registros, int *tam_registros, int n_registros);

/* Avalia a nota de avaliação do filme e atualiza seu número de atualizações */
int da_avalia_filme(int id, float nota);
