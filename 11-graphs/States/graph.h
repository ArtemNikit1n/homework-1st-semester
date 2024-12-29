#pragma once

#include <stdbool.h>

// A structure for storing vertices.
typedef struct Graph Graph;

// The value that is stored at the vertex.
typedef struct VertexValue {
    int key;
    int stateNumber;
    bool isCapital;
} VertexValue;

// Creates an array of vertices.
Graph* createGraph(int initialSizeOfGraph, bool* errorCode);

// Deletes the entire graph.
void deleteGraph(Graph** pointerToGraph, bool* errorCode);

// Adds a new vertex to the graph.
// The key for the node is set automatically and is equal to the number of nodes already added.
void addVertex(Graph* graph, VertexValue value, bool* errorCode);

// Connects two vertices.
Graph* connectVertices(Graph* graph, int key1, int key2, const unsigned int edgeWeight, bool* errorCode);

// Sets the capital by the key.
void setCapital(Graph* graph, int key, bool* errorCode);

// Unites the graph into states.
void createStates(Graph* graph, bool* errorCode);

// Returns an array whose indexes are keys, and the values in the cell are the state to which the vertex belongs according to this key (index).
int* giveInformationAboutStates(Graph* graph, bool* errorCode);

// Allows you to find out the size of the graph.
int getGraphSize(Graph* graph, bool* errorCode);
