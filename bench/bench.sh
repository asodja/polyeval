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
  for n in 32 512 8192; do
    $exe -n "$n" >> $logfile 2>&1
  done
}

target_cpu() {
  bench "cpu" "$@"
}

target_dfe() {
  bench "dfe" "$@"
}

TEMP=$(getopt -o h --long help -n "$MYNAME" -- "$@")
test "$?" != "0" && fail "Command line error"
eval set -- "$TEMP"
while true; do
  case $1 in
    -h|--help)
      help
      exit 0
      ;;
   --)
      shift
      break
      ;;
   *)
      fail "Invalid command: $1"
      ;;
  esac
done

run "$@"




