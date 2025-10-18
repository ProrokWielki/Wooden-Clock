#!/bin/sh

if [[ $# -ne 1 ]]; then 
    printf "\nUsage: $0 DIR\n\nDIR: build directory with compile_commands.json in it\n"
    exit 2
fi

while getopts "h?:" opt; do
    case "$opt" in
    h|\?)
        printf "\nUsage: $0 DIR\n\nDIR: build directory with compile_commands.json in it\n"
        exit 0
        ;;
    esac
done

cat $1/compile_commands.json | grep file | grep -v MCU | grep -v build | grep -v tests | grep -v lib |  awk -F '"' '{print $4}' | xargs clang-tidy -p $1 