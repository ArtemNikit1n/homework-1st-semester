#define _CRT_SECURE_NO_WARNINGS

#include "graphsTests.h"
#include "graph.h"

#include <stdbool.h>
#include <stdio.h>

Graph* buildGraph(const char* fileName, bool* errorCode) {
    FILE* file = fopen(fileName, "r");
    int numberOfVertices = 0;
    fscanf(file, "%d ", &numberOfVertices);
    Graph* graph = createGraph(numberOfVertices, errorCode);
    if (*errorCode) {
        return NULL;
    }

    int numberOfEdges = 0;
    fscanf(file, "%d ", &numberOfEdges);
    int numberOfVerticesCreated = 0;
    for (int i = 0; i < numberOfEdges; ++i) {
        VertexValue value = { .isCapital = false, .key = -1, .stateNumber = -1 };
        int firstKey = -1;
        fscanf(file, "%d ", &firstKey);
        value.key = firstKey;
        addVertex(graph, value, errorCode);
        if (*errorCode) {
            deleteGraph(&graph, errorCode);
            return NULL;
        }

        int secondKey = -1;
        fscanf(file, "%d ", &secondKey);
        value.key = secondKey;
        addVertex(graph, value, errorCode);
        if (*errorCode) {
            deleteGraph(&graph, errorCode);
            return NULL;
        }

        int edgeWeight = -1;
        fscanf(file, "%d ", &edgeWeight);

        graph = connectVertices(graph, firstKey, secondKey, edgeWeight, errorCode);
        if (*errorCode) {
            deleteGraph(&graph, errorCode);
            return NULL;
        }
    }

    int numberOfCapitals = -1;
    fscanf(file, "%d ", &numberOfCapitals);
    for (int i = 0; i < numberOfCapitals; ++i) {
        int city = -1;
        fscanf(file, "%d ", &city);
        setCapital(graph, city, errorCode);
    }
    return graph;
}

int main(void) {
    bool errorCode = false;
    testGraph(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    Graph* graph = buildGraph("graphData.txt", &errorCode);
    if (errorCode) {
        return errorCode;
    }
    createStates(graph, &errorCode);
    if (errorCode) {
        deleteGraph(&graph, &errorCode);
        return errorCode;
    }
    int* informationAboutStates = giveInformationAboutStates(graph, &errorCode);
    if (errorCode) {
        deleteGraph(&graph, &errorCode);
        return errorCode;
    }
    int graphSize = getGraphSize(graph, &errorCode);

    printf("City number:\n");
    for (int i = 0; i < graphSize; ++i) {
        printf("%d\t", i);
    }
    printf("\nState number:\n");
    for (int i = 0; i < graphSize; ++i) {
        printf("%d\t", informationAboutStates[i]);
    }
    return errorCode;
} 