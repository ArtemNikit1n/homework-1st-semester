#include <stdio.h>
#include <stdbool.h>

#include "workingWithAFile.h"
#include "testsWorkingWithAFile.h"

struct TestStruct {
    char* name;
    char* phone;
};

bool testSearchByPhone() {
    struct TestStruct* testStruct;
    char name[6] = "Artem";
    char phone[11] = "89004325486";

    testStruct->name = name;
    testStruct->phone = phone;

    return searchByPhone(testStruct, phone);
}

bool testSearchByName() {
    struct TestStruct* testStruct;
    char name[6] = "Artem";
    char phone[11] = "89004325486";

    testStruct->name = name;
    testStruct->phone = phone;

    return searchByName(testStruct, name);
}