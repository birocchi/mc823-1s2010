#!/bin/bash

if [ $# == 0 ]
then
    echo "Uso: ./runserver.sh <arquivo do banco>"
    exit 1
fi

ROOT=$(pwd) #/home/ec2007/..../mc823-1s2010/proj3
CLASSPATH=$CLASSPATH:$ROOT/sqlitejdbc-v056.jar

cd bin

# executa o servidor passando como parâmetro o arquivo do BD
java Servidor $ROOT/$1
