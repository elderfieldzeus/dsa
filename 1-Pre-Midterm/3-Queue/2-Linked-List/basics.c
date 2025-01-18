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
} Queue;

// Front, Dequeue, Enqueue, and other utility functions such as initQueue, isEmpty, and isFull
void init(Queue *Q);
void read(Queue Q);
bool isEmpty(Queue Q);
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
}

void read(Queue Q) {
    printf("Queue: ");

    if(isEmpty(Q)) {
        printf("EMPTY\n");
    }
    else {
        LinkedList stop = Q.front;

        do {
            Element elem = front(Q);
            printf("%d ", elem.data);

            LinkedList temp = Q.front;

            // dequeue
            Q.front = Q.front->next; 

            if(Q.front == NULL) {
                Q.rear = NULL;
            }

            // enqueue
            temp->next = NULL;
            if(Q.front == NULL) {
                Q.front = temp;
            }
            else {
                Q.rear->next = temp;
            }
            Q.rear = temp;
        } while (Q.front != stop);
        printf("\n");
    }
}

bool isEmpty(Queue Q) {
    return (Q.front == NULL) ? true : false;
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
            Q->rear = NULL;
        }
        free(temp);
    } 
}

void enqueue(Queue *Q, int data) {
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