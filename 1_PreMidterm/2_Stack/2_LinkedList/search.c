#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 0XA

typedef struct node {
    int data;
    struct node *next;
} *Stack;

Stack populateStack();
void read(Stack S);
int top(Stack S);
void push(Stack *S, int data);
void pop(Stack *S);
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
    Stack S = NULL;

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
    while(!isEmpty(S)) {
        printf("%d%s", top(S), (S->next != NULL) ? ", " : ".\n");
        pop(&S);
    }
}

int top(Stack S) {
    return (isEmpty(S)) ? -1 : S->data;
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
    if(!isEmpty(*S)) {
        Stack temp = *S;
        *S = temp->next;
        // free(temp);
    }
}

bool isEmpty(Stack S) {
    return (S == NULL) ? true : false;
}

int prompt() {
    int temp;

    printf("Enter number to be searched: ");
    scanf("%d", &temp);

    return temp;
}

bool isFound(Stack S, int elem) { //maybe not the right way to search for element in stack because the 'free()' breaks it haha idk just trying
    while(!isEmpty(S) && elem != top(S)) {
        pop(&S);
    }

    return isEmpty(S) ? false : true;
}