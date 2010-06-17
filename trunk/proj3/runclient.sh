#!/bin/bash

cd bin

# $# - número de parametros 
if [ $# -ne 1 ]
then
    echo "uso: ./runclient.sh <endereço_servidor>"
    exit 1
fi

# $1 - endereço do servidor
java -Djava.security.policy=../policy Cliente $1
