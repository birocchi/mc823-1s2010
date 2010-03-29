#include<stdio.h>

#define SAIR 's'
#define BLA 'b'
#define FOO 'f'


char read_option() {
	/* considera os possiveis erros e só sai quando o usuario
	 digitar um caractere válido */

	/* TODO */

	return('s');
}

void bla() {
	return;
}

void foo() {
	return;
}

int main() {

	char c;

	c = read_option(); 

	while(c != SAIR) {

		switch(c) {

		case BLA:
			/* faça BLA */
			bla();
			break;
		case FOO:
			/* faça FOO */
			foo();
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
