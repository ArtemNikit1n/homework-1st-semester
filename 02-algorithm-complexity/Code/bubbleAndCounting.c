#include <stdio.h>
#include <stdlib.h>
#include "headerFile.h"
#include <time.h>
#include <stdbool.h>

#define ARRAY_LENGTH 100000

void fillingAnArray(int array[], size_t arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        if (i % 5 == 0) {
            array[i] = (rand() % 100) * -1;
            continue;
        }
        array[i] = rand() % 100;
    }
}

void bubbleSort(int array[], size_t arrayLength) {
    bool swapWorked = false;
    while (arrayLength > 1) {
        for (int i = 0; i < arrayLength - 1; ++i) {
            if (array[i] > array[i + 1]) {
                swap(&array[i + 1], &array[i]);
                swapWorked = true;
            }
        }
        if (!swapWorked) {
            break;
        }
        --arrayLength;
    }
}


int min(int firstNumber, int secondNumber) {
    return (firstNumber > secondNumber) ? secondNumber : firstNumber;
}

int max(int firstNumber, int secondNumber) {
    return (firstNumber < secondNumber) ? secondNumber : firstNumber;
}

void countingSort(int array[], size_t arrayLength) {
    int minValue = INT_MAX;
    int maxValue = INT_MIN;
    for (int i = 0; i < arrayLength; ++i) {
        if (array[i] < minValue) {
            minValue = min(minValue, array[i]);
            maxValue = max(maxValue, array[i]);
        }
    }
    int* arrayToCount = calloc(abs(minValue) + abs(maxValue) + 1, sizeof(int));
    if (arrayToCount == NULL) {
        return;
    }
    for (int i = 0; i < arrayLength; ++i) {
        ++arrayToCount[array[i] + abs(minValue)];
    }
    int j = 0;
    for (int i = 0; i < abs(minValue) + abs(maxValue) + 1; ++i) {
        if (arrayToCount[i] != 0) {
            while (arrayToCount[i] != 0) {
                array[j] = i - abs(minValue);
                ++j;
                --arrayToCount[i];
            }
        }
    }
}

bool checkTheSortingInAscendingOrder(const int array[], int arrayLength) {
    for (int i = 0; i < arrayLength - 1; ++i) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

bool testBubbleSort() {
    int testArray[20] = {20, 20, 18, -17, 16, 15, 14, 13, -12, 11, 10, 9, 8, -7, 6, 5, 4, 3, -2, 1};
    bubbleSort(testArray, 20);
    bool test1 = checkTheSortingInAscendingOrder(testArray, 20);
    return test1;
}

bool testCountingSort() {
    int testArray[20] = {20, 19, 18, 17, 16, 16, 14, 13, 12, 11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1};
    countingSort(testArray, 20);
    bool test1 = checkTheSortingInAscendingOrder(testArray, 20);
    return test1;
}

void bubbleAndCountingTask() {
    srand(time(NULL));

    if (!testBubbleSort()) {
        printf("Bubble sorting test failed");
        return;
    }

    if (!testCountingSort()) {
        printf("Counting sorting test failed");
        return;
    }

    int arrayForBubble[ARRAY_LENGTH] = {0};

    fillingAnArray(arrayForBubble, ARRAY_LENGTH);

    clock_t startBubbleSort = clock();
    bubbleSort(arrayForBubble, ARRAY_LENGTH);
    clock_t endBubbleSort = clock();

    double timeSpentBubbleSorting = (double)(endBubbleSort - startBubbleSort) / CLOCKS_PER_SEC;
    printf("Time taken for bubble sorting: %f seconds", timeSpentBubbleSorting);

    int arrayForCounting[ARRAY_LENGTH] = {0};

    fillingAnArray(arrayForCounting, ARRAY_LENGTH);

    clock_t startCountingSort = clock();
    countingSort(arrayForCounting, ARRAY_LENGTH);
    clock_t endCountingSort = clock();

    double timeSpentCountingSort = (double)(endCountingSort - startCountingSort) / CLOCKS_PER_SEC;
    printf("\nTime taken for counting sorting: %f seconds\n", timeSpentCountingSort);
}