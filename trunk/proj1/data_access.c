#include <stdio.h>
#include <stdlib.h>
#include "data_access.h"

int da_str_to_filme (filme *f_ret, int *tam_reg, char *f_str) {
	/* Entrada: string crua lida do arquivo, referente a um registro */
	/* Saída: - setup da struct filme passada por referência 
		        - tamanho do registro no arquivo
						- valor numérico para erros */
	

	/* Formato do registro no arquivo */
	/* Como há atributos de texto, é difícil manter os registros com tamanho constante no arq */
	/* Assim, uma ideia é usar separadores entre os atributos, assim como manter o tamanho do registro */
	/* 
		int tam_total_do_reg (incluindo todos os separadores do registro)
		int id, string titulo, string sinopse, string sala, string horarios
		Separador: @
		Ex: 75@1@Rei Leão@Filme assim assim assado@Kinoplex - sala 10@12h40, 15h, 17h20@
		(contando tudo, incluindo os caracteres de tam_total_do_reg e os separadores)

		Esse esquema do número de caracteres num campo é pra possibilitar a busca entre os registros.
	 */

	/*  Importante!
		 Essa função só faz o processamento (parse); ela considera que f_str é válida
		 e que a struct f_ret já tem memória alocada para as strings 
	*/

	char str[INT];
	char c;

	int i = 0; /* índice de acesso de f_str */
	int j = 0; /* indice para montagem da string  */

	/* tamanho do registro */
	while(f_str[i]!='@') {
		str[j] = f_str[i];
		i++; j++;
	}
	str[j] = '\0';
 	*tam_reg = atoi(str);

	/* id */
	i++; j = 0;
	while(f_str[i]!='@') {
		str[j] = f_str[i];
		i++; j++;
	}
	str[j] = '\0';
	(*f_ret).id = atoi(str);

	/* titulo */
	i++; j = 0;
	while(f_str[i]!='@') {
		(*f_ret).titulo[j] = f_str[i];
		i++; j++;
	}
	(*f_ret).titulo[j] = '\0';

	return(0);
}


int main() {

	filme f;

	char *teste;
	teste = "800@12@Rei Leão@";

	int tam_reg;

	if(da_str_to_filme(&f, &tam_reg, teste)==0) {
		printf("Tamanho do reg no arq: %d\n", tam_reg);
		printf("Id: %d\n", f.id);
		printf("Titulo: %s\n", f.titulo);
	}
	else {
		printf("Ocorreu algum problema...\n\n");
	}

	return(0);
}
