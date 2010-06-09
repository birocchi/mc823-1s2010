#!/bin/bash

if [ $# == 0 ]
then
    echo "Uso: ./runserver.sh <arquivo do banco>"
    exit 1
fi

CLASSPATH=$CLASSPATH:./sqlitejdbc-v056.jar
FULLPATH=$(pwd)

cd bin

# executa o servidor passando como parâmetro o arquivo do BD
java Servidor $FULLPATH/$1
