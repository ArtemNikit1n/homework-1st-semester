#include <stdlib.h>
#include <stdbool.h>

#include "mergeSort.h"
#include "../list/list.h"

void merge(List* list, Position left, Position middle, Position right, bool* errorCode) {
    List* result = createList(errorCode);
    Position i = first(result, errorCode);
    if (*errorCode) {
        return;
    }
    Position saveLeft = left;
    Position saveMiddle = middle;

    while (left != saveMiddle && middle != right) {
        if (getValue(left, errorCode) - getValue(middle, errorCode) < 0) {
            add(result, i, getValue(left, errorCode), errorCode);
            i = next(i, errorCode);
            left = next(left, errorCode);
            if (*errorCode) {
                return;
            }
        } else {
            add(result, i, getValue(middle, errorCode), errorCode);
            i = next(i, errorCode);
            middle = next(middle, errorCode);
            if (*errorCode) {
                return;
            }
        }
    }

    while (left != saveMiddle) {
        add(result, i, getValue(left, errorCode), errorCode);
        i = next(i, errorCode);
        left = next(left, errorCode);
        if (*errorCode) {
            return;
        }
    }

    while (middle != right) {
        add(result, i, getValue(middle, errorCode), errorCode);
        i = next(i, errorCode);
        middle = next(middle, errorCode);
        if (*errorCode) {
            return;
        }
    }

    i = next(first(result, errorCode), errorCode);
    if (*errorCode) {
        return;
    }
    left = saveLeft;
    for (Position j = left; j != NULL && i != NULL; j = next(j, errorCode)) {
        if (*errorCode) {
            return;
        }
        setValue(j, getValue(i, errorCode), errorCode);
        if (*errorCode) {
            return;
        }
        i = next(i, errorCode);
    }
}

Position calculateTheMiddle(List* list, Position left, Position right, bool* errorCode) {
    int middle = 0;
    Position i = left;
    while (i != NULL) {
        if (i == right) {
            break;
        }
        i = next(i, errorCode);
        ++middle;
    }
    i = left;

    int j = 0;
    while (j < (int)(middle / 2)) {
        i = next(i, errorCode);
        ++j;
    }
    return i;
}

void sortByMerging(List* list, Position left, Position right, bool* errorCode) {
    if (next(left, errorCode) == right) { 
        return;
    }
    Position saveRight = right;
    for (Position i = right; i != NULL; i = next(i, errorCode)) {
        if (*errorCode) {
            return;
        }
        if (i == left) {
            right = saveRight;
            return;
        }
    }
    right = saveRight;

    Position middle = calculateTheMiddle(list, left, right, errorCode);
    if (*errorCode) {
        return;
    }
    sortByMerging(list, left, middle, errorCode);
    if (*errorCode) {
        return;
    }
    sortByMerging(list, middle, right, errorCode);
    if (*errorCode) {
        return;
    }
    merge(list, left, middle, right, errorCode);
}