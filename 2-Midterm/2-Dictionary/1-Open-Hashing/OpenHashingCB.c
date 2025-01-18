#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 0XA

typedef struct {
    int data;
    int next;
} Nodetype;

typedef struct {
    Nodetype Nodes[MAX];
    int avail;
} VHeap;

typedef int List;

typedef List Dictionary[MAX];

void initVH(VHeap *V);
int allocSpace(VHeap *V);
void deallocSpace(VHeap *V, List index);

void initDict(Dictionary D);
int hash(int data);
void insert(Dictionary D, VHeap *V, int data);
bool isMember(Dictionary D, VHeap V, int data);
void printDict(Dictionary D, VHeap V);

int main() {
    printf("\033[H\033[J");

    VHeap V;
    initVH(&V);

    Dictionary D;
    initDict(D);

    for(int i = 0; i < MAX; i++) {
        int temp;
        printf("Enter element %d: ", i + 1);
        scanf("%d", &temp);

        insert(D, &V, temp);
    }

    int find;
    printf("Enter element to be searched: ");
    scanf("%d", &find);

    printf("\nElement %s in the Dictionary.\n\n", (isMember(D, V, find)) ? "IS" : "IS NOT");

    printDict(D, V);

    return 0;
}

void initVH(VHeap *V) {
    V->avail = 0;

    for(int i = 1; i < MAX; i++) {
        V->Nodes[i - 1].next = i;
    }

    V->Nodes[MAX - 1].next = -1;
}

int allocSpace(VHeap *V) {
    List temp = V->avail;

    if(temp != -1) {
        V->avail = V->Nodes[temp].next;
    }

    return temp;
}

void deallocSpace(VHeap *V, List index) {
    if(index >= 0 && index < MAX) {
        V->Nodes[index].next = V->avail;
        V->avail = index;
    }
}

void initDict(Dictionary D) {
    for(int i = 0; i < MAX; i++) {
        D[i] = -1;
    }
}

int hash(int data) {
    return data % MAX;
}

void insert(Dictionary D, VHeap *V, int data) {
    List temp = allocSpace(V);

    if(temp != -1) {
        List *trav;
        int h = hash(data);

        for(trav = &D[h]; *trav != -1 && V->Nodes[*trav].data != data; trav = &V->Nodes[*trav].next) {}

        if(*trav == -1) {
            V->Nodes[temp].data = data;
            V->Nodes[temp].next = -1;
            *trav = temp;
        }
    }
}

bool isMember(Dictionary D, VHeap V, int data) {
    int temp = hash(data);
    List curr;

    for(curr = D[temp]; curr != -1 && V.Nodes[curr].data != data; curr = V.Nodes[curr].next) {}

    return curr == -1 ? false : true;
}

void printDict(Dictionary D, VHeap V) {
    for(int i = 0; i < MAX; i++) {
        if(D[i] == -1) {
            printf("EMPTY");
        }

        for(List curr = D[i]; curr != -1; curr = V.Nodes[curr].next) {
            printf("%d ", V.Nodes[curr].data);
        }

        printf("\n");
    }
}