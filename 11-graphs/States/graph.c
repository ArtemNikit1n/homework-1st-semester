#include "graph.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct Edge {
    int edgeWeight;
    struct Vertex* adjacentVertex;
} Edge;

typedef struct Vertex {
    VertexValue value;
    int numberOfAdjacentVertices;
    Edge* adjacentVertices;
} Vertex;

struct Graph {
    int numberOfCitiesOutsideState;
    int numberOfVertices;
    Vertex** vertices;
};

Vertex* createVertex(VertexValue value, bool* errorCode) {
    Vertex* vertex = calloc(1, sizeof(Vertex));
    if (vertex == NULL) {
        *errorCode = true;
        return NULL;
    }

    vertex->value = value;
    return vertex;
}

void addVertex(Graph* graph, VertexValue value, bool* errorCode) {
    if (graph->vertices == NULL) {
        graph->vertices = calloc(value.key, sizeof(Vertex*));
        if (graph->vertices == NULL) {
            *errorCode = true;
            return;
        }
    } 

    if (value.key + 1 > graph->numberOfVertices) {
        Vertex** memoryForVertices = realloc(graph->vertices, (value.key + 1) * sizeof(Vertex*));
        if (memoryForVertices == NULL) {
            *errorCode = true;
            return;
        }
        graph->vertices = memoryForVertices;
        for (int i = graph->numberOfVertices; i < value.key + 1; ++i) {
            graph->vertices[i] = NULL;
        }
    }

    if (graph->vertices[value.key] != NULL) {
        return;
    }
    graph->vertices[value.key] = createVertex(value, errorCode);
    graph->numberOfVertices = max(graph->numberOfVertices, value.key + 1);
}

Vertex* addVertexToListOfAdjacentOnes(Vertex* vertex, Vertex* newVertex, const unsigned int edgeWeight, bool* errorCode) {
    if (vertex->adjacentVertices == NULL) {
        vertex->adjacentVertices = calloc(1, sizeof(Edge));
        if (vertex->adjacentVertices == NULL) {
            *errorCode = true;
            return NULL;
        }
        vertex->adjacentVertices[0].adjacentVertex = newVertex;
        vertex->adjacentVertices[0].edgeWeight = edgeWeight;

        ++vertex->numberOfAdjacentVertices;
    }
    else {
        Edge* memoryForAdjacentVertices = realloc(vertex->adjacentVertices, (vertex->numberOfAdjacentVertices + 1) * sizeof(Edge));
        if (memoryForAdjacentVertices == NULL) {
            *errorCode = true;
            return NULL;
        }
        vertex->adjacentVertices = memoryForAdjacentVertices;

        vertex->adjacentVertices[vertex->numberOfAdjacentVertices].adjacentVertex = newVertex;
        vertex->adjacentVertices[vertex->numberOfAdjacentVertices].edgeWeight = edgeWeight;
        ++vertex->numberOfAdjacentVertices;
    }
    return vertex;
}

Graph* connectVertices(Graph* graph, int key1, int key2, const unsigned int edgeWeight, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return NULL;
    }

    if (key1 >= graph->numberOfVertices || key2 >= graph->numberOfVertices || key2 < 0 || key1 < 0) {
        *errorCode = true;
        return NULL;
    }

    Vertex* updatedVertexBasedOnFirstKey = addVertexToListOfAdjacentOnes(graph->vertices[key1], graph->vertices[key2], edgeWeight, errorCode);
    if (*errorCode) {
        return NULL;
    }
    graph->vertices[key1] = updatedVertexBasedOnFirstKey;
    Vertex* updatedVertexBasedOnSecondKey = addVertexToListOfAdjacentOnes(graph->vertices[key2], graph->vertices[key1], edgeWeight, errorCode);
    if (*errorCode) {
        return NULL;
    }
    graph->vertices[key2] = updatedVertexBasedOnSecondKey;

    return graph;
}

