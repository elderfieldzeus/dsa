/*

    THIS IS MY FIRST ATTEMPT AT STACK BASED ON MY KNOWLEDGE ON HOW A STACK SHOULD WORK
    NOTE: I THINK THIS IS WRONG BECAUSE IM NOT SUPPOSED TO TRAVERSE THE STACK LIKE A NORMAL LINKED LIST
    E.G. (isFull(), pop(), push())...
    I mean it still works, just wrong implementation...

*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int data;
} Element;

typedef struct node {
    Element elem;
    struct node *next;
} *LinkedList;

// Top, Pop, Push, and other utility functions such as initStack, isEmpty, and isFull
void init(LinkedList *Stack);
void read(LinkedList Stack);
bool isEmpty(LinkedList Stack);
bool isFull(LinkedList Stack);
Element top(LinkedList Stack);
void pop(LinkedList *Stack);
void push(LinkedList *Stack, int data);

void freeAll(LinkedList Stack);

int main() {
    LinkedList Stack;

    printf("\033[H\033[J");

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

    freeAll(Stack);

    return 0;
}

void init(LinkedList *Stack) {
    *Stack = NULL;
}

void read(LinkedList Stack) {
    printf("Stack: ");
    for(LinkedList curr = Stack; curr != NULL; curr = curr->next) {
        printf("%d%s", curr->elem.data, (curr->next != NULL) ? ", " : ".\n");
    }
    if(Stack == NULL) {
        printf("EMPTY\n");
    }
}

bool isEmpty(LinkedList Stack) {
    return (Stack == NULL) ? true : false;
}

bool isFull(LinkedList Stack) {
    //assuming MAX is the capacity of the stack
    int i = 0;
    for(LinkedList curr = Stack; curr != NULL; curr = curr->next, i++) {}

    return i == MAX ? true : false;
}

Element top(LinkedList Stack) {
    LinkedList curr;
    Element d = {-1};

    for(curr = Stack; curr->next != NULL; curr = curr->next) {}

    return (isEmpty(Stack)) ? d : curr->elem;
}

void pop(LinkedList *Stack) {
    if(!isEmpty(*Stack)) {
        LinkedList *trav, temp;

        for(trav = Stack; (*trav)->next != NULL; trav = &(*trav)->next) {}

        temp = (*trav);
        (*trav) = NULL;
        free(temp);
    }
}

void push(LinkedList *Stack, int data) {
    if(!isFull(*Stack)) {
        LinkedList *trav;

        for(trav = Stack; (*trav) != NULL; trav = &(*trav)->next) {}

        LinkedList temp = (LinkedList)malloc(sizeof(struct node));
        if(temp != NULL) {
            temp->elem.data = data;
            temp->next = NULL;
            (*trav) = temp;
        }
    }
}

void freeAll(LinkedList Stack) {
    LinkedList temp;

    while(Stack != NULL) {
        temp = Stack;
        Stack = Stack->next;
        free(temp);
    }
}