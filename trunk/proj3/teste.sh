#!/bin/bash

for i in $(seq 10)
do
  ./runclient.sh localhost < file.in 2>> tempos.time
done