void deleteGraph(Graph** pointerToGraph, bool* errorCode) {
    if (*pointerToGraph == NULL) {
        *errorCode = true;
        return;
    }

    for (int i = 0; i < (*pointerToGraph)->numberOfVertices; ++i) {
        if ((*pointerToGraph)->vertices[i] != NULL) {
            free((*pointerToGraph)->vertices[i]);
        }
    }
    free(*pointerToGraph);
    pointerToGraph = NULL;
}

Graph* createGraph(int initialSizeOfGraph, bool* errorCode) {
    Graph* graph = calloc(1, sizeof(Graph));
    if (graph == NULL) {
        *errorCode = true;
        return NULL;
    }

    if (*errorCode) {
        deleteGraph(&graph, errorCode);
        return NULL;
    }

    if (initialSizeOfGraph <= 0) {
        deleteGraph(&graph, errorCode);
        *errorCode = true;
        return NULL;
    }
    Vertex** vertices = calloc(initialSizeOfGraph, sizeof(Vertex*));
    if (vertices == NULL) {
        deleteGraph(&graph, errorCode);
        *errorCode = true;
        return NULL;
    }
    graph->vertices = vertices;
    graph->numberOfVertices = initialSizeOfGraph;
    return graph;
}

void setCapital(Graph* graph, int key, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return;
    }
    if (graph->vertices == NULL) {
        *errorCode = true;
        return;
    }
    if (graph->vertices[key] == NULL) {
        *errorCode = true;
        return;
    }
    graph->vertices[key]->value.isCapital = true;
    graph->vertices[key]->value.stateNumber = key;
}

void addNearestCity(Graph* graph, const int stateNumber, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return;
    }
    if (stateNumber < 0 || graph->numberOfVertices < stateNumber) {
        *errorCode = true;
        return;
    }

    int shortestRoad = INT_MAX;
    int nearestCity = -2;
    for (int i = 0; i < graph->numberOfVertices; ++i) {
        Vertex* selectedCityOfState = graph->vertices[i];
        int selectedStateNumber = selectedCityOfState->value.stateNumber;
        if (selectedStateNumber != stateNumber) {
            continue;
        }
        for (int j = 0; j < selectedCityOfState->numberOfAdjacentVertices; ++j) {
            int candidatesNumberForNearestCity = selectedCityOfState->adjacentVertices[j].adjacentVertex->value.key;
            if (selectedCityOfState->adjacentVertices[j].adjacentVertex->value.stateNumber == -1) {
                shortestRoad = min(shortestRoad, selectedCityOfState->adjacentVertices[j].edgeWeight);
                if (shortestRoad == selectedCityOfState->adjacentVertices[j].edgeWeight) {
                    nearestCity = candidatesNumberForNearestCity;
                }
            }
        }
    }
    if (nearestCity == -2) {
        return;
    }
    graph->vertices[nearestCity]->value.stateNumber = stateNumber;
}

void createStates(Graph* graph, bool* errorCode) {
    if (graph == NULL) {
        return;
    }

    graph->numberOfCitiesOutsideState = graph->numberOfVertices;
    for (int i = 0; i < graph->numberOfVertices; ++i) {
        if (graph->vertices[i]->value.isCapital) {
            addNearestCity(graph, graph->vertices[i]->value.stateNumber, errorCode);
            if (*errorCode) {
                return;
            }
            --graph->numberOfCitiesOutsideState;
            if (graph->numberOfCitiesOutsideState == 0) {
                return;
            }
        }
        if (i == graph->numberOfVertices - 1) {
            i = -1;
        }
    }
}

int* giveInformationAboutStates(Graph* graph, bool* errorCode) {
    int* information = calloc(graph->numberOfVertices, sizeof(int));
    if (information == NULL) {
        *errorCode = true;
        return NULL;
    }

    for (int i = 0; i < graph->numberOfVertices; ++i) {
        information[i] = graph->vertices[i]->value.stateNumber;
    }
    return information;
}

int getGraphSize(Graph* graph, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return 0;
    }
    return graph->numberOfVertices;
}