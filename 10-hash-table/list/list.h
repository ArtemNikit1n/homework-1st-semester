#pragma once

// This is necessary to quickly change the type of data stored in the list.
typedef const char * Value;

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
void removeListElement(List* list, Position position, bool* errorCode);

// Returns a pointer to the first added element.
Position first(List* list, bool* errorCode);

// Returns a pointer to the last added element.
Position last(List* list, bool* errorCode);

// Returns a pointer to the next element.
Position next(Position position, bool* errorCode);

// Returns the value at the passed position.
Value getValue(Position position, bool* errorCode);

// Allows you to set the frequency parameters.
void setFrequency(Position position, int frequency, bool* errorCode);

// Get the string frequency.
int getFrequency(Position position, bool* errorCode);