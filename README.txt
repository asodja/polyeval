# Clone
git clone …/polyeval
cd polyeval

# Make and run CPU
cd cpu
make
cd ..
cd bench
./bench.sh ../cpu/SingleSparseReal

# Alternative Make and run CPU Automatically (script with all upper commands)
cd polyeval
./make-cpu-and-run.sh

# DF use correct RUNRULE
cd SingleSparseReal/RunRules/…
make RUNRULE=…

cd bench
./bench.sh ../SingleSparseReal/RunRules/…

