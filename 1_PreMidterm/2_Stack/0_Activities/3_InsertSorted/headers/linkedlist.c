#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void init(Stack *S) {
    *S = NULL;
}

void push(Stack *S, int data) {
    Stack temp = (Stack)malloc(sizeof(struct node));

    if(temp != NULL) {
        temp->data = data;
        temp->next = *S;
        *S = temp;
    }
}

void pop(Stack *S) {
    Stack temp = *S;

    if(temp != NULL) {
        *S = temp->next;
        free(temp);
    }
}

int peek(Stack S) {
    return (S != NULL) ? S->data : -1;
}

Stack popNoFree(Stack *S) {
    Stack temp = *S;

    if(temp != NULL) {
        *S = temp->next;
    }

    return temp;
}

void pushNoFree(Stack *S, Stack temp) {
    if(temp != NULL) {
        temp->next = *S;
        *S = temp;
    }
}

void insertSorted(Stack *S, int data) {
    Stack temp;
    init(&temp);

    while(*S != NULL && peek(*S) < data) {
        Stack t = popNoFree(S);
        pushNoFree(&temp, t);
    }

    push(S, data);

    while(temp != NULL) {
        Stack t = popNoFree(&temp);
        pushNoFree(S, t);
    }
}

void read(Stack S) {
    Stack temp;
    init(&temp);

    while(S != NULL) {
        printf("%d ", S->data);
        Stack t = popNoFree(&S);
    }

    printf("\n");
}