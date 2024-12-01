#include <stdio.h>
#include <stdbool.h>
#include "headerFile.h"
#include "time.h"

long long fibonacciRecursively(int fibonacciIndex) {
    if (fibonacciIndex == 1) {
        return 1;
    }
    if (fibonacciIndex <= 0) {
        return 0;
    }
    return fibonacciRecursively(fibonacciIndex - 1) + fibonacciRecursively(fibonacciIndex - 2);
}

long long fibonacciIteratively(int fibonacciIndex) {
    if (fibonacciIndex < 0) {
        return -1;
    }
    long long fibonacciNumbers[2] = {1, 0};

    int i = 0;
    while (i < fibonacciIndex) {
        long long theLastNumber = fibonacciNumbers[1];
        fibonacciNumbers[1] = fibonacciNumbers[0] + fibonacciNumbers[1];
        fibonacciNumbers[0] = theLastNumber;
        ++i;
    }
    return fibonacciNumbers[1];
}

bool testIterativeAlgorithm() {
    bool test1Iteratively = fibonacciIteratively(5) == 5;
    bool test2Iteratively = fibonacciIteratively(30) == 832040;
    bool test3Iteratively = fibonacciIteratively(60) == 1548008755920;
    bool test4Iteratively = fibonacciIteratively(0) == 0;
    bool test5Iteratively = fibonacciIteratively(1) == 1;


    return test1Iteratively && test2Iteratively && test3Iteratively && test4Iteratively && test5Iteratively;
}

bool testRecursiveAlgorithm() {
    bool test1Recursively = fibonacciRecursively(5) == 5;
    bool test2Recursively = fibonacciRecursively(30) == 832040;
    bool test3Recursively = fibonacciRecursively(0) == 0;
    bool test4Recursively = fibonacciRecursively(1) == 1;

    return test1Recursively && test2Recursively && test3Recursively && test4Recursively;
}

void fibonacciNumbersTask() {
    int fibonacciIndex = -1;

    if (!testIterativeAlgorithm() || !testRecursiveAlgorithm()) {
        printf("Tests failed\n");
        return;
    }

    printf("Enter how many times you want to calculate the fibonacci number:\n");
    if (scanf("%d", &fibonacciIndex) != 1) {
        printf("You didn't enter a number\n");
        return;
    }
    if (fibonacciIndex < 0) {
        printf("The number must be not negative\n");
        return;
    }

    clock_t startFibonacciIteratively = clock();
    printf("\nIterative algorithm: %lld\n", fibonacciIteratively(fibonacciIndex));
    clock_t stopFibonacciIteratively = clock();
    double timeSpentFibonacciIteratively = (double)(stopFibonacciIteratively - startFibonacciIteratively) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", timeSpentFibonacciIteratively);

    clock_t startFibonacciRecursively = clock();
    printf("Recursive algorithm: %lld\n", fibonacciRecursively(fibonacciIndex));
    clock_t stopFibonacciRecursively = clock();
    double timeSpentFibonacciRecursively = (double)(stopFibonacciRecursively - startFibonacciRecursively) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", timeSpentFibonacciRecursively);
}