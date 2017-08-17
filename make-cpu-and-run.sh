#!/bin/bash

cd cpu
echo "In ./cpu"
make
echo "Make done"
cd ..
cd bench
echo "In ./bench"
echo "Will run, be ready!"
./bench.sh cpukm "../cpu/KMeans"
./bench.sh cpumul "../cpu/MultiDenseComplex"
./bench.sh cpumul "../cpu/MultiSparseComplex"
./bench.sh cpudft "../cpu/DFT"
echo "Done"
