#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10 //number of elements that can be stored in the queue. MAX + 1 is the actual size of the circular array

typedef struct {
    int data;
} Element;

typedef struct {
    Element Elements[MAX + 1]; //one cell is sacrificed to identify if empty or full
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
    Queue->rear = MAX;
}

void read(Circular Queue) {
    printf("Queue: ");

    if(!isEmpty(Queue)) {
        int afterRear = (Queue.rear + 1) % (MAX + 1); //this is my way of doing it since i do not know the standard way of doing it yet
        for(int i = Queue.front; i != afterRear; i = ((i + 1) % (MAX + 1))) {
            printf("%d%s", Queue.Elements[i].data, (i !=  Queue.rear) ? ", " : ".\n");
        }
    }
    else {
        printf("EMPTY\n");
    }
}

bool isEmpty(Circular Queue) {
    return ((Queue.rear + 1) % (MAX + 1) == Queue.front) ? true : false;
}

bool isFull(Circular Queue) {
    return ((Queue.rear + 2) % (MAX + 1) == Queue.front) ? true : false;
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
        Queue->front = (Queue->front + 1) % (MAX + 1); 
    }
}

void enqueue(Circular *Queue, int data) {
    if(!isFull(*Queue)) {
        Queue->rear = (Queue->rear + 1) % (MAX + 1);
        Queue->Elements[Queue->rear].data = data;
    }
}
