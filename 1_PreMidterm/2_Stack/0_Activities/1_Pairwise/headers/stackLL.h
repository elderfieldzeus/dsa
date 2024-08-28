#ifndef QUEUE_ARR_H
#define QUEUE_ARR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

typedef struct node {
    int data;
    struct node *next;
} *LIST;

typedef struct {
    LIST top;
} Stack;

void init(Stack *S) {
    S->top = NULL;
}

bool isFull(Stack S) {
    return false;
}

bool isEmpty(Stack S) {
    return (S.top == NULL) ? true : false;
}

void push(Stack *S, int data) {
    LIST temp = (LIST)malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->data = data;
        temp->next = S->top;
        S->top = temp;
    } 
}

void pop(Stack *S) {
    if(!isEmpty(*S)) {
        LIST temp = S->top;
        S->top = temp->next;
        free(temp);
    }
}

int top(Stack S) {
    return (isEmpty(S)) ? -1 : S.top->data;
}

void print(Stack *S) {
    if(isEmpty(*S)) {
        printf("EMPTY");
    }
    else {
        Stack temp;
        init(&temp);

        while(!isEmpty(*S)) {
            int data = top(*S);

            printf("%d ", data);

            pop(S);
            push(&temp, data);
        }

        while(!isEmpty(temp)) {
            push(S, top(temp));
            pop(&temp);
        }

    }

    printf("\n");
}

#endif