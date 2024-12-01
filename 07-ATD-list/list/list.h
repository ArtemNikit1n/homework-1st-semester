#pragma once

// This is necessary to quickly change the type of data stored in the list.
typedef int Value;

// This is a list type declaration.
typedef struct List List;

// Pointer to a list item.
typedef struct ListElement* Position;

// Returns true if the list is empty.
bool listIsEmpty(List* list, bool* errorCode);

// Deletes the list.
void deleteList(List** listDoublePointer);

// Creates a list together with the guard.
List* createList(bool* errorCode);

// Adds a new element to the specified location.
Position add(List* list, Position position, Value value, bool* errorCode);

// Deletes an element from the specified location.
Value removeListElement(List* list, Position position, bool* errorCode);

// Returns a pointer to the first added element.
Position first(List* list, bool* errorCode);

// Returns a pointer to the next element.
Position next(Position position, bool* errorCode);

// Returns the value at the passed position.
Value getValue(Position position, bool* errorCode);

// Sets a value to a list item.
void setValue(Position position, Value value, bool* errorCode);

// Returns the last item in the list.
Position last(List* list, bool* errorCode);
