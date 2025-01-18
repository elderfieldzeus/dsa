#ifndef QUEUE_ARR_H
#define QUEUE_ARR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

typedef struct node {
    int data;
    struct node *next;
} *LIST;

typedef struct {
    LIST front;
    LIST rear;
}Queue;

void init(Queue *Q) {
    Q->front = Q->rear = NULL;
}

bool isFull(Queue Q) {
    return false;
}

bool isEmpty(Queue Q) {
    return (Q.front == NULL) ? true : false;
}

void enqueue(Queue *Q, int data) {
    LIST temp = (LIST) malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->data = data;
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

void dequeue(Queue *Q) {
    if(!isEmpty(*Q)) {
        LIST temp = Q->front;
        Q->front = temp->next;
        free(temp);
        if(isEmpty(*Q)) {
            Q->rear = NULL;
        }
    }
}

int front(Queue Q) {
    return (isEmpty(Q)) ? -1 : Q.front->data;
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

    printf("\n");
}

#endif