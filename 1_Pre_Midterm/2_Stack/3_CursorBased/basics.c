#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define VHSIZE 0XA

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

typedef int Stack;

// Top, Pop, Push, and other utility functions such as initStack, isEmpty, and isFull
void init(Stack *S);
void read(Stack S, VHeap V);
bool isEmpty(Stack S);
bool isFull(Stack S, VHeap V);
Element top(Stack S, VHeap V);
void pop(Stack *S, VHeap *V);
void push(Stack *S, VHeap *V, int data);

void initVH(VHeap *V);
int mallocVH(VHeap *V);
void freeVH(VHeap *V, int index);

void readNexts(VHeap V);

int main() {
    VHeap V;
    Stack S;

    printf("\033[H\033[J");

    initVH(&V);
    readNexts(V);

    init(&S);
    read(S, V);

    push(&S, &V, 1);
    read(S, V);

    push(&S, &V, 2);
    push(&S, &V, 3);
    read(S, V);

    Element temp = top(S, V);
    printf("Top: %d\n", temp.data);

    pop(&S, &V);
    read(S, V);

    return 0;
}

void init(Stack *S) {
    *S = -1;
}

void read(Stack S, VHeap V) {
    printf("Stack: ");
    for(int i = S; i != -1; i = V.VHNode[i].next) {
        printf("%d%s", V.VHNode[i].elem.data, (V.VHNode[i].next != -1) ? ", " : ".\n");
    }
    if(S == -1) {
        printf("EMPTY\n");
    }
}

bool isEmpty(Stack S) {
    return (S == -1) ? true : false;
}

bool isFull(Stack S, VHeap V) {
    int i = 0;

    for(int curr = S; curr != -1; curr = V.VHNode[curr].next, i++) {}

    return (i == VHSIZE) ? true : false;
}

Element top(Stack S, VHeap V) {
    Element top = {-1};

    if(!isEmpty(S)) {
        int i;
        for(i = S; V.VHNode[i].next != -1; i = V.VHNode[i].next) {}
        top = V.VHNode[i].elem;
    }

    return top;
}

void pop(Stack *S, VHeap *V) {
    if(!isEmpty(*S)) {
        int *trav;

        for(trav = S; V->VHNode[*trav].next != -1; trav = &V->VHNode[*trav].next) {}
        
        int temp = *trav;
        *trav = -1;
        freeVH(V, *trav);
    }
}

void push(Stack *S, VHeap *V, int data) {
    if(!isFull(*S, *V)) {
        int *trav;

        for(trav = S; *trav != -1; trav = &V->VHNode[*trav].next) {}

        int temp = mallocVH(V);
        if(temp != -1) {
            V->VHNode[temp].elem.data = data;
            V->VHNode[temp].next = -1;
            *trav = temp;
        }
    }
}


//general functions
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