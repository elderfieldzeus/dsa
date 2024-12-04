#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int Set[MAX]; // bit-vector

typedef struct node {
    int label;
    struct node *next;
} *Vertex;

typedef Vertex AdjList[MAX];

void dfs(AdjList M, Set visited, int root);

void initList(AdjList M);
void insertEdge(AdjList M, int edge[2]);
void displayList(AdjList M);
void displayEdges(AdjList M);

int main() {
    int edges[][2] = {{0, 1}, {1, 4}, {1, 2}, {2, 3}, {3, 4}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);
    
    AdjList M;
    initList(M);

    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(M, edges[i]);
    }

    displayList(M);
    displayEdges(M);

    int root = 0;
    Set visited = {};

    printf("DFS: ");
    dfs(M, visited, root);

    return 0;
}

void dfs(AdjList M, Set visited, int root) {
    printf("%d ", root);
    visited[root] = 1;

    for(Vertex curr = M[root]; curr != NULL; curr = curr->next) {
        if(visited[curr->label] == 0) {
            visited[curr->label] = 1;
            dfs(M, visited, curr->label);
        }
    }
}

void initList(AdjList M) {
    for(int i = 0; i < MAX; i++) {
        M[i] = NULL;
    }
}

void insertEdge(AdjList M, int edge[2]) {
    Vertex temp = (Vertex) malloc(sizeof(struct node));

    if(temp != NULL) {
        temp->label = edge[1];
        temp->next = M[edge[0]];
        M[edge[0]] = temp;
    }

    temp = (Vertex) malloc(sizeof(struct node));

    if(temp != NULL) {
        temp->label = edge[0];
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