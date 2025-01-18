#ifndef STACK_ARR_H
#define STACK_ARR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int top;
}Stack;

void init(Stack *S) {
    S->top = -1;
}

bool isFull(Stack S) {
    return (S.top == MAX - 1) ? true : false;
}

bool isEmpty(Stack S) {
    return (S.top == -1) ? true : false;
}

void push(Stack *S, int data) {
    if(!isFull(*S)) {
        S->elem[++S->top] = data;
    }
}

void pop(Stack *S) {
    if(!isEmpty(*S)) {
        S->top--;
    }
}

int top(Stack S) {
    return (isEmpty(S)) ? -1 : S.elem[S.top];
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