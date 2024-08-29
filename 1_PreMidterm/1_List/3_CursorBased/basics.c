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

typedef int List;

// Initialize, insert, delete, member, locate, and other operations
void init(List *L);
void read(List L, VHeap V);
void insertFirst(List *L, VHeap *V, int data);
void insertLast(List *L, VHeap *V, int data);
void delete(List *L, VHeap *V, int data);
bool member(List L, VHeap V, int data);
int locate(List L, VHeap V, int data);

//CursorBased Functions
void initVH(VHeap *V);
int mallocVH(VHeap *V);
void freeVH(VHeap *V, int index);

//for debugging only
void readNexts(VHeap V);

int main() {
    VHeap V;
    List L;

    printf("\033[H\033[J");

    initVH(&V);
    // readNexts(V); //debug

    init(&L);
    read(L, V);

    insertFirst(&L, &V, 1);
    read(L, V);

    insertLast(&L, &V, 2);
    read(L, V);

    delete(&L, &V, 1);
    read(L, V);

    printf("%s\n", member(L, V, 1) ? "TRUE" : "FALSE");

    printf("%d\n", locate(L, V, 2));

    return 0;
}

void init(List *L) {
    *L = -1;
}

void read(List L, VHeap V) {
    printf("CB List: ");

    for(int i = L; i != -1; i = V.VHNode[i].next) {
        printf("%d%s", V.VHNode[i].elem.data, (V.VHNode[i].next == -1) ? ".\n" : ", ");
    }

    if(L == -1) {
        printf("EMPTY\n");
    }
}

void insertFirst(List *L, VHeap *V, int data) {
    if(V->avail != -1) {
        int avail = mallocVH(V);
        if(avail != -1) {
            V->VHNode[avail].elem.data = data;
            V->VHNode[avail].next = *L;
            *L = avail;
        }
    }
}

void insertLast(List *L, VHeap *V, int data) {
    if(V->avail != -1) {
        int *curr;

        for(curr = L; (*curr) != -1; curr = &(V->VHNode[*curr].next)) {}

        int avail = mallocVH(V);
        if(avail != -1) {
            V->VHNode[avail].elem.data = data;
            V->VHNode[avail].next = -1;
            
            *curr = avail;
        }

    }
}

void delete(List *L, VHeap *V, int data) {
    int *curr;
    for(curr = L; *curr != -1 && V->VHNode[*curr].elem.data != data; curr = &V->VHNode[*curr].next) {}

    if(*curr != -1) {
        int temp = *curr;
        *curr = V->VHNode[*curr].next;
        freeVH(V, temp);
    }
}

bool member(List L, VHeap V, int data) {
    int curr;

    for(curr = L; curr != -1 && V.VHNode[curr].elem.data != data; curr = V.VHNode[curr].next) {}
    
    return (curr == -1) ? false : true;
}

int locate(List L, VHeap V, int data) {
    int curr;

    for(curr = L; curr != -1 && V.VHNode[curr].elem.data != data; curr = V.VHNode[curr].next) {}
    
    return curr;
}

//CURSOR BASED FUNCTIONS

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