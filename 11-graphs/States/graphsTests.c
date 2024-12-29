#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

void testCreateAndDelete(bool* errorCode) {
    VertexValue value1 = { .key = 0, .stateNumber = 0, .isCapital = false };
    VertexValue value2 = { .key = 1, .stateNumber = 1, .isCapital = true };

    Graph* testGraph = createGraph(5, errorCode);
    addVertex(testGraph, value1, errorCode);
    addVertex(testGraph, value2, errorCode);
    deleteGraph(&testGraph, errorCode);
}

void testConnectVertices(bool* errorCode) {
    VertexValue value1 = { .key = 0, .stateNumber = 0, .isCapital = false };
    VertexValue value2 = { .key = 1, .stateNumber = 1, .isCapital = true };
    VertexValue value3 = { .key = 5, .stateNumber = 2, .isCapital = true };

    Graph* testGraph1 = createGraph(2, errorCode);
    addVertex(testGraph1, value1, errorCode);
    addVertex(testGraph1, value2, errorCode);
    addVertex(testGraph1, value3, errorCode);

    testGraph1 = connectVertices(testGraph1, 0, 5, 10, errorCode);
    testGraph1 = connectVertices(testGraph1, 0, 1, 7, errorCode);

    deleteGraph(&testGraph1, errorCode);
    if (*errorCode) {
        return;
    }
    VertexValue value4 = { .key = 5, .stateNumber = 0, .isCapital = false };
    VertexValue value5 = { .key = 1, .stateNumber = 1, .isCapital = true };
    VertexValue value6 = { .key = 0, .stateNumber = 2, .isCapital = true };

    Graph* testGraph2 = createGraph(3, errorCode);
    addVertex(testGraph2, value4, errorCode);
    addVertex(testGraph2, value5, errorCode);
    addVertex(testGraph2, value6, errorCode);

    testGraph2 = connectVertices(testGraph2, 0, 1, 10, errorCode);
    testGraph2 = connectVertices(testGraph2, 0, 5, 7, errorCode);
    deleteGraph(&testGraph2, errorCode);
}

bool areArraysEqual(int array1[], int array2[], int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

void testCreateStates(bool* errorCode) {
    int graphSize = 10;
    Graph* graph = createGraph(graphSize, errorCode);
    if (*errorCode) {
        return;
    }

    for (int i = 0; i < graphSize; ++i) {
        VertexValue value = { .isCapital = false, .key = i, .stateNumber = -1 };
        addVertex(graph, value, errorCode);
        if (*errorCode) {
            deleteGraph(&graph, errorCode);
            return;
        }
    }
    connectVertices(graph, 0, 4, 1, errorCode);
    connectVertices(graph, 0, 1, 3, errorCode);
    connectVertices(graph, 0, 5, 5, errorCode);
    connectVertices(graph, 1, 2, 2, errorCode);
    connectVertices(graph, 2, 5, 20, errorCode);
    connectVertices(graph, 2, 3, 7, errorCode);
    connectVertices(graph, 3, 7, 5, errorCode);
    connectVertices(graph, 3, 8, 4, errorCode);
    connectVertices(graph, 5, 6, 6, errorCode);
    connectVertices(graph, 7, 8, 1, errorCode);
    connectVertices(graph, 7, 9, 2, errorCode);
    if (*errorCode) {
        deleteGraph(&graph, errorCode);
        return;
    }
    setCapital(graph, 0, errorCode);
    setCapital(graph, 8, errorCode);
    if (*errorCode) {
        deleteGraph(&graph, errorCode);
        return;
    }

    createStates(graph, errorCode);
    if (*errorCode) {
        deleteGraph(&graph, errorCode);
        return;
    }
    int expectedResult[10] = { 0, 0, 0, 8, 0, 0, 0, 8, 8, 8 };
    int* informationAboutStates = giveInformationAboutStates(graph, errorCode);
    if (*errorCode) {
        deleteGraph(&graph, errorCode);
        return;
    }
    if (!areArraysEqual(expectedResult, informationAboutStates, graphSize)) {
        *errorCode = true;
        deleteGraph(&graph, errorCode);
        return;
    }
}

void testGraph(bool* errorCode) {
    testCreateAndDelete(errorCode);
    testConnectVertices(errorCode);
    testCreateStates(errorCode);
}