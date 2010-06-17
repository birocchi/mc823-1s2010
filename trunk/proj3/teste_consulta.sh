#!/bin/bash

# $# - número de parametros 
if [ $# -ne 1 ]
then
    echo "uso: ./teste_consulta.sh <endereço_servidor>"
    exit 1
fi

OUT=tempos.query

# limpa o arquivo com os tempos antigos
rm $OUT

./runclient.sh $1 2>> $OUT

clear

# lembrete pra quando for rodar o teste
echo "$OUT gerado"
echo "Lembrete da condição:"
echo "(Client.java) boolean TEST = true;"

