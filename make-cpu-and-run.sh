#!/bin/bash

cd cpu
echo "In ./cpu"
make
echo "Make done"
cd ..
cd bench
echo "In ./bench"
echo "Will run, be ready!"
#./bench.sh cpusin "../cpu/FastSingleSparseReal"
./bench.sh cpumul "../cpu/MultiDenseComplex"
./bench.sh cpumul "../cpu/MultiSparseReal"
./bench.sh cpumul "../cpu/MultiSparseComplex"
echo "Done"
