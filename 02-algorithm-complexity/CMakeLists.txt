cmake_minimum_required(VERSION 3.29)
project(AlgorithmComplexity C)

set(CMAKE_C_STANDARD 11)

add_executable(AlgorithmComplexity
        Code/halfQsort.c
        Code/headerFile.h
        Code/main.c
        Code/bubbleAndCounting.c
        Code/exponentiation.c
        Code/fibonacciNumbers.c
)
