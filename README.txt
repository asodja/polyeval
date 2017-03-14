# Clone
git clone …/polyeval
cd polyeval

# Make and run CPU
cd cpu
make
cd ..
cd bench
./bench.sh cpu ../cpu/SingleSparseReal

# Alternative Make and run CPU Automatically (script with all upper commands)
cd polyeval
./make-cpu-and-run.sh

# DF use correct RUNRULE
cd SingleSparseReal/RunRules/DFE
make

cd ../../../bench
./bench.sh dfe "../SingleSparseReal/RunRules/DFE/binaries/DefaultApplication" 

