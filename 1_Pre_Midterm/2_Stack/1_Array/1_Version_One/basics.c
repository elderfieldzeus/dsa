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
} Version_One;

// Top, Pop, Push, and other utility functions such as initStack, isEmpty, and isFull
void init(Version_One *Stack);
void read(Version_One Stack);
bool isEmpty(Version_One Stack);
bool isFull(Version_One Stack);
Element top(Version_One Stack);
void pop(Version_One *Stack);
void push(Version_One *Stack, int data);


int main() {
    Version_One Stack;
    
    printf("\033[H\033[J"); // clear screen
    
    init(&Stack);
    read(Stack);

    push(&Stack, 1);
    read(Stack);

    push(&Stack, 2);
    push(&Stack, 3);
    read(Stack);

    Element temp = top(Stack);
    printf("Top: %d\n", temp.data);

    pop(&Stack);
    read(Stack);

    return 0;
}

void init(Version_One *Stack) {
    Stack->top = -1;
}

void read(Version_One Stack) {
    printf("Stack: ");
    for(int i = 0; i <= Stack.top; i++) {
        printf("%d%s", Stack.Elements[i].data, (i !=  Stack.top) ? ", " : ".\n");
    }
    if(isEmpty(Stack)) {
        printf("EMPTY\n");
    }
}

bool isEmpty(Version_One Stack) {
    return (Stack.top == -1) ? true : false; 
}

bool isFull(Version_One Stack) {
    return (Stack.top == MAX - 1) ? true : false;
}

Element top(Version_One Stack) {
    Element d = {-1};
    return (!isEmpty(Stack)) ? Stack.Elements[Stack.top] : d;
}

void pop(Version_One *Stack) {
    if(!isEmpty(*Stack)) {
        Stack->top--;
    }
}

void push(Version_One *Stack, int data) {
    if(!isFull(*Stack)) {
        Stack->Elements[++Stack->top].data = data; 
    }
}

