#ifndef CB_H
#define CB_H

#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef enum {
    TRUE,
    FALSE
} boolean;

typedef struct {
    int data;
    int next;
} Nodetype;

typedef struct {
    Nodetype Nodes[MAX];
    int Avail;
} VHeap;

typedef int List;

boolean isEqualNotSorted(VHeap V, List A, List B);
boolean isEqualSorted(VHeap V, List A, List B);

void initVH(VHeap *V);
List mallocVH(VHeap *V);
void freeVH(VHeap *V, int index);

void initList(List *L);
void insertFirst(VHeap *V, List *L, int data);
void deleteFirst(VHeap *V, List *L);

void populate(VHeap *V, List *L, int arr[], int size);
void sort(VHeap *V, List L);
void printList(VHeap V, List L);
void freeAll(VHeap *V, List *L);

#endif