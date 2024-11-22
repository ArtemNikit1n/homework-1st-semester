#include <stdio.h>
#include <stdbool.h>

#include "advancedBracketBalance.h"

bool testAdvancedBracketBalance(bool *errorCode) {
    bool test1 = checkBracketBalance("102938", errorCode);
    bool test2 = checkBracketBalance("([{}])()[{}]", errorCode);
    bool test3 = !checkBracketBalance("([)]{}", errorCode);
    bool test4 = checkBracketBalance("{{{123}}}(2[])", errorCode);
    if (*errorCode) {
        return false;
    }
    return test1 && test2 && test3 && test4;
}