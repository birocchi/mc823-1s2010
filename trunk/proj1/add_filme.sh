#!/bin/bash

echo "Cadastro de novo filme!"
echo -n "Id: "; read id
echo -n "Titulo: "; read titulo
echo -n "Sinopse: "; read sinopse
echo -n "Sala: "; read sala
echo -n "Horários: "; read horarios

tam_substr=$(echo -n $id\@0000\@000000\@$titulo\@$sinopse\@$sala\@$horarios\@ | wc -c)

# tam_reg deve ser tam_substr + 3~4 (digitos+@)
tam_reg=$(echo -n $tam_substr\@$id\@0000\@000000\@$titulo\@$sinopse\@$sala\@$horarios\@ | wc -c)

# expressão regular ^10*$ casa com qq seq começando com 1 seguida de zeros
if [ $tam_reg = $(echo $tam_reg | grep ^10*$) ]
then
		echo 'Entrou no caso da exceção da virada 10/100/1000'
		tam_reg=$((tam_reg + 1))
else
		echo 'Não entrou na exceção.'
fi

# finalmente, manda os valores para o arquivo
echo -n $tam_reg\@$id\@0000\@000000\@$titulo\@$sinopse\@$sala\@$horarios\@ >> filmes.dat

echo "Registro adicionado com sucesso!"