#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "workingWithAFile.h"

struct testStruct {
    char names[MAX_ENTRIES][MAX_RECORD_LENGTH];
    char phones[MAX_ENTRIES][MAX_RECORD_LENGTH];
    int numberOfEntries;
};

bool testSearchByPhone(void) {
    const char* name = "Artem";
    const char* phone = "89004325486";

    struct testStruct testStruct = { .numberOfEntries = 1 };

    strcpy(testStruct.names[0], name);
    strcpy(testStruct.phones[0], phone);

    return strcmp(searchByPhone(&testStruct, phone), name) == 0;
}

bool testSearchByName(void) {
    const char* name = "Artem";
    const char* phone = "89004325486";

    struct testStruct testStruct = { .numberOfEntries = 1 };

    strcpy(testStruct.names[0], name);
    strcpy(testStruct.phones[0], phone);

    return strcmp(searchByName(&testStruct, name), phone) == 0;
}