#!/bin/bash

loop1=20
loop2=10000
path="unit_test/benchmark/"

printf "\n\nOld vs New vs libc.. Printing $((loop1 * loop2 * 1000)) char\n\n"

printf "New version: \n"
make re -sC ./
gcc ${path}benchmark.c -I./include/ -L. -lftprintf
/usr/bin/time -f "\n%E real | %U user | %S sys | mem %K | %p" ${path}loop.sh "/dev/null"

printf "\nLibc version: \n"
gcc -D PRINTF=1 -I./include/ ${path}benchmark.c
/usr/bin/time -f "\n%E real | %U user | %S sys" ${path}loop.sh "/dev/null"

printf "\nOld version: \n"
make -sC ${path}old
gcc ${path}benchmark.c -I./include/ -L${path} -loldftprintf
/usr/bin/time -f "\n%E real | %U user | %S sys" ${path}loop.sh "/dev/null"

echo

rm a.out
