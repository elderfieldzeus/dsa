#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUM_OF_ELEMENTS 10 //number of elements that can be stored in the queue. 
#define MAX (NUM_OF_ELEMENTS + 1) //number of elements + 1 is the actual size of the circular array

typedef struct {
    int data;
} Element;

typedef struct {
    Element Elements[MAX]; //one cell is sacrificed to identify if empty or full
    int front;
    int rear;
} Circular;

// Front, Dequeue, Enqueue, and other utility functions such as initQueue, isEmpty, and isFull
void init(Circular *Queue);
void read(Circular Queue);
bool isEmpty(Circular Queue);
bool isFull(Circular Queue);
Element front(Circular Queue);
void dequeue(Circular *Queue);
void enqueue(Circular *Queue, int data);

int main() {
    Circular Queue;

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

void init(Circular *Queue) {
    Queue->front = 0;
    Queue->rear = MAX - 1;
}

void read(Circular Queue) {
    printf("Queue: ");

    if(isEmpty(Queue)) {
        printf("EMPTY\n");
    }

    while(!isEmpty(Queue)) {
        Element F = front(Queue);
        printf("%d", F.data);
        dequeue(&Queue);
        printf("%s", (!isEmpty(Queue)) ? ", " : ".\n");
    }
}

bool isEmpty(Circular Queue) {
    return ((Queue.rear + 1) % (MAX) == Queue.front) ? true : false;
}

bool isFull(Circular Queue) {
    return ((Queue.rear + 2) % (MAX) == Queue.front) ? true : false;
}

Element front(Circular Queue) {
    Element temp = {-1};

    if(!isEmpty(Queue)) {
        temp = Queue.Elements[Queue.front];
    }

    return temp;
}

void dequeue(Circular *Queue) {
    if(!isEmpty(*Queue)) {
        Queue->front = (Queue->front + 1) % (MAX); 
    }
}

void enqueue(Circular *Queue, int data) {
    if(!isFull(*Queue)) {
        Queue->rear = (Queue->rear + 1) % (MAX);
        Queue->Elements[Queue->rear].data = data;
    }
}
