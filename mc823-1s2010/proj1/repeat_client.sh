#!/bin/bash

for i in $(seq 100)
do
    ./client 143.106.150.80 < arq.in 2>> tempos.out
done
