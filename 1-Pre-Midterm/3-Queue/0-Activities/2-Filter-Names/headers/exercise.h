#ifndef EXERCISE_H
#define EXERCISE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 5

typedef struct
{
  char fname[30];
  char lname[30];
} Name;

typedef struct
{
  Name elems[MAX];
  int front;
  int rear;
} NQueue;

void initNQueue(NQueue *nq);
bool isEmpty(NQueue nq);
bool isFull(NQueue nq);
void displayQueue(NQueue nq);
bool enqueue(NQueue *nq, Name n);
bool dequeue(NQueue *nq);
Name front(NQueue nq);
Name *filterNames(NQueue *nq, char *filterString);
bool insertSorted(NQueue *nq, Name n);

#endif