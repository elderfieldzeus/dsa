#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define INF 9999

typedef int Set[MAX]; // bit-vector implementation
typedef int AdjMatrix[MAX][MAX];

int* dijkstras(AdjMatrix M, int root);
void displayDjk(int arr[], int root);
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
    int *djk = dijkstras(M, root);
    displayDjk(djk, root);

    return 0;
}

int* dijkstras(AdjMatrix M, int root) {
    int *weightFromRoot = (int*) malloc(sizeof(int) * MAX);
    
    if(weightFromRoot != NULL) {
        Set visited = {};
        visited[root] = 1; 

        // initialize weight from root
        for(int i = 0; i < MAX; i++) {
            weightFromRoot[i] = M[root][i];
        }

        // algorithm
        for(int i = 1; i < MAX; i++) {
            int smallestIndex = 0;

            // find smallest
            for(int j = 0; j < MAX; j++) {
                if(visited[smallestIndex] == 1 || (weightFromRoot[j] < weightFromRoot[smallestIndex] && visited[j] == 0)) {
                    smallestIndex = j;
                }
            }

            // add smallestIndex to visited
            visited[smallestIndex] = 1;

            for(int k = 0; k < MAX; k++) {
                if(visited[k] == 0) {
                    int nextWeight = weightFromRoot[smallestIndex] + M[smallestIndex][k]; // adds the new path from smallestIndex to next index
                    weightFromRoot[k] = (weightFromRoot[k] < nextWeight) ? weightFromRoot[k] : nextWeight; // new weight gets the lesser of the two
                }
            }
        }
    }

    return weightFromRoot;
}

void displayDjk(int arr[], int root) {
    printf("\nDijkstra's Paths from %d:\n", root);
    for(int i = 0; i < MAX; i++) {
        
        printf("Path from %d to %d: ", root, i);
        (arr[i] == INF) ? printf("NONE\n") : printf("%d\n", arr[i]);
    }
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
}