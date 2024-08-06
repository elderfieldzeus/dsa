#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int data;
} Element;

typedef struct {
    Element *Elements;
    int top;
} Version_Three;

// Initialize, insert, delete, member, locate, and other operations
void init(Version_Three *Stack);
void read(Version_Three Stack);
bool isEmpty(Version_Three Stack);
bool isFull(Version_Three Stack);
Element top(Version_Three Stack);
void pop(Version_Three *Stack);
void push(Version_Three *Stack, int data);


int main() {
    Version_Three Stack;
    
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

void init(Version_Three *Stack) {
    Stack->top = -1;
    Stack->Elements = (Element*)malloc(sizeof(Element) * MAX);
    Stack->Elements[0].data = 1;
}

void read(Version_Three Stack) {
    printf("Stack: ");
    for(int i = 0; i <= Stack.top; i++) {
        printf("%d%s", Stack.Elements[i].data, (i !=  Stack.top) ? ", " : ".\n");
    }
    if(isEmpty(Stack)) {
        printf("EMPTY\n");
    }
}

bool isEmpty(Version_Three Stack) {
    return (Stack.top == -1) ? true : false; 
}

bool isFull(Version_Three Stack) {
    return (Stack.top == MAX - 1) ? true : false;
}

Element top(Version_Three Stack) {
    Element d = {-1};
    return (!isEmpty(Stack)) ? Stack.Elements[Stack.top] : d;
}

void pop(Version_Three *Stack) {
    if(!isEmpty(*Stack)) {
        Stack->top--;
    }
}

void push(Version_Three *Stack, int data) {
    if(!isFull(*Stack)) {
        Stack->Elements[++Stack->top].data = data; 
    }
}