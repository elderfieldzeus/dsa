#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int data;
} Element;

typedef struct node {
    Element *Elements;
    int top;
} *Version_Four;

// Initialize, insert, delete, member, locate, and other operations
void init(Version_Four *Stack);
void read(Version_Four Stack);
bool isEmpty(Version_Four Stack);
bool isFull(Version_Four Stack);
Element top(Version_Four Stack);
void pop(Version_Four Stack);
void push(Version_Four Stack, int data);


int main() {
    Version_Four Stack;
    
    printf("\033[H\033[J"); // clear screen
    
    init(&Stack);
    read(Stack);

    push(Stack, 1);
    read(Stack);

    push(Stack, 2);
    push(Stack, 3);
    read(Stack);

    Element temp = top(Stack);
    printf("Top: %d\n", temp.data);

    pop(Stack);
    read(Stack);

    return 0;
}

void init(Version_Four *Stack) {
    *Stack = (Version_Four) malloc(sizeof(struct node));
    (*Stack)->top = -1;
    (*Stack)->Elements = (Element*)malloc(sizeof(Element) * MAX);
}

void read(Version_Four Stack) {
    printf("Stack: ");
    for(int i = 0; i <= Stack->top; i++) {
        printf("%d%s", Stack->Elements[i].data, (i !=  Stack->top) ? ", " : ".\n");
    }
    if(isEmpty(Stack)) {
        printf("EMPTY\n");
    }
}

bool isEmpty(Version_Four Stack) {
    return (Stack->top == -1) ? true : false; 
}

bool isFull(Version_Four Stack) {
    return (Stack->top == MAX - 1) ? true : false;
}

Element top(Version_Four Stack) {
    Element d = {-1};
    return (!isEmpty(Stack)) ? Stack->Elements[Stack->top] : d;
}

void pop(Version_Four Stack) {
    if(!isEmpty(Stack)) {
        Stack->top--;
    }
}

void push(Version_Four Stack, int data) {
    if(!isFull(Stack)) {
        Stack->Elements[++Stack->top].data = data; 
    }
}