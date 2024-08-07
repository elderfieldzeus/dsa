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

typedef int Queue;


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
    *Q = -1;
}

void read(Queue Q, VHeap V) {
    printf("Queue: ");
    for(int i = Q; i != -1; i = V.VHNode[i].next) {
        printf("%d%s", V.VHNode[i].elem.data, (V.VHNode[i].next != -1) ? ", " : ".\n");
    }
    if(Q == -1) {
        printf("EMPTY\n");
    }
}

bool isEmpty(Queue Q) {
    return (Q == -1) ? true : false;
}

bool isFull(VHeap V) {
    return (V.avail == -1) ? true : false;
}

Element front(Queue Q, VHeap V) {
    Element temp = {-1};

    if(!isEmpty(Q)) {
        temp = V.VHNode[Q].elem;
    } 

    return temp;
}

void dequeue(Queue *Q, VHeap *V) {
    if(!isEmpty(*Q)) {
        int temp = *Q;
        *Q = V->VHNode[temp].next;
        freeVH(V, temp);
    }
}

void enqueue(Queue *Q, VHeap *V, int data) {
    if(!isFull(*V)) {
        int *trav;
        for(trav = Q; *trav != -1; trav = &V->VHNode[*trav].next) {}
        int temp = mallocVH(V);
        if(temp != -1) {
            V->VHNode[temp].elem.data = data;
            V->VHNode[temp].next = -1;
            *trav = temp;
        }
    }
}


//CB General Functions

void initVH(VHeap *V) {
    V->avail = 0;

    for(int i = 0; i < VHSIZE; i++) {
        V->VHNode[i].next = i + 1;
    }

    V->VHNode[VHSIZE - 1].next = -1;
}

int mallocVH(VHeap *V) {
    int temp = -1;

    if(V->avail != -1) {
        temp = V->avail;
        V->avail = V->VHNode[temp].next;
    }

    return temp;
}

void freeVH(VHeap *V, int index) {
    if(index > 0 && index < VHSIZE) {
        V->VHNode[index].next = V->avail;
        V->avail = index;
    }
}

void readNexts(VHeap V) {
    printf("Nexts: ");
    for(int i = 0; i < VHSIZE; i++) {
        printf("%d%s", V.VHNode[i].next, (V.VHNode[i].next == -1) ? ".\n" : ", ");
    }
}