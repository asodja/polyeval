# Clone
git clone …/polyeval
cd polyeval

# Make and run CPU
cd cpu
make
cd ..
cd bench
./bench.sh cpumul ../cpu/MultiSparseReal
./bench.sh cpumul ../cpu/MultiSparseComplex

# Alternative Make and run CPU Automatically (script with all upper commands)
cd polyeval
./make-cpu-and-run.sh

# DF use correct RUNRULE
cd MultiSparseReal/RunRules/DFE
make
cd MultiSparseComplex/RunRules/DFE
make

cd ../../../bench
./bench.sh dfemul "../MultiSparseReal/RunRules/DFE/binaries/MultiSparseReal" 
./bench.sh dfemul "../MultiSparseComplex/RunRules/DFE/binaries/MultiSparseComplex" 

# Alternative Make and run DFE Automatically (script with all upper commands)
cd polyeval
./make-dfe-and-run.sh

