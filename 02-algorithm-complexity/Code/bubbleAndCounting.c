#include <stdio.h>
#include <stdlib.h>
#include "headerFile.h"
#include <time.h>
#include <stdbool.h>

void fillingAnArray(int array[], size_t arrayLength) {
    srand(time(NULL));
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = rand() % 100;
    }
}

void bubbleSort(int array[], size_t arrayLength) {
    while (arrayLength > 1) {
        for (int i = 0; i < arrayLength - 1; ++i) {
            if (array[i] > array[i + 1]) {
                swap(&array[i + 1], &array[i]);
            }
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
    int *arrayToCount = calloc(abs(minValue) + abs(maxValue), sizeof(int));
    if (arrayToCount == NULL) {
        return;
    }
    for (int i = 0; i < arrayLength; ++i) {
        ++arrayToCount[array[i] - 1];
    }
    for (int i = 0; i < abs(minValue) + abs(maxValue); ++i) {
        if (arrayToCount[i] != 0) {
            int j = 0;
            while (arrayToCount[i] != 0) {
                array[j] = i;
                ++j;
                --arrayToCount[i];
            }
        }
    }
}

bool checkForSorting(int array[], int arrayLength) {
    for (int i = 0; i < 19; ++i) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}


bool testBubbleSort() {
    int testArray[20] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    bubbleSort(testArray, 20);
    bool test1 = checkForSorting(testArray, 20);
    return test1;
}

bool testCountingSort() {
    int testArray[20] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    countingSort(testArray, 20);
    bool test1 = checkForSorting(testArray, 20);
    return test1;
}

void bubbleAndCountingTask() {
    if (!testBubbleSort()) {
        printf("Bubble sorting test failed");
        return;
    }

    if (!testCountingSort()) {
        printf("Counting sorting test failed");
        return;
    }

    size_t arrayLength = 10000;
    int *arrayForBubble = (int *)malloc(arrayLength * sizeof(int));

    if (arrayForBubble == NULL) {
        printf("Memory allocation error\n");
        return;
    }

    fillingAnArray(arrayForBubble, arrayLength);

    clock_t startBubbleSort = clock();
    bubbleSort(arrayForBubble, arrayLength);
    clock_t endBubbleSort = clock();

    double timeSpentBubbleSorting = (double)(endBubbleSort - startBubbleSort) / CLOCKS_PER_SEC;

    free(arrayForBubble);
    int *arrayForCounting = malloc(arrayLength * sizeof(int));
    if (arrayForCounting == NULL) {
        printf("Memory allocation error\n");
        return;
    }

    fillingAnArray(arrayForCounting, arrayLength);

    clock_t startCountingSort = clock();
    countingSort(arrayForCounting, arrayLength);
    clock_t endCountingSort = clock();
    double timeSpentCountingSort = (double)(endCountingSort - startCountingSort) / CLOCKS_PER_SEC;

    free(arrayForCounting);
    printf("Time taken for bubble sorting: %f seconds", timeSpentBubbleSorting);
    printf("\nTime taken for counting sorting: %f seconds\n", timeSpentCountingSort);
}