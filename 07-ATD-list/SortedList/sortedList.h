#pragma once

#include "../list/list.h"

// Print all the values of the list.
void printList(const List* list, bool* errorCode);

// Adds a value to the sorted list.
void addItToSortedList(List* list, int valueToAdd, bool* errorCode);

// Allows the user to delete an item by position.
void deleteFromSortedList(List* list, int position, bool* errorCode);