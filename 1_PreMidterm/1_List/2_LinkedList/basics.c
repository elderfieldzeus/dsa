#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int data;
} Element;

typedef struct node {
    Element elem;
    struct node *next;
} *LinkedList;

// Initialize, insert, delete, member, locate, and other operations
void init(LinkedList *List);
void read(LinkedList List);
void insertFirst(LinkedList *List, int data);
void insertLast(LinkedList *List, int data);
void delete(LinkedList *List, int data);
bool member(LinkedList List, int data);
int locate(LinkedList List, int data);

void freeAll(LinkedList List);

int main() {
    LinkedList List;

    printf("\033[H\033[J");

    init(&List);
    read(List);

    insertFirst(&List, 1);
    read(List);

    insertLast(&List, 2);
    read(List);

    delete(&List, 2);
    read(List);

    printf("%s\n", member(List, 1) ? "TRUE" : "FALSE");

    printf("%d\n", locate(List, 1));

    freeAll(List);

    return 0;
}

void init(LinkedList *List) {
    *List = NULL;
}

void read(LinkedList List) {
    printf("List: ");
    for(LinkedList curr = List; curr != NULL; curr = curr->next) {
        printf("%d%s", curr->elem.data, (curr->next != NULL) ? ", " : ".\n");
    }
    if(List == NULL) {
        printf("EMPTY\n");
    }
}

void insertFirst(LinkedList *List, int data) { 
    LinkedList temp = (LinkedList)malloc(sizeof(struct node));
    
    if(temp == NULL) {
        printf("ERROR IN MALLOC");
        return;
    }

    temp->elem.data = data;
    temp->next = *List;

    *List = temp;
}

void insertLast(LinkedList *List, int data) {
    LinkedList *trav;

    for(trav = List; (*trav) != NULL; trav = &(*trav)->next) {}

    LinkedList temp = (LinkedList)malloc(sizeof(struct node));

    if(temp == NULL) {
        printf("ERROR IN MALOC");
        return;
    }

    temp->elem.data = data;
    temp->next = NULL;

    *trav = temp;
}

void delete(LinkedList *List, int data) {
    LinkedList *trav;

    for(trav = List; (*trav) != NULL && (*trav)->elem.data != data; trav = &(*trav)->next) {}

    if(*trav != NULL) {
        LinkedList temp = *trav;

        *trav = temp->next;
        free(temp);
    }
}

bool member(LinkedList List, int data) {
    LinkedList curr;

    for(curr = List; curr != NULL && curr->elem.data != data; curr = curr->next) {}

    return (curr == NULL) ? false : true;
}

int locate(LinkedList List, int data) {
    int index = 0;
    LinkedList curr;

    for(curr = List; curr != NULL && curr->elem.data != data; curr = curr->next, index++) {}

    return (curr == NULL) ? -1 : index;
}

void freeAll(LinkedList List) {
    LinkedList temp;
    while(List != NULL) {
        temp = List;
        List = temp->next;
        free(temp);
    }
}