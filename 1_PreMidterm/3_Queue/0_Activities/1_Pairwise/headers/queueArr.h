#ifndef QUEUE_ARR_H
#define QUEUE_ARR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int front;
    int rear;
}Queue;

void init(Queue *Q) {
    Q->front = 0;
    Q->rear = -1;
}

bool isFull(Queue Q) {
    return (Q.front == (Q.rear + 2) % MAX) ? true : false;
}

bool isEmpty(Queue Q) {
    return (Q.front == (Q.rear + 1) % MAX) ? true : false;
}

void enqueue(Queue *Q, int data) {
    if(!isFull(*Q)) {
        Q->rear = (Q->rear + 1) % MAX;
        Q->elem[Q->rear] = data;
    }
}

void dequeue(Queue *Q) {
    if(!isEmpty(*Q)) {
        Q->front = (Q->front + 1) % MAX;
    }
}

int front(Queue Q) {
    return (isEmpty(Q)) ? -1 : Q.elem[Q.front];
}

void print(Queue *Q) {
    if(isEmpty(*Q)) {
        printf("EMPTY");
    }
    else {
        Queue temp;
        init(&temp);

        while(!isEmpty(*Q)) {
            int data = front(*Q);

            printf("%d ", data);

            dequeue(Q);
            enqueue(&temp, data);
        }

        *Q = temp;
    }

    // int end = (Q->rear + 1) % MAX;

    // while(Q->front != end) {
    //     int data = front(*Q);

    //     printf("%d ", data);

    //     dequeue(Q);
    //     enqueue(Q, data);
    // }

    printf("\n");
}

#endif