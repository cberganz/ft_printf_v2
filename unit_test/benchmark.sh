#!/bin/bash

loop1=20
loop2=10000

printf "\n\nOld vs New vs libc.. Printing $((loop1 * loop2)) char\n\n"

printf "Old version: \n"
make -sC ../old
gcc benchmark.c -I../old -L../old -lftprintf
/usr/bin/time -f "\n%E real | %U user | %S sys | %P cpu" ./loop.sh loop1 loop2

echo

printf "New version: \n"
make -sC ../new
gcc benchmark.c -I../new/include -L../new -lftprintf
/usr/bin/time -f "\n%E real | %U user | %S sys | %P cpu" ./loop.sh loop1 loop2

echo

printf "Libc version: \n"
gcc -D PRINTF=1 -I../new/include benchmark.c
/usr/bin/time -f "\n%E real | %U user | %S sys | %P cpu" ./loop.sh loop1 loop2

echo

rm a.out
