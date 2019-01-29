#!/bin/bash

clear

#Fib
echo "Compile and time fibonacci -O0"
time gcc fibonacci.c -o fibonacci_O0 -std=c11 -O0 -lgmp
echo "fibonacci_O0"
time ./fibonacci_O0

echo "Compile and time fibonacci -O1"
time gcc fibonacci.c -o fibonacci_O1 -std=c11 -O1 -lgmp
echo "fibonacci_O1"
time ./fibonacci_O1

echo "Compile and time fibonacci -O2"
time gcc fibonacci.c -o fibonacci_O2 -std=c11 -O2 -lgmp
echo "fibonacci_O2"
time ./fibonacci_O2

echo "Compile and time fibonacci -O3"
time gcc fibonacci.c -o fibonacci_O3 -std=c11 -O3 -lgmp
echo "fibonacci_O3"
time ./fibonacci_O3

echo "Compile and time fibonacci -Os"
time gcc fibonacci.c -o fibonacci_Os -std=c11 -Os -lgmp
echo "fibonacci_Os"
time ./fibonacci_Os

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

echo "Compile and time Blister_1 -Os"
time gcc Blister_1.c -o Blister_1_Os -std=c11 -Os
echo "Time Blister_1_Os"
time ./Blister_1_Os

#blister 2
echo "Compile and time Blister_2 -O0"
time gcc Blister_2.c -o Blister_2_O0 -std=c11 -O0
echo "Time Blister_2_O0"
time ./Blister_2_O0

echo "Compile and time Blister_2 -O1"
time gcc Blister_2.c -o Blister_2_O1 -std=c11 -O1
echo "Time Blister_2_O1"
time ./Blister_2_O1

echo "Compile and time Blister_2 -O2"
time gcc Blister_2.c -o Blister_2_O2 -std=c11 -O2
echo "Time Blister_2_O2"
time ./Blister_2_O2

echo "Compile and time Blister_2 -O3"
time gcc Blister_2.c -o Blister_2_O3 -std=c11 -O3
echo "Time Blister_2_O3"
time ./Blister_2_O3

exit 1
