#include <stdio.h>
#include <stdbool.h>

#include "userInput.h"

bool testCheckingUserInput() {
    bool test1 = checkingUserInput("325423+ -*/");
    bool test2 = checkingUserInput("1283981fre+_=");

    return test1 && !test2;
}