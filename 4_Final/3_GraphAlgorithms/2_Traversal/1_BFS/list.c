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

typedef struct node {
    int label;
    struct node *next;
} *Vertex;

typedef Vertex AdjList[MAX];

void bfs(AdjList M, int root);
void initQueue(Queue *Q);
bool isEmpty(Queue Q);
void enqueue(Queue *Q, int data);
int dequeue(Queue *Q);

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

    bfs(M, 0);
    return 0;
}

void bfs(AdjList M, int root) {
    Set visited = {};
    visited[root] = 1;

    Queue Q;
    initQueue(&Q);

    enqueue(&Q, root);
    
    printf("BFS: ");
    
    while(!isEmpty(Q)) {
        int node = dequeue(&Q);
        printf("%d ", node);

        for(Vertex curr = M[node]; curr != NULL; curr = curr->next) {
            if(visited[curr->label] == 0) {
                visited[curr->label] = 1;
                enqueue(&Q, curr->label);
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