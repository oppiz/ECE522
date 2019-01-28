#!/bin/bash

clear
echo "Compile and time Blister_1 -O0"
time gcc Blister_1.c -o Blister_1_O0 -std=c11 -O0
echo "Time Blister_1_O0"
time ./Blister_1

echo "Compile and time Blister_1 -O1"
time gcc Blister_1.c -o Blister_1_O1 -std=c11 -O1
echo "Time Blister_1_O1"
time ./Blister_1_O1

echo "Compile and time Blister_1 -O2"
time gcc Blister_1.c -o Blister_1_O2 -std=c11 -O2
echo "Time Blister_1_O2"
time ./Blister_1_O2

echo "Compile and time Blister_1 -O3"
time gcc Blister_1.c -o Blister_1_O3 -std=c11 -O3
echo "Time Blister_1_O3"
time ./Blister_1_O3

echo "Compile and time Blister_1 -Os"
time gcc Blister_1.c -o Blister_1_Os -std=c11 -Os
echo "Time Blister_1_Os"
time ./Blister_1_Os

exit 1
