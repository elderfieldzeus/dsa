/*
    NOTICE: THIS IMPLEMENTATION IS BASED SOLELY ON MY IDEA OF PARENT POINTER TREES. USE WISELY.
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef enum {
    NO_PARENT = -1,
    EMPTY = -2
} ParentStatus;

typedef struct {
    int data;
    int parent;
} Node;

typedef Node Tree[MAX];

void initTree(Tree T);
void insertTree(Tree T, int data, int nodeIndex, int parentIndex);
void printFromRoot(Tree T, int nodeIndex);

int main() {
    Tree T;

    initTree(T);
    
    // insert element for root
    insertTree(T, 100, MAX / 2, NO_PARENT);

    // populate left side of the tree
    for(int i = MAX / 2 - 1; i >= 0; i--) {
        insertTree(T, i, i, i + 1);
    }

    // populate right side of the tree
    for(int i = MAX / 2 + 1; i < MAX; i++) {
        insertTree(T, i, i, i - 1);
    }

    int node = 0;
    printf("From root up to node %d: ", node);
    printFromRoot(T, node);
}

void initTree(Tree T) {
    for(int i = 0; i < MAX; i++) {
        T[i].parent = EMPTY;
    }
}

void insertTree(Tree T, int data, int nodeIndex, int parentIndex) {
    T[nodeIndex].data = data;
    T[nodeIndex].parent = parentIndex;
}

// From root, print until node is found
void printFromRoot(Tree T, int nodeIndex) {
    if(T[nodeIndex].parent != NO_PARENT && T[nodeIndex].parent != EMPTY) {
        printFromRoot(T, T[nodeIndex].parent);
        printf("%d ", T[nodeIndex].data);
    }
}