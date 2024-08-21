#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 0XA

typedef struct {
    int elem[MAX];
    int top;
} Stack;

Stack populateStack();
void read(Stack S);
int top(Stack S);
void push(Stack *S, int data);
void pop(Stack *S);
bool isFull(Stack S);
bool isEmpty(Stack S);

int prompt();
bool isFound(Stack S, int elem);

int main() {
    Stack S = populateStack();
    read(S);

    int toSearch = prompt(); 
    printf("%d %s IN THE STACK!!!\n", toSearch, isFound(S, toSearch) ? "IS" : "IS NOT");

    return 0;
}

Stack populateStack() {
    Stack S = {.top = -1};

    for(int i = 1; i <= MAX;) {
        int temp;
        printf("Enter element #%d (POSITIVE ONLY): ", i);
        scanf("%d", &temp);

        if(temp < 0) continue;

        push(&S, temp);
        i++;
    }

    return S;
}

void read(Stack S) {
    printf("Stack: ");
    for(int i = S.top; i >= 0; i--) {
        printf("%d%s", top(S), i != 0 ? ", " : ".\n");
        pop(&S);
    }
}

int top(Stack S) {
    return (isEmpty(S)) ? -1 : S.elem[S.top];
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

bool isFull(Stack S) { 
    return (S.top == MAX - 1) ? true : false;
}

bool isEmpty(Stack S) { 
    return (S.top == -1) ? true : false;
}

int prompt() {
    int temp;

    printf("Enter number to be searched: ");
    scanf("%d", &temp);

    return temp;
}

bool isFound(Stack S, int elem) {
    while(!isEmpty(S) && elem != top(S)) {
        pop(&S);
    }

    return isEmpty(S) ? false : true;
}