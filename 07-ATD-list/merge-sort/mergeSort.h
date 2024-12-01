#pragma once

#include "../list/list.h"

// Sorts a list with elements of the char* type.
void sortByMerging(List* list, Position left, Position right, SortingCriteria criteria, bool* errorCode);