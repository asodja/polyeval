#!/bin/bash

EXE=$1
filename=$(basename "$EXE")
filename="${filename%.*}"

logfile="$filename.txt"

for n in 32 512 8192 131072 2097152 33554432 536870912; do
  $EXE -n "$n" >> $logfile 2>&1
done
