#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void swap(int* first, int* second) {
    if (*first == *second) {
        return;
    }
    *first ^= *second;
    *second ^= *first;
    *first ^= *second;
}

void insertionSort(int array[], int start, int stop) {
    for (int i = start + 1; i <= stop; ++i) {
        int indexSave = i;
        int insertableElement = array[i];
        while (array[i] < array[i - 1] && start < i) {
            swap(&array[i], &array[i - 1]);
            --i;
        }
        i = indexSave;
    }
}

int halfQSort(int array[], int startArray, int endArray) {
    int randomIndex = startArray + rand() % (endArray - startArray + 1);
    swap(&array[startArray], &array[randomIndex]);

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

void smartQSort(int array[], int start, int stop) {
    if (start < stop) {
        if (stop - start > 0) {
            int supportingIndex = halfQSort(array, start, stop);

            if (supportingIndex - 1 > start) {
                smartQSort(array, start, supportingIndex - 1);
            }
            if (supportingIndex + 1 < stop) {
                smartQSort(array, supportingIndex + 1, stop);
            }
        }
        if (stop - start <= 10) {
            insertionSort(array, start, stop);
        }
    }

}

void readingAnArrayOfNumbersFromAFile(int memoryForNumbers[], int *arrayLength, bool *errorCode) {
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        *errorCode = true;
        return;
    }

    int i = 0;
    while (fscanf(file, "%d", &memoryForNumbers[i]) == 1) {
        i++;
    }
    fclose(file);
    *arrayLength = i;
}
