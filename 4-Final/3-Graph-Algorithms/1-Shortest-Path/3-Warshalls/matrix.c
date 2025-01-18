#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define INF 9999

typedef int AdjMatrix[MAX][MAX];

int **warshalls(AdjMatrix M);
void displayWarshalls(int **warsh);
void initMatrix(AdjMatrix M);
void insertEdge(AdjMatrix M, int edge[2]);
void displayMatrix(AdjMatrix M);

int main() {
    int edges[][2] = {
        {0, 1},  // Edge from 0 to 1 
        {0, 2},  // Edge from 0 to 2 
        {1, 2},  // Edge from 1 to 2 
        {1, 3},  // Edge from 1 to 3
        {2, 4},  // Edge from 2 to 4
        {4, 3}   // Edge from 4 to 3
    };

    int numOfEdges = sizeof(edges) / sizeof(edges[0]);
    
    AdjMatrix M;
    initMatrix(M);

    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(M, edges[i]);
    }

    displayMatrix(M);

    int **warsh = warshalls(M);
    displayWarshalls(warsh);

    return 0;
}

int **warshalls(AdjMatrix M) {
    int **weights = (int**) malloc(sizeof(int*) * MAX);

    // initialize weights
    for(int i = 0; i < MAX; i++){
        weights[i] = (int*) malloc(sizeof(int) * MAX);

        // copy to M
        for(int j = 0; j < MAX; j++) {
            if(i == j) {
                weights[i][j] = 0;
            }
            else {
                weights[i][j] = M[i][j];
            }
        }
    }


    // algorithm O(n^3)
    for(int k = 0; k < MAX; k++) { // connecting vertex
        for(int i = 0; i < MAX; i++) { // source vertex
            for(int j = 0; j < MAX; j++) { // destination vertex
                if(weights[i][k] == 1 && weights[k][j] == 1) { // if there is a path from i to k, and a path from k to j, then there is a path from i to j
                    weights[i][j] = 1;
                } 
            }
        }
    }

    return weights;
}

void displayWarshalls(int **warsh) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            (warsh[i][j] == INF) ? printf("INF ") : printf("%3d ", warsh[i][j]);
        }
        printf("\n");
    }
    printf("\n");
} 

void initMatrix(AdjMatrix M) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            M[i][j] = INF; // initialized to INF if not adjacent
        }
    }
}

void insertEdge(AdjMatrix M, int edge[2]) {
    M[edge[0]][edge[1]] = 1;
    M[edge[1]][edge[0]] = 1;
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