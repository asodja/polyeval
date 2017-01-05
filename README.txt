# Clone
git clone …/polyeval
cd polyeval

# Make and run CPU
cd cpu
make
cd ..
cd bench
./bench.sh cpumul ../cpu/MultiDenseReal

# Alternative Make and run CPU Automatically (script with all upper commands)
cd polyeval
./make-cpu-and-run.sh

# DF use correct RUNRULE
cd VecMultiDenseReal16/RunRules/DFE
make
cd VecMultiDenseReal32/RunRules/DFE
make
cd VecMultiDenseReal48/RunRules/DFE
make

cd ../../../bench
./bench.sh dfemul "../VecMultiDenseReal16/RunRules/DFE/binaries/VecMultiDenseReal16" 
./bench.sh dfemul "../VecMultiDenseReal64/RunRules/DFE/binaries/VecMultiDenseReal32" 
./bench.sh dfemul "../VecMultiDenseReal128/RunRules/DFE/binaries/VecMultiDenseReal48" 


