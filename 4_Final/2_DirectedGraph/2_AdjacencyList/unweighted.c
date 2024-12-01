#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct node {
    int label;
    struct node *next;
} *Vertex;

typedef Vertex AdjList[MAX];

void initAdjList(AdjList L);
void insertEdge(AdjList L, int edge[2]);
void displayAdjList(AdjList L);
void displayEdges(AdjList L);

int main() {
    int edges[][2] = {{1, 2}, {2, 3}, {3, 0}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);

    AdjList L;
    initAdjList(L);

    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(L, edges[i]);
    }

    displayAdjList(L);
    displayEdges(L);
}

void initAdjList(AdjList L) {
    for(int i = 0; i < MAX; i++) {
        L[i] = NULL;
    }
}

void insertEdge(AdjList L, int edge[2]) {
    Vertex temp = (Vertex) malloc(sizeof(struct node));

    if(temp != NULL) {
        temp->label = edge[1];
        temp->next = L[edge[0]];
        L[edge[0]] = temp;
    }
}

void displayAdjList(AdjList L) {
    for(int i = 0; i < MAX; i++) {
        printf("Node %d: ", i);

        Vertex trav = L[i];

        if(trav == NULL) {
            printf("EMPTY");
        }

        for(; trav != NULL; trav = trav->next) {
            printf("%d ", trav->label);
        }

        printf("\n");
    }
}

void displayEdges(AdjList L) {
    printf("Edges: ");
    for(int i = 0; i < MAX; i++) {
        for(Vertex trav = L[i]; trav != NULL; trav = trav->next) {
            printf("(%d, %d) ", i, trav->label);
        }
    }
}