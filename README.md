# Polynomial evaluation on data-flow computers
This code was used to test my solutions of polynomial algorithms for my Master Thesis with title *Polynomial evaluation on data-flow computers*. It is written for [Maxeler Dataflow](https://www.maxeler.com/technology/dataflow-computing).

A lot of tests were done for same algorithms, so there are some duplicated algorithms but with different paralelism. This was done for easier testing.

Test names consist of type of polynomial that they are written for and paralelism level. For example *VecMultiDenseComplex64* tests algorithm for multi-point dense complex polynomial with paralelism of 64 (this number is size of Maxeler Dataflow vector that is used). *VecMultiDenseComplex8* is same algorithm but with paralelism of 8.

# Structure of project
* Tests are in folders with name like *VecMultiDenseComplex64* - one test folder contains code for that tests
* Common code folder *common* where all common code is
* Cpu solutions are in *cpu* folder
* Bench folder *bench* where simple bench script is and where results logs are written
* Script to do all make and run CPU steps *make-cpu-and-run.sh* script

# Example how to run tests on Maxeler Dataflow
#### Clone
- git clone git@github.com:asodja/polyeval.git
- cd ./polyeval

#### Make and run CPU
- cd ./cpu && make
- cd ../bench && ./bench.sh cpumul "../cpu/MultiDenseReal"


#### Alternative Make and run CPU Automatically
./make-cpu-and-run.sh

#### DFE (use correct RUNRULE)
- cd VecMultiDenseReal4/RunRules/DFE && make
- cd VecMultiDenseReal8/RunRules/DFE && make
- cd VecMultiDenseReal16/RunRules/DFE && make

- cd ../../../bench
- ./bench.sh dfemul "../VecMultiDenseReal4/RunRules/DFE/binaries/VecMultiDenseReal4" 
- ./bench.sh dfemul "../VecMultiDenseReal8/RunRules/DFE/binaries/VecMultiDenseReal8" 
- ./bench.sh dfemul "../VecMultiDenseReal16/RunRules/DFE/binaries/VecMultiDenseReal16" 



