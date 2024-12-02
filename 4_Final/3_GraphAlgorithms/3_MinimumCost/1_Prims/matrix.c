#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define INF 9999

typedef struct {
    int u, v;
    int weight;
} EdgeType;

typedef struct {
    EdgeType nodes[MAX - 1];
    int nodeCount;
    int totalWeight;
} MinimumCostTree;

typedef int Set[MAX]; //  bit-vector Set

typedef int AdjMatrix[MAX][MAX];

MinimumCostTree prims(AdjMatrix M, int start);
void displayEdgeList(EdgeType edges[], int size);

void initMatrix(AdjMatrix M);
void insertEdge(AdjMatrix M, int edge[3]);
void displayMatrix(AdjMatrix M);
void displayEdges(AdjMatrix M);

int main() {
    int edges[][3] = {
        {0, 1, 2},  // Edge from 0 to 1 with weight 2
        {0, 2, 4},  // Edge from 0 to 2 with weight 4
        {1, 2, 1},  // Edge from 1 to 2 with weight 1
        {1, 3, 7},  // Edge from 1 to 3 with weight 7
        {2, 4, 3},  // Edge from 2 to 4 with weight 3
        {4, 3, 2}   // Edge from 4 to 3 with weight 2
    };

    int numOfEdges = sizeof(edges) / sizeof(edges[0]);
    
    AdjMatrix M;
    initMatrix(M);

    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(M, edges[i]);
    }

    displayMatrix(M);

    MinimumCostTree MCT = prims(M, 0);
    printf("Minimum weight is: %d\n", MCT.totalWeight);

    printf("MCT Edges: ");
    displayEdgeList(MCT.nodes, MCT.nodeCount);

    return 0;
}

MinimumCostTree prims(AdjMatrix M, int start) {
    MinimumCostTree MST = {.nodeCount = 0, .totalWeight = 0};

    Set visited = {};
    visited[start] = 1;
    int NUMBER_OF_NODES = MAX - 1;

    while(MST.nodeCount < NUMBER_OF_NODES && MST.totalWeight < INF) { // MST.totalWeight < INF is optional, only using it to check if graph is connected
        EdgeType minEdge = {.weight = INF}; // initialized to INF
        
        for(int i = 0; i < MAX; i++) {
            // if part of the tree, then find for shortest edge to a vertex that is not part of the tree
            if(visited[i] == 1) {
                for(int j = 0; j < MAX; j++) {
                    if(visited[j] == 0 && M[i][j] < minEdge.weight) {
                        EdgeType temp = {i, j, M[i][j]};
                        minEdge = temp;
                    }
                }
            }
        }

        MST.totalWeight += minEdge.weight;

        if(minEdge.weight != INF) {
            MST.nodes[MST.nodeCount++] = minEdge;
            visited[minEdge.v] = 1;
        }
        else {
            printf("GRAPH NOT CONNECTED.\n\n");
        }
    }

    return MST;
}

void displayEdgeList(EdgeType edges[], int size) {
    for(int i = 0; i < size; i++) { 
        printf("[(%d, %d) = %d] ", edges[i].u, edges[i].v, edges[i].weight);
    }
}

void initMatrix(AdjMatrix M) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            M[i][j] = INF;
        }
    }
}

void insertEdge(AdjMatrix M, int edge[3]) {
    M[edge[0]][edge[1]] = edge[2];
    M[edge[1]][edge[0]] = edge[2];
}

void displayMatrix(AdjMatrix M) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            (M[i][j] == INF) ? printf("INF ") : printf("%3d ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void displayEdges(AdjMatrix M) {
    printf("Edges: ");
    for(int i = 0; i < MAX; i++) {
        for(int j = i + 1; j < MAX; j++) {
            if(M[i][j] == 1) {
                printf("(%d, %d) ", i, j);
            }
        }
    }
}