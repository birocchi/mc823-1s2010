#!/bin/bash

for i in $(seq 100)
do
    ./client localhost < arq.in 2>> tempos.out
done
