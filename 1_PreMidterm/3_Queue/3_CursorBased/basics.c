#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define VHSIZE 10

typedef struct {
    int data;
} Element;

typedef struct {
    Element elem;
    int next;
} Node;

typedef struct {
    Node VHNode[VHSIZE];
    int avail;
} VHeap;

typedef int List;

typedef struct {
    List front;
    List rear;
} Queue;


void init(Queue *Q);
void read(Queue Q, VHeap V);
bool isEmpty(Queue Q);
bool isFull(VHeap V);
Element front(Queue Q, VHeap V);
void dequeue(Queue *Q, VHeap *V);
void enqueue(Queue *Q, VHeap *V, int data);


//CB General Functions
void initVH(VHeap *V);
int mallocVH(VHeap *V);
void freeVH(VHeap *V, int index);

void readNexts(VHeap V);


int main() {
    VHeap V;
    Queue Q;

    printf("\033[H\033[J");

    initVH(&V);
    // readNexts(V);

    init(&Q);
    read(Q, V);

    enqueue(&Q, &V, 1);
    read(Q, V);

    enqueue(&Q, &V, 2);
    enqueue(&Q, &V, 3);
    enqueue(&Q, &V, 4);
    read(Q, V);

    dequeue(&Q, &V);
    read(Q, V);

    Element temp = front(Q, V);
    printf("Front: %d\n", temp.data);

    dequeue(&Q, &V);
    dequeue(&Q, &V);
    dequeue(&Q, &V);
    read(Q, V);

    return 0;
}


void init(Queue *Q) {
    Q->front = -1;
    Q->rear = -1;
}

void read(Queue Q, VHeap V) {
    printf("Queue: ");

    if(isEmpty(Q)) {
        printf("EMPTY");
    }
    
    while(!isEmpty(Q)) {
        Element elem = front(Q, V);
        printf("%d ", elem.data);
        dequeue(&Q, &V);
    }
    printf("\n");
}

bool isEmpty(Queue Q) {
    return (Q.front == -1) ? true : false;
}

bool isFull(VHeap V) {
    return (V.avail == -1) ? true : false;
}

Element front(Queue Q, VHeap V) {
    Element temp = {-1};

    if(!isEmpty(Q)) {
        temp = V.VHNode[Q.front].elem;
    } 

    return temp;
}

void dequeue(Queue *Q, VHeap *V) {
    if(!isEmpty(*Q)) {
        int temp = Q->front;
        Q->front = V->VHNode[temp].next;
        freeVH(V, temp);

        if(isEmpty(*Q)) {
            Q->rear = -1;
        }
    }
}

void enqueue(Queue *Q, VHeap *V, int data) {
    if(!isFull(*V)) {
        int temp = mallocVH(V);
        if(temp != -1) {
            V->VHNode[temp].elem.data = data;
            V->VHNode[temp].next = -1;

            if(isEmpty(*Q)) {
                Q->front = temp;
            }
            else {
                V->VHNode[Q->rear].next = temp;
            }

            Q->rear = temp;
        }
    }
}


//CB General Functions

void initVH(VHeap *V) {
    V->avail = 0;

    for(int i = 1; i < VHSIZE; i++) {
        V->VHNode[i - 1].next = i; //set all default nexts to the next address
    }

    V->VHNode[VHSIZE - 1].next = -1; //set last address' next to -1
}

int mallocVH(VHeap *V) {
    int temp = V->avail; //temp gets the current available address to be returned

    if(temp != -1) {
        V->avail = V->VHNode[temp].next; //avail gets the next available address after it is assigned to temp
    }

    return temp;
}

void freeVH(VHeap *V, int index) {
    if(index >= 0 && index < VHSIZE) {
        V->VHNode[index].next = V->avail; //the address next gets the current available address
        V->avail = index; //the index to be freed becomes the new current available address
    }
}

void readNexts(VHeap V) {
    printf("Nexts: ");
    for(int i = 0; i < VHSIZE; i++) {
        printf("%d%s", V.VHNode[i].next, (V.VHNode[i].next == -1) ? ".\n" : ", ");
    }
}