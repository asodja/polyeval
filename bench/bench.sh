#!/bin/bash

MYNAME=$(basename "$0")

help() {
cat <<EOF
Example usage: $MYNAME cpu ../SingleSparseReal

TARGETS:
  * cpu <path to executable>     Runs cpu bench
  * dfe <path to executable>     Runs dfe bench

OPTIONS:
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

bench() {
  local type="$1"
  local exe="$2"
  test -z "$exe" && fail "No executable given"
  local filename="$(basename "$exe")"
  local logfile="${filename%.*}-$type.log"
  echo "Running $exe, log is written to $logfile"
  for n in 32 512 8192 131072 2097152 33554432 536870912; do
    $exe -n "$n" >> $logfile 2>&1
  done
}

target_cpu() {
  bench "cpu" "$@"
}

target_dfe() {
  bench "dfe" "$@"
}

if [ "$1" = "-h" -o "$1" = "--help" ]; then
  help
  exit 0
fi

run "$@"




