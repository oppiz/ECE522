#!/bin/bash

#Fib
echo "Compile and time fibonacci -O2"
time gcc fibonacci.c -o fibonacci_O2 -std=c11 -O2 -lgmp
echo "fibonacci_O2"
#time ./fibonacci_O2

#Blister1
echo "Compile and time Blister_1 -O0"
time gcc Blister_1.c -o Blister_1_O0 -std=c11 -O0
echo "Time Blister_1_O0"
time ./Blister_1_O0

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

echo "Compile and time Blister_Multi -O0"
time gcc Blister_1_Multithread.c -o Blister_Multi -std=c11 -O0
echo "Time Blister_Multi"
time ./Blister_Multi

echo "Compile and time Blister_1 -Os"
time gcc Blister_1.c -o Blister_1_Os -std=c11 -Os
echo "Time Blister_1_Os"
time ./Blister_1_Os

echo "Compile and time Blister -O3"
time gcc Blister_2.c -o Blister_2 -std=c11 -O3
echo "Time Blister_2"
time ./Blister_2

exit 1
