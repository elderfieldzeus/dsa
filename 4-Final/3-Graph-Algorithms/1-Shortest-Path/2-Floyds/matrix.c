#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define INF 9999

typedef int AdjMatrix[MAX][MAX];

int **floyds(AdjMatrix M);
void displayFloyds(int **flyd);
void initMatrix(AdjMatrix M);
void insertEdge(AdjMatrix M, int edge[3]);
void displayMatrix(AdjMatrix M);

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

    int root = 0;
    int **flyd= floyds(M);
    displayFloyds(flyd);

    return 0;
}

int **floyds(AdjMatrix M) {
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
                int newWeight = weights[i][k] + weights[k][j];

                if(newWeight < weights[i][j]) {
                    weights[i][j] = newWeight;
                } 
            }
        }
    }

    return weights;
}

void displayFloyds(int **flyd) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            (flyd[i][j] == INF) ? printf("INF ") : printf("%3d ", flyd[i][j]);
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