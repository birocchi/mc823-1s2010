#!/bin/bash

# $# - número de parametros 
if [ $# -ne 1 ]
then
    echo "uso: ./teste_conexao.sh <endereço_servidor>"
    exit 1
fi

OUT=tempos.rtt

# limpa o arquivo com os tempos antigos
rm $OUT

for i in $(seq 100)
do
  ./runclient.sh $1 <file.in 2>> $OUT
done

clear
echo "$OUT gerado"
echo "Lembrete da condição:"
echo "(Client.java) boolean TEST = false;"
