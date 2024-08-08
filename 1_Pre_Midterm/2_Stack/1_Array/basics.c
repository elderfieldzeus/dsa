#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int data;
} Element;

typedef struct {
    Element Elements[MAX];
    int top; //index of stack top
} Stack;

// Top, Pop, Push, and other utility functions such as initStack, isEmpty, and isFull
void init(Stack *S);
void read(Stack S);
bool isEmpty(Stack S);
bool isFull(Stack S);
Element top(Stack S);
void pop(Stack *S);
void push(Stack *S, int data);


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

    Element temp = top(S);
    printf("Top: %d\n", temp.data);

    pop(&S);
    read(S);

    return 0;
}

void init(Stack *Stack) {
    Stack->top = -1;
}

void read(Stack S) {
    printf("Stack: ");
    for(int i = S.top; i >= 0; i--) {
        printf("%d%s", S.Elements[i].data, (i !=  0) ? ", " : ".\n");
    }
    if(isEmpty(S)) {
        printf("EMPTY\n");
    }
}

bool isEmpty(Stack S) {
    return (S.top == -1) ? true : false; 
}

bool isFull(Stack S) {
    return (S.top == MAX - 1) ? true : false;
}

Element top(Stack S) {
    Element d = {-1};
    return (!isEmpty(S)) ? S.Elements[S.top] : d;
}

void pop(Stack *S) {
    if(!isEmpty(*S)) {
        S->top--;
    }
}

void push(Stack *S, int data) {
    if(!isFull(*S)) {
        S->Elements[++S->top].data = data; 
    }
}


