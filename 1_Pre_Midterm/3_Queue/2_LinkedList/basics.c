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

void init(LinkedList *Queue);
void read(LinkedList Queue);
bool isEmpty(LinkedList Queue);
bool isFull(LinkedList Queue);
Element front(LinkedList Queue);
void dequeue(LinkedList *Queue);
void enqueue(LinkedList *Queue, int data);

int main() {
    LinkedList Queue;

    printf("\033[H\033[J");

    init(&Queue);
    read(Queue);

    enqueue(&Queue, 1);
    read(Queue);

    enqueue(&Queue, 2);
    enqueue(&Queue, 3);
    enqueue(&Queue, 4);
    read(Queue);

    dequeue(&Queue);
    read(Queue);

    Element temp = front(Queue);
    printf("Front: %d\n", temp.data);

    dequeue(&Queue);
    dequeue(&Queue);
    dequeue(&Queue);
    read(Queue);

    return 0;
}

void init(LinkedList *Queue) {
    *Queue = NULL;
}

void read(LinkedList Queue) {
    printf("Queue: ");
    for(LinkedList curr = Queue; curr != NULL; curr = curr->next) {
        printf("%d%s", curr->elem.data, (curr->next != NULL) ? ", " : ".\n");
    }

    if(Queue == NULL) {
        printf("EMPTY\n");
    }
}

bool isEmpty(LinkedList Queue) {
    return Queue == NULL ? true : false;
}

bool isFull(LinkedList Queue) {
    int i = 0;

    for(LinkedList curr = Queue; curr != NULL; curr = curr->next, i++) {}

    return (i == MAX) ? true : false;
}

Element front(LinkedList Queue) {
    Element temp = {-1};

    if(!isEmpty(Queue)) {
        temp = Queue->elem;
    }

    return temp;
}

void dequeue(LinkedList *Queue) {
    if(!isEmpty(*Queue)) {
        LinkedList temp = *Queue;
        *Queue = (*Queue)->next;
        free(temp);
    }
}

void enqueue(LinkedList *Queue, int data) {
    if(!isFull(*Queue)) {
        LinkedList *trav, temp;

        for(trav = Queue; (*trav) != NULL; trav = &(*trav)->next) {}
        
        temp = (LinkedList)malloc(sizeof(struct node));
        if(temp != NULL) {
            temp->elem.data = data;
            temp->next = NULL;
            *trav = temp;
        }
    }
}