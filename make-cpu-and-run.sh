#!/bin/bash

cd cpu
echo "In ./cpu"
make
echo "Make done"
cd ..
cd bench
echo "In ./bench"
echo "Will run, be ready!"
./bench.sh cpusin "../cpu/FastSingleSparseReal"
./bench.sh cpusin "../cpu/SingleSparseReal"
echo "Done"
