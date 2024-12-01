#include <stdio.h>
#include "stdlib.h"
#include <stdbool.h>
#include <time.h>
#include <assert.h>

void swap(int *first, int *second)
{
    if (*first == *second) {
        return;
    }
    *first ^= *second;
    *second ^= *first;
    *first ^= *second;
}

int halfQSort(int array[], int startArray, int endArray) {
    int supportingElement = array[startArray];
    int leftPart = startArray + 1;

    for (int rightPart = startArray + 1; rightPart <= endArray; ++rightPart) {
        if (array[rightPart] < supportingElement) {
            swap(&array[leftPart], &array[rightPart]);
            ++leftPart;
        }
    }
    swap(&array[startArray], &array[leftPart - 1]);
    return leftPart - 1;
}

bool testCorrectSortingTask1() {
    int testArray[20] = {10, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int firstElement = testArray[0];
    const int arrayLength = 20;
    int i = 0;
    int indexFirstElement = halfQSort(testArray, 0, arrayLength - 1);

    for (int j = 0; j < arrayLength; ++j) {
        if (j < indexFirstElement && testArray[j] > firstElement) {
            return false;
        }
        if (j > indexFirstElement && testArray[j] < firstElement) {
            return false;
        }
    }
    return true;
}

void halfQsortTask() {
    if (!testCorrectSortingTask1()) {
        printf("Test failed");
        return;
    }

    srand(time(NULL));
    int arrayLength = 0;
    int arrayRand[100];

    printf("Enter the number of elements in the array (<100):\n");
    scanf("%d", &arrayLength);
    assert(arrayLength < 100 && arrayLength > 0);

    int firstElement = arrayRand[0];

    printf("Initial array:\n");
    for (int i = 0; i < arrayLength; ++i) {
        arrayRand[i] = rand();
        printf("%d ", arrayRand[i]);
    }

    halfQSort(arrayRand, 0, arrayLength - 1);

    printf("\nResult:\n");
    for (int i = 0; i < arrayLength; ++i) {
        printf("%d ", arrayRand[i]);
    }
}