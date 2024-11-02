#include <stdio.h>
#include <stdbool.h>

#include "userInput.h"

bool testCheckingUserInput() {
    bool test1 = checkingUserInput("3254(23+) -*/");
    bool test2 = checkingUserInput("1283981fre+_=");

    return test1 && !test2;
}

bool testCheckingTheBalanceOfBrackets() {
    bool test1 = checkingTheBalanceOfBrackets("(()!2())");
    bool test2 = checkingTheBalanceOfBrackets("(()!2()(((((()");
    bool test3 = checkingTheBalanceOfBrackets("\0");
    bool test4 = checkingTheBalanceOfBrackets("");
    bool test5 = checkingTheBalanceOfBrackets("erigtre2412");

    return test1 && !test2 && test3 && test4 && test5;
}