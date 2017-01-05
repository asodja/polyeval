#!/bin/bash

MYNAME=$(basename "$0")
BENCH_MAX="536870912"

help() {
cat <<EOF
Example usage: $MYNAME cpusin ../SingleSparseReal

TARGETS:
  * cpusin <path to executable>     Runs single point cpu bench
  * dfesin <path to executable>     Runs single point dfe bench
  * cpumul <path to executable>     Runs multi point cpu bench
  * dfemul <path to executable>     Runs multi point dfe bench

OPTIONS:
  -d --debug   Run debug with small number of inputs
  -h --help    Prints this help

EOF
}

fail() {
  echo "$@"
  exit 1
}

run() {
  local target="$1"
  shift
  test -z "$target" && target="invalid"
  local func_name="target_${target}"
  ${func_name} "$@" || fail "Error running target: $target"
}

single_bench() {
  local type="$1"
  local exe="$2"
  test -z "$exe" && fail "No executable given"
  local filename="$(basename "$exe")"
  local logfile="${filename%.*}-$type.log"
  echo "Running $exe, log is written to $logfile"
  for (( n=16; n <= BENCH_MAX; n=n*2 )); do
    $exe -n "$n" >> $logfile 2>&1
    sleep 2
  done
}

multi_bench() {
  local type="$1"
  local exe="$2"
  test -z "$exe" && fail "No executable given"
  local filename="$(basename "$exe")"
  local logfile="${filename%.*}-$type.log"
  echo "Running $exe, log is written to $logfile"
  for n in 16 32 128 256 512 1024; do
	for m in 16 128 1024 4096 16384 65536 262144 1048576 4194304 8388608 16777216 33554432 67108864; do
		$exe -n "$n" -m "$m" >> $logfile 2>&1
    		sleep 2
	done
  done
}

target_cpusin() {
  single_bench "cpu" "$@"
}

target_dfesin() {
  single_bench "dfe" "$@"
}

target_cpumul() {
  multi_bench "cpu" "$@"
}

target_dfemul() {
  multi_bench "dfe" "$@"
}


if [ "$1" = "-d" -o "$1" = "--debug" ]; then
  BENCH_MAX="131072"
  shift
fi

if [ "$1" = "-h" -o "$1" = "--help" ]; then
  help
  exit 0
fi

run "$@"




