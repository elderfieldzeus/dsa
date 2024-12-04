#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define INF 9999

typedef int Set[MAX]; // bit-vector implementation

typedef struct node {
    int label;
    int weight;
    struct node *next;
} *Vertex;

typedef Vertex AdjList[MAX];

int* dijkstras(AdjList M, int root);
void displayDjk(int arr[], int root);
void initList(AdjList M);
void insertEdge(AdjList M, int edge[3]);
void displayList(AdjList M);

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
    
    AdjList M;
    initList(M);

    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(M, edges[i]);
    }

    displayList(M);

    int root = 0;
    int *djk = dijkstras(M, root);
    displayDjk(djk, root);

    return 0;
}

int* dijkstras(AdjList M, int root) {
    int *weightFromRoot = (int *) malloc(sizeof(int) * MAX);
    Set visited = {};
    visited[root] = 1;

    // initialize all to INF
    for(int i = 0; i < MAX; i++) {
        weightFromRoot[i] = INF;
    }

    // initialize weight from nodes connected to root 
    for(Vertex curr = M[root]; curr != NULL; curr = curr->next) {
        weightFromRoot[curr->label] = curr->weight;
    }

    weightFromRoot[root] = 0;

    for(int i = 1; i < MAX; i++) {
        int min = INF;
        int minNode;

        for(int j = 0; j < MAX; j++) {      // find minimum from weight array
            if(visited[j] == 0 && weightFromRoot[j] < min) {
                min = weightFromRoot[j];
                minNode = j;
            }
        }

        if(min != INF) {
            visited[minNode] = 1;

            for(int j = 0; j < MAX; j++) {
                if(visited[j] == 0) {
                    Vertex trav;

                    for(trav = M[minNode]; trav != NULL && trav->label != j; trav = trav->next) {}

                    if(trav != NULL) {
                        if(trav->weight + min < weightFromRoot[j]) {
                            weightFromRoot[j] = trav->weight + min;
                            printf("%d %d %d\n", minNode, j, weightFromRoot[j]);
                        }
                    }
                }
            }
        }
        else {
            printf("GRAPH IS NOT CONNECTED.\n");
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

void initList(AdjList M) {
    for(int i = 0; i < MAX; i++) {
        M[i] = NULL;
    }
}

void insertEdge(AdjList M, int edge[3]) {
    Vertex temp = (Vertex) malloc(sizeof(struct node));

    if(temp != NULL) {
        temp->label = edge[1];
        temp->weight = edge[2];
        temp->next = M[edge[0]];
        M[edge[0]] = temp;
    }

    temp = (Vertex) malloc(sizeof(struct node));

    if(temp != NULL) {
        temp->label = edge[0];
        temp->weight = edge[2];
        temp->next = M[edge[1]];
        M[edge[1]] = temp;
    }
}

void displayList(AdjList M) {
    for(int i = 0; i < MAX; i++) {
        printf("Node %d: ", i);
        for(Vertex curr = M[i]; curr != NULL; curr = curr->next) {
            printf("%d ", curr->label);
        }
        printf("\n");
    }
}

void displayEdges(AdjList M) {
    printf("Edges: ");
    for(int i = 0; i < MAX; i++) {
        for(Vertex curr = M[i]; curr != NULL; curr = curr->next) {
            if(curr->label > i) {
                printf("(%d, %d) ", i, curr->label);
            }
        }
    }

    printf("\n");
}