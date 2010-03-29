#include<stdio.h>

#define SAIR 's'

char read_option() {
	/* considera os possiveis erros e só sai quando o usuario
	 digitar um caractere válido */

	/* TODO */

	return('s');
}

int main() {

	char c;

	c = read_option(); 

	while(c != SAIR) {
		/* cases... */

		c = read_option();
	}
	
	return(0);

}
