#!/bin/bash

ROOTDIR=$(pwd) #/home/ec2007/..../mc823-1s2010/proj3
CLASSPATH=$CLASSPATH:$ROOTDIR/sqlitejdbc-v056.jar

cd bin

# executa o servidor passando como parâmetro o arquivo do BD
java -Djava.security.policy=$ROOTDIR/policy Servidor $ROOTDIR/filmes.db