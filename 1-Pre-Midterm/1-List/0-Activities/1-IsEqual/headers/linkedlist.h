#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TRUE,
    FALSE
} boolean;

typedef struct node {
    int data;
    struct node *next;
} *List;

boolean isEqualNotSorted(List A, List B);
boolean isEqualSorted(List A, List B);

void initList(List *L);
void insertFirst(List *L, int data);
void deleteFirst(List *L);

void populate(List *L, int arr[], int size);
void sort(List L);
void printList(List L);
void freeAll(List *L);

#endif