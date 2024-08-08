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

typedef struct {
    LinkedList front;
    LinkedList rear;
    int count; // only used for isFull() function to avoid traversing, can be removed !
} Queue;

// Front, Dequeue, Enqueue, and other utility functions such as initQueue, isEmpty, and isFull
void init(Queue *Q);
void read(Queue Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q); // i dont think this is necessary for linked list
Element front(Queue Q);
void dequeue(Queue *Q);
void enqueue(Queue *Q, int data);

int main() {
    Queue Q;

    printf("\033[H\033[J");

    init(&Q);
    read(Q);

    enqueue(&Q, 1);
    read(Q);

    enqueue(&Q, 2);
    enqueue(&Q, 3);
    enqueue(&Q, 4);
    read(Q);

    dequeue(&Q);
    read(Q);

    Element temp = front(Q);
    printf("Front: %d\n", temp.data);

    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);
    read(Q);

    return 0;
}

void init(Queue *Q) {
    Q->front = NULL;
    Q->rear = NULL;
    Q->count = 0;
}

void read(Queue Q) {
    printf("Queue: ");
    for(LinkedList curr = Q.front; curr != NULL; curr = curr->next) {
        printf("%d%s", curr->elem.data, (curr->next != NULL) ? ", " : ".\n");
    }
    if(isEmpty(Q)) {
        printf("EMPTY\n");
    }
}

bool isEmpty(Queue Q) {
    return (Q.front == NULL) ? true : false;
}

bool isFull(Queue Q) {
    //the other way of doing it without count is to traverse and count each element. but since traversing is not allowed, i decided a count was better (just for this). 
     return (Q.count == MAX) ? true : false;
}

Element front(Queue Q) {
    Element temp = {-1};

    if(!isEmpty(Q)) {
        temp = Q.front->elem;
    }

    return temp;
}

void dequeue(Queue *Q) {
    if(!isEmpty(*Q)) {
        LinkedList temp = Q->front;
        Q->front = Q->front->next;
        if(isEmpty(*Q)) {
            Q->rear = Q->front;
        }
        free(temp);
    } 
}

void enqueue(Queue *Q, int data) {
    if(!isFull(*Q)) { //can remove if there is no max given
        LinkedList temp = (LinkedList) malloc(sizeof(struct node));
        if(temp != NULL) {
            temp->elem.data = data;
            temp->next = NULL;
            
            if(isEmpty(*Q)) {
                Q->front = temp;
            }
            else {
                Q->rear->next = temp;
            }

            Q->rear = temp;
        }
    }
}