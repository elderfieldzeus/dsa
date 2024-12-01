#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5

typedef int Set[MAX]; // bit-vector

typedef struct {
    int nodes[MAX];
    int front;
    int rear;
} Queue; // array implementation of queue

typedef int AdjMatrix[MAX][MAX];

void bfs(AdjMatrix M, int root);
void initQueue(Queue *Q);
bool isEmpty(Queue Q);
void enqueue(Queue *Q, int data);
int dequeue(Queue *Q);

void initMatrix(AdjMatrix M);
void insertEdge(AdjMatrix M, int edge[2]);
void displayMatrix(AdjMatrix M);
void displayEdges(AdjMatrix M);

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

    bfs(M, 0);
    return 0;
}

void bfs(AdjMatrix M, int root) {
    Set visited = {};
    visited[root] = 1;

    Queue Q;
    initQueue(&Q);

    enqueue(&Q, root);
    
    printf("BFS: ");
    
    while(!isEmpty(Q)) {
        int node = dequeue(&Q);
        printf("%d ", node);

        for(int i = 0; i < MAX; i++) {
            if(visited[i] == 0 && M[node][i] != 0) {
                visited[i] = 1;
                enqueue(&Q, i);
            }
        }
    }
}

void initQueue(Queue *Q) {
    Q->front = 1;
    Q->rear = 0;
}

bool isEmpty(Queue Q) {
    return (Q.rear + 1) % MAX == Q.front ? true : false;
}

void enqueue(Queue *Q, int data) {
    if((Q->rear + 2) % MAX != Q->front) {
        Q->rear = (Q->rear + 1) % MAX;
        Q->nodes[Q->rear] = data; 
    }
}

int dequeue(Queue *Q) {
    int ret = -1;
    if(!isEmpty(*Q)) {
        ret = Q->nodes[Q->front];
        Q->front = (Q->front + 1) % MAX;
    }
    return ret;
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