
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../TheCyclicList/theCyclicList.h"

typedef struct ListElement {
    Value value;
    struct ListElement* next;
} ListElement;

struct List {
    ListElement* first;
    ListElement* last;
};

bool listIsEmpty(List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return true;
    }
    return list->last == NULL;
}

List* createList(bool* errorCode) {
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return list;
}

void deleteList(List** listDoublePointer) {
    List* list = *listDoublePointer;
    if (list == NULL) {
        return;
    }
    while (list->first != NULL) {
        if (list->first->next = list->first) {
            free(list->first);
            break;
        }
        ListElement* next = list->first->next;
        free(list->first);
        list->first = next;
    }
    free(list);
    *listDoublePointer = NULL;
}

Value removeListElement(List* list, Position position, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return true;
    }
    if (list->first == list->last) {
        Value value = position->value;
        free(position);
        list->first = NULL;
        list->last = NULL;
        return value;
    }
    if (list->first == position->next) {
        list->first = list->first->next;
    }
    if (list->last == position->next) {
        list->last = position;
    }
    ListElement* temp = position->next;
    if (temp == NULL) {
        *errorCode = true;
        return NULL;
    } 
    Value value = position->next->value;
    position->next = position->next->next;
    free(temp);
    if (list->first == NULL) {
        *errorCode = true;
        return NULL;
    }
    return value;
}

Position add(List* list, Position position, Value value, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    ListElement* new = calloc(1, sizeof(ListElement));
    if (new == NULL) {
        *errorCode = true;
        return NULL;
    }
    new->value = value;
    if (position == NULL) {
        list->first = new;
        list->last = new;
        new->next = new;
        return new;
    }
    if (list->last == position) {
        new->next = list->first;
        position->next = new;
        list->last = new;
        return new;
    }
    ListElement* temp = position->next;
    position->next = new;
    new->next = temp;
    return new;
}

Position first(List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return list->first;
}

Position last(List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return list->last;
}

Position next(Position position, bool *errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return NULL;
    }
    if (position->next == NULL) {
        *errorCode = true;
        return NULL;
    }
    return position->next;
}

Value getValue(Position position, bool *errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return 0;
    }
    return position->value;
}
