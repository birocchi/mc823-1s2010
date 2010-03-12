echo "Cadastro de novo filme!"
echo -n "Id: "; read id
echo -n "Titulo: "; read titulo
echo -n "Sinopse: "; read sinopse
echo -n "Sala: "; read sala
echo -n "Horários: "; read horarios

tam_substr=$(echo -n $id\@$titulo\@$sinopse\@$sala\@$horarios\@ | wc -c)

# tam_reg deve ser tam_substr + 3~4 (digitos+@)
tam_reg=$(echo -n $tam_substr\@$id\@$titulo\@$sinopse\@$sala\@$horarios\@ | wc -c)

# finalmente, manda os valores para o arquivo
echo -n $tam_reg\@$id\@$titulo\@$sinopse\@$sala\@$horarios\@ >> filmes.dat

echo "Registro adicionado com sucesso!"