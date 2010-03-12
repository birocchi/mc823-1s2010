#include <stdio.h>
#include <stdlib.h>
#include "data_access.h"

int da_str_to_filme (filme *f_ret, int *tam_reg, char *f_str) {
	/* Entrada: string crua lida do arquivo, a partir do início de um registro */
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

	char str[TAM_MAX_ATR]; /* string fixa bem grande pra comportar qq atributo */

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
		str[j] = f_str[i];
		i++; j++;
	}
	str[j] = '\0';
	/* aloca a string dinamicamente */
	(*f_ret).titulo = (char *)malloc(j*sizeof(char));
	sprintf((*f_ret).titulo, "%s", str);

	/* Blocos de código similares ao de cima, só que comprimidos  */
	/* sinopse */
	i++; j = 0;
	while(f_str[i]!='@') { str[j] = f_str[i];	i++; j++;	} str[j] = '\0';
	(*f_ret).sinopse = (char *)malloc(j*sizeof(char));
	sprintf((*f_ret).sinopse, "%s", str);

	/* sala */
	i++; j = 0;
	while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; } str[j] = '\0';
	(*f_ret).sala = (char *) malloc(j*sizeof(char));
	sprintf((*f_ret).sala, "%s", str);

	/* horarios */
	i++; j = 0;
	while(f_str[i]!='@') { str[j] = f_str[i]; i++; j++; } str[j] = '\0';
	(*f_ret).horarios = (char *) malloc(j*sizeof(char));
	sprintf((*f_ret).horarios, "%s", str);

	/* next - lembra dele? :) */
	(*f_ret).prox_filme = NULL;

	return(0);
}


void da_print_infos(filme *f) {
	printf("Id: %d\n", (*f).id);
	printf("Titulo: %s\n", (*f).titulo);
	printf("Sinopse: %s\n", (*f).sinopse);
	printf("Sala: %s\n", (*f).sala);
	printf("Horários: %s\n", (*f).horarios);
	return;
}

void da_free_strs(filme *f) {
	free((*f).titulo);
	free((*f).sinopse);
	free((*f).sala);
	free((*f).horarios);
	return;
}

int main() {

	filme f;

	char *teste;
	teste = "800@12@Rei Leão@Bla@Sala2@10h@";

	int tam_reg;

	if(da_str_to_filme(&f, &tam_reg, teste)==0) {
		printf("Tamanho do reg no arq: %d\n", tam_reg);
		da_print_infos(&f);
	}
	else {
		printf("Ocorreu algum problema...\n\n");
	}

	da_free_strs(&f);
	
	return(0);
}
