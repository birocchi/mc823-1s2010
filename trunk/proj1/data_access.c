#include "data_access.h"

int da_str_to_filme (filme *f_ret, char *f_str) {
	/* Entrada: string crua lida do arquivo, referente a um registro */
	/* Saída: - setup da struct filme passada por referência 
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





	return(0);
}


int main() {
	return(0);
}
