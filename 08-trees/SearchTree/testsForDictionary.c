#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"
#include "../Tree/tree.h"

bool testDictionary(bool* errorCode) {
    Node* root = createNode(createNodeValue(1, "a"), errorCode);
    addToTheDictionary(root, 5, "b", errorCode);
    addToTheDictionary(root, 3, "c", errorCode);
    addToTheDictionary(root, 10, "f", errorCode);
    addToTheDictionary(root, -5, "d", errorCode);
    addToTheDictionary(root, -3, "e", errorCode);

    if (*errorCode) {
        disposeNode(&root);
        return false;
    }

    bool test1 = findValueByTheKey(root, 3, errorCode) == "c";
    bool test2 = findValueByTheKey(root, 1, errorCode) == "a";
    bool test3 = findValueByTheKey(root, -3, errorCode) == "e";
    bool test4 = findValueByTheKey(root, 0, errorCode) == NULL;

    if (*errorCode) {
        disposeNode(&root);
        return false;
    }

    deleteByKey(root, 10, errorCode);
    deleteByKey(root, 5, errorCode);
    bool test5 = findValueByTheKey(root, 10, errorCode) == NULL;
    bool test6 = findValueByTheKey(root, 5, errorCode) == NULL;

    if (*errorCode) {
        disposeNode(&root);
        return false;
    }

    addToTheDictionary(root, -10, "m", errorCode);
    addToTheDictionary(root, -4, "g", errorCode);
    addToTheDictionary(root, 0, "n", errorCode);
    addToTheDictionary(root, -2, "k", errorCode);

    deleteByKey(root, -5, errorCode);
    bool test7 = findValueByTheKey(root, -5, errorCode) == NULL;

    disposeNode(&root);

    return test1 && test2 && test3 && test4 && test5 && test6 && test7;
}

void runTheDictionaryTests(bool* errorCode) {
    if (!testDictionary(errorCode)) {
        printf("Тест testDictionary не пройден\n");
        if (*errorCode) {
            printf("Код ошибки: 1\n");
            return;
        }
        printf("Код ошибки: 0\n");
        *errorCode = true;
        return;
    }
}