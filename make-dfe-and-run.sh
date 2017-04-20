#!/bin/bash

#DF="Simulation"
DF="DFE"
DEBUG=""
make_and_run() {
  cd "./$1/RunRules/$DF"
  echo "Make on ./$1/RunRules/$DF"
  make
  cd ../../../bench
  echo "Bench on ./$1/RunRules/$DF"
  ./bench.sh "$DEBUG" "$2" "../$1/RunRules/$DF/binaries/$1"
}


(
make_and_run "MultiSparseReal" dfemul 
)

(
make_and_run "MultiSparseComplex" dfemul 
)

