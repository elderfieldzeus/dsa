#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} *Stack;

// Top, Pop, Push, and other utility functions such as initStack, isEmpty, and isFull
void init(Stack *S);
void read(Stack S);
bool isEmpty(Stack S);
bool isFull(Stack S);
int top(Stack S);
void pop(Stack *S);
void push(Stack *S, int data);

void freeAll(Stack S);

int main() {
    Stack S;

    printf("\033[H\033[J"); // clear screen
    
    init(&S);
    read(S);

    push(&S, 1);
    read(S);

    push(&S, 2);
    push(&S, 3);
    read(S);

    int temp = top(S);
    printf("Top: %d\n", temp);

    pop(&S);
    read(S);

    freeAll(S);

    return 0;
}

void init(Stack *S) {
    *S = NULL;
}

void read(Stack S) {
    Stack temp;
    init(&temp);

    printf("Stack: ");

    if(isEmpty(S)) {
        printf("EMPTY");
    }

    while(!isEmpty(S)) {
        printf("%d ", top(S));

        Stack t = S;
        S = S->next;

        t->next = temp;
        temp = t;
    }

    while(!isEmpty(temp)) {
        Stack t = temp;
        temp = temp->next;

        t->next = S;
        S = t;
    }

    printf("\n");
}

bool isEmpty(Stack S) {
    return (S == NULL) ? true : false;
}

int top(Stack S) {
    return (!isEmpty(S)) ? S->data : -1;
}

void pop(Stack *S) {
    if(!isEmpty(*S)) {
        Stack temp = (*S);
        (*S) = temp->next;
        free(temp);
    }
}

void push(Stack *S, int data) {
    Stack temp = (Stack)malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->data = data;
        temp->next = *S;
        (*S) = temp;
    }
}

void freeAll(Stack S) {
    Stack temp;

    while(S != NULL) {
        temp = S;
        S = S->next;
        free(temp);
    }
}