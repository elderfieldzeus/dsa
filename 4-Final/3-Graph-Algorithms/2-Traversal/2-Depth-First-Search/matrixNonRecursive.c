#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define MAX_STACK 25

typedef int Set[MAX]; // bit-vector

typedef int AdjMatrix[MAX][MAX];

void dfs(AdjMatrix M, int root);

typedef struct {
    int elems[MAX];
    int top;
} Stack;

void initMatrix(AdjMatrix M);
void insertEdge(AdjMatrix M, int edge[2]);
void displayMatrix(AdjMatrix M);
void displayEdges(AdjMatrix M);
void push(Stack *S, int data);
int isEmpty(Stack S);
int pop(Stack *S);

int main() {
    int edges[][2] = {{0, 1}, {1, 4}, {1, 2}, {2, 3}, {3, 4}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);
    
    AdjMatrix M;
    initMatrix(M);

    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(M, edges[i]);
    }

    displayMatrix(M);
    displayEdges(M);

    int root = 0;

    printf("DFS: ");
    dfs(M, root);

    return 0;
}

void dfs(AdjMatrix M, int root) {
    Stack S = {.top = -1};
    Set visited = {};

    push(&S, root);

    while(!isEmpty(S)) {
        int top = pop(&S);

        if(visited[top] == 0) {
            printf("%d ", top);
            visited[top] = 1;

            for(int i = MAX - 1; i >= 0; i--) {
                if(M[top][i] == 1 && visited[i] == 0) {
                    push(&S, i);
                }
            }
        }
    }
}

void initMatrix(AdjMatrix M) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            M[i][j] = 0;
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
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
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
    printf("\n");
}

void push(Stack *S, int data) {
    if(S->top + 1 < MAX) {
        S->elems[++S->top] = data;
    }
}

int isEmpty(Stack S) {
    return (S.top == -1) ? 1 : 0;
}

int pop(Stack *S) {
    int ret = -1;

    if(!isEmpty(*S)) {
        ret = S->elems[S->top--];
    }

    return ret;
}

