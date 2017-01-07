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
cd VecMultiDenseReal4/RunRules/DFE
make
cd VecMultiDenseReal8/RunRules/DFE
make
cd VecMultiDenseReal16/RunRules/DFE
make

cd ../../../bench
./bench.sh dfemul "../VecMultiDenseReal4/RunRules/DFE/binaries/VecMultiDenseReal4" 
./bench.sh dfemul "../VecMultiDenseReal8/RunRules/DFE/binaries/VecMultiDenseReal8" 
./bench.sh dfemul "../VecMultiDenseReal16/RunRules/DFE/binaries/VecMultiDenseReal16" 


