#include <stdio.h>
#include <stdbool.h>

#include "postfixCalculator.h"

bool testCalculate(bool* errorCode) {
    int test1 = calculate("9 6 - 1 2 + *", errorCode);
    int test2 = calculate("17 10 + 3 * 9 /", errorCode);
    return test1 == 9 && test2 == 9;
}