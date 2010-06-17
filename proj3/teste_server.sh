#!/bin/bash

OUT=tempos.server

# limpa o arquivo com os tempos antigos
rm $OUT

./runserver.sh 2>> $OUT
