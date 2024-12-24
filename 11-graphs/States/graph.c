#include "graph.h"
#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct Vertex {
    VertexValue value;
    int numberOfAdjacentVertices;
    struct Vertex** adjacentVertices;
} Vertex;

struct Graph {
    int numberOfCitiesOutsideState;
    int numberVertices;
    int** adjacencyMatrix;
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

int** expandMatrix(int** matrix, int currentSize, int desiredSize, bool* errorCode) {
    matrix = realloc(matrix, desiredSize * sizeof(int*));
    if (matrix == NULL) {
        *errorCode = true;
        return;
    }
    for (int i = currentSize; i < desiredSize; ++i) {
        matrix[i] = NULL;
    }

    for (int i = 0; i < desiredSize; ++i) {
        matrix[i] = realloc(matrix[i], desiredSize * sizeof(int));
        if (matrix[i] == NULL) {
            *errorCode = true;
            return;
        }
        if (i + 1 > currentSize) {
            memset(matrix[i], 0, desiredSize * sizeof(int));
        }
        else {
            for (int j = currentSize; j < desiredSize; ++j) {
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

void addVertex(Graph* graph, VertexValue value, bool* errorCode) {
    if (graph->vertices == NULL) {
        graph->vertices = calloc(value.key, sizeof(Vertex*));
        if (graph->vertices == NULL) {
            *errorCode = true;
            return;
        }
    } 

    if (value.key + 1 > graph->numberVertices) {
        graph->vertices = realloc(graph->vertices, (value.key + 1) * sizeof(Vertex*));
        if (graph->vertices == NULL) {
            *errorCode = true;
            return;
        }
        for (int i = graph->numberVertices; i < value.key + 1; ++i) {
            graph->vertices[i] = NULL;
        }

        graph->adjacencyMatrix = expandMatrix(graph->adjacencyMatrix, graph->numberVertices, value.key + 1, errorCode);
        if (*errorCode) {
            return;
        }
    }

    if (graph->vertices[value.key] != NULL) {
        return;
    }
    graph->vertices[value.key] = createVertex(value, errorCode);
    graph->numberVertices = max(graph->numberVertices, value.key + 1);
}

Vertex* addVertexToListOfAdjacentOnes(Vertex* vertex, Vertex* newVertex, bool* errorCode) {
    if (vertex->adjacentVertices == NULL) {
        vertex->adjacentVertices = calloc(1, sizeof(Vertex*));
        if (vertex->adjacentVertices == NULL) {
            *errorCode = true;
            return;
        }
        vertex->adjacentVertices[0] = newVertex;

        ++vertex->numberOfAdjacentVertices;
    }
    else {
        vertex->adjacentVertices = realloc(vertex->adjacentVertices, (vertex->numberOfAdjacentVertices + 1) * sizeof(Vertex*));
        if (vertex->adjacentVertices == NULL) {
            *errorCode = true;
            return;
        }
        
        vertex->adjacentVertices[vertex->numberOfAdjacentVertices] = newVertex;
        ++vertex->numberOfAdjacentVertices;
    }
    return vertex;
}

Graph* connectVertices(Graph* graph, int key1, int key2, int edgeWeight, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return;
    }

    if (key1 >= graph->numberVertices || key2 >= graph->numberVertices || key2 < 0 || key1 < 0) {
        *errorCode = true;
        return;
    }

    graph->adjacencyMatrix[key1][key2] = edgeWeight;

    graph->vertices[key1] = addVertexToListOfAdjacentOnes(graph->vertices[key1], graph->vertices[key2], errorCode);
    if (*errorCode) {
        return;
    }
    graph->vertices[key2] = addVertexToListOfAdjacentOnes(graph->vertices[key2], graph->vertices[key1], errorCode);
    if (*errorCode) {
        return;
    }
    return graph;
}

void deleteMatrix(int*** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        free((*matrix)[i]);
    }
    free(*matrix);
    *matrix = NULL;
}

int** createMatrix(int size, bool* errorCode) {
    int** matrix = calloc(size, sizeof(int*));
    if (matrix == NULL) {
        *errorCode = true;
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        matrix[i] = calloc(size, sizeof(int));
        if (matrix[i] == NULL) {
            deleteMatrix(&matrix, i + 1);
            *errorCode = true;
            return NULL;
        }
    }
    return matrix;
}

void deleteGraph(Graph** pointerToGraph, bool* errorCode) {
    if (*pointerToGraph == NULL) {
        *errorCode = true;
        return;
    }

    deleteMatrix(&(*pointerToGraph)->adjacencyMatrix, (*pointerToGraph)->numberVertices);
    for (int i = 0; i < (*pointerToGraph)->numberVertices; ++i) {
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

    graph->adjacencyMatrix = createMatrix(initialSizeOfGraph, errorCode);
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
    graph->numberVertices = initialSizeOfGraph;
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

void printMatrix(Graph* graph) {
    int** matrix = graph->adjacencyMatrix;
    for (int i = 0; i < graph->numberVertices; ++i) {
        for (int j = 0; j < graph->numberVertices; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int getGraphSize(Graph* graph) {
    return graph->numberVertices;
}

void addNearestCity(Graph* graph, const int city, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return;
    }
    if (city < 0 || graph->numberVertices < city) {
        *errorCode = true;
        return;
    }

    int shortestRoad = INT_MAX;
    int nearestCity = -2;
    for (int i = 0; i < graph->numberVertices; ++i) {
        Vertex* selectedCityOfState = graph->vertices[i];
        int stateNumber = selectedCityOfState->value.stateNumber;
        if (stateNumber != city) {
            continue;
        }
        for (int j = 0; j < selectedCityOfState->numberOfAdjacentVertices; ++j) {
            int candidatesNumberForNearestCity = selectedCityOfState->adjacentVertices[j]->value.key;
            if (selectedCityOfState->adjacentVertices[j]->value.stateNumber == -1) {
                shortestRoad = min(shortestRoad, graph->adjacencyMatrix[i][candidatesNumberForNearestCity]);
                if (shortestRoad == graph->adjacencyMatrix[i][candidatesNumberForNearestCity]) {
                    nearestCity = candidatesNumberForNearestCity;
                }
            }
        }
    }
    if (nearestCity == -2) {
        return;
    }
    graph->vertices[nearestCity]->value.stateNumber = city;
}

bool isCapital(Graph* graph, int key, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return false;
    }
    if (key < 0 || graph->numberVertices < key) {
        *errorCode = true;
        return false;
    }
    return graph->vertices[key]->value.isCapital;
}

void createStates(Graph* graph, int graphSize, bool* errorCode) {
    Queue* capitals = createQueue(*errorCode);
    if (*errorCode) {
        return;
    }
    for (int i = 0; i < graphSize; ++i) {
        if (isCapital(graph, i, errorCode)) {
            enqueue(capitals, i, errorCode);
            if (*errorCode) {
                return;
            }
        }
    }
    graph->numberOfCitiesOutsideState = graphSize;
    while (graph->numberOfCitiesOutsideState != 0) {
        int selectedCity = dequeue(capitals, errorCode);
        enqueue(capitals, selectedCity, errorCode);
        if (*errorCode) {
            return;
        }
        addNearestCity(graph, selectedCity, errorCode);
        if (*errorCode) {
            return;
        }
        --graph->numberOfCitiesOutsideState;
    }
}