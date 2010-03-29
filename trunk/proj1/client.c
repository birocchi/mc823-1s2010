#include <stdio.h>
#include "data_access.h"

#define SAIR 's'
#define LISTAR_TODOS_COMPLETO 'a'
#define LISTAR_TODOS 'b'
#define REG_COMPLETO 'c'
#define REG_SINOPSE 'd'
#define REG_MEDIA 'e'
#define REG_AVALIAR 'f'

char read_option() {
	/* considera os possiveis erros e só sai quando o usuario
	 digitar um caractere válido */

	/* TODO */

	return('s');
}


/**************************************************************/
/******[inicio] Funções que implementam os casos de uso  ******/
/**************************************************************/
void client_lista_todos_completo() {
	/* faz uma consulta ao servidor, coletando TODAS as infos de 
		 TODOS os filmes */

	/* para cada filme f, chama da_print_full_info(f) */

	/* TODO */
	return;
}

void client_lista_todos() {
	/* também pega todas as infos de todos os filmes */

	/* para cada filme f, chama da_print_parcial(f) */
	/* TODO */
	return;
}

void client_reg_completo() {
	/* TODO */
	return;
}

void client_reg_sinopse() {
	/* TODO */
	return;
}

void client_reg_media() {
	/* TODO */
	return;
}

void client_reg_avalia() {
	/* TODO */
	return;
}

/**************************************************************/
/*******[fim] Funções que implementam os casos de uso  ********/
/**************************************************************/



int main() {

	char c;

	c = read_option(); 

	while(c != SAIR) {

		switch(c) {

		case LISTAR_TODOS_COMPLETO:
			client_lista_todos_completo();
			break;
		case LISTAR_TODOS:
			client_lista_todos();
			break;
		case REG_COMPLETO:
			client_reg_completo();
			break;
		case REG_SINOPSE:
			client_reg_sinopse();
			break;
		case REG_MEDIA:
			client_reg_media();
			break;
		case REG_AVALIAR:
			client_reg_avalia();
			break;

		default:
			/* teoricamente, nunca é pra entrar aqui, pois c já
			 foi filtrado em read_option */
			c = read_option();
			break;
		}

		c = read_option();
	}
	
	return(0);

}
