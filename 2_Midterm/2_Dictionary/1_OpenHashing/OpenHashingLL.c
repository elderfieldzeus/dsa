#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 10

typedef struct node {
    int data;
    struct node *next;
} *Nodetype;

typedef Nodetype Dictionary[MAX];

// dictionary functions
void initDict(Dictionary D);
int hash(int data);
void insert(Dictionary D, int data);
bool inDict(Dictionary D, int data);
void delete(Dictionary D, int data);
void printDict(Dictionary D);

// helper functions
int* getInput(int *size);
void populateDict(Dictionary D, int arr[], int size);
void askToAdd(Dictionary D);
void askToDelete(Dictionary D);
int cont();


int main() {
    printf("\033[H\033[J");

    Dictionary D;
    int size, choice;
    int *arr = getInput(&size);

    initDict(D);
    populateDict(D, arr, size);

    do {
        askToAdd(D);
        askToDelete(D);
        choice = cont();
    } while(choice != 0);

    printDict(D);

    return 0;
}

int* getInput(int *size) {
    int *arr;

    printf("Enter size: ");
    scanf("%d", size);

    arr = (int*)malloc(sizeof(int) * (*size));

    for(int i = 0; i < *size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", arr + i);
    }

    return arr;
}

void populateDict(Dictionary D, int arr[], int size) {
    for(int i = 0; i < size; i++) {
        insert(D, arr[i]);
    }
}


void initDict(Dictionary D) {
    for(int i = 0; i < MAX; i++) {
        D[i] = NULL;
    }
}

int hash(int data) {
    return data % MAX;
}

void insert(Dictionary D, int data) {
    int index = hash(data);

    Nodetype *trav;

    for(trav = &D[index]; *trav != NULL && (*trav)->data != data; trav = &(*trav)->next) {}

    if(*trav == NULL) {
        Nodetype temp = (Nodetype)malloc(sizeof(struct node));

        if(temp != NULL) {
            temp->data = data;
            temp->next = NULL;
            *trav = temp;
        }
    }
}

void askToAdd(Dictionary D) {
    int data;
    printf("Enter element to find: ");
    scanf("%d", &data);

    printf("The element %s in the Dictionary\n", (inDict(D, data) == true) ? "IS" : "IS NOT");
}

bool inDict(Dictionary D, int data) {
    int index = hash(data);

    Nodetype curr;

    for(curr = D[index]; curr != NULL && curr->data != data; curr = curr->next) {}

    return (curr != NULL) ? true : false;
}

void askToDelete(Dictionary D) {
    int data;
    printf("Enter element to delete: ");
    scanf("%d", &data);

    delete(D, data);  
}

void delete(Dictionary D, int data) {
    int index = hash(data);

    Nodetype *trav;

    for(trav = &D[index]; *trav != NULL && (*trav)->data != data; trav = &(*trav)->next) {}

    if(*trav != NULL) {
        Nodetype temp = *trav;
        *trav = temp->next;
        free(temp);
    }
}

int cont() {
    char c;
    printf("Do you want to continue? [y/n]: ");
    scanf(" %c", &c);

    return (tolower(c) == 'y') ? 1 : 0;
}

void printDict(Dictionary D) {
    for(int i = 0; i < MAX; i++) {
        printf("Row %d: ", i);

        for(Nodetype curr = D[i]; curr != NULL; curr = curr->next) {
            printf("%d ", curr->data);
        }

        printf("\n");
    }
}