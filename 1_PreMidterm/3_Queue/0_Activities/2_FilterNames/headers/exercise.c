#include "./exercise.h"

void initNQueue(NQueue *nq)
{
  nq->front = 1;
  nq->rear = 0;
}

bool isEmpty(NQueue nq)
{
  return (nq.rear + 1) % MAX == nq.front ? true : false;
}

bool isFull(NQueue nq)
{
  return (nq.rear + 2) % MAX == nq.front ? true : false;
}

void displayQueue(NQueue nq)
{
  int stop = (nq.rear + 1) % MAX;

  while (nq.front != stop)
  {
    Name data = front(nq);
    printf("%s %s\n", data.fname, data.lname);

    dequeue(&nq);
    enqueue(&nq, data);
  }
}

bool enqueue(NQueue *nq, Name n)
{
  bool status = false;

  if (!isFull(*nq))
  {
    nq->rear = (nq->rear + 1) % MAX;
    nq->elems[nq->rear] = n;
    status = true;
  }

  return status;
}

bool dequeue(NQueue *nq)
{
  bool status = false;

  if (!isEmpty(*nq))
  {
    nq->front = (nq->front + 1) % MAX;
    status = true;
  }

  return status;
}

Name front(NQueue nq)
{
  Name def = {"XXXX", "XXXXX"};

  return (isEmpty(nq)) ? def : nq.elems[nq.front];
}

/*Removes the names that matches the filterString to the lastname.
  Returns the removed names. Use the concept of adding a sentinel
  at the end indicating the last item in list as empty strings for
  fname and lname. If there are no names that will match then the
  function should return the sentinel.*/
Name *filterNames(NQueue *nq, char *filterString)
{
  Name temp[MAX];
  int tCount = 0;

  int stop = (nq->rear + 1) % MAX;

  while (!isEmpty(*nq) && nq->front != stop)
  {
    Name data = front(*nq);
    dequeue(nq);
    if (strcmp(data.lname, filterString) == 0)
    {
      temp[tCount++] = data;
    }
    else
    {
      enqueue(nq, data);
    }
  }

  Name *removed = (Name *)malloc(sizeof(Name) * (tCount + 1));
  memcpy(removed, temp, sizeof(Name) * tCount);

  strcpy(removed[tCount].lname, "END");

  return removed;
}

/*Insert soreted base on lastname. Rember to use the property
  of the queue but without using the functions (enqueue, dequeue, front)*/
bool insertSorted(NQueue *nq, Name n)
{
  bool status = false;
  if (!isFull(*nq))
  {
    int stop = (nq->rear + 1) % MAX;

    while (nq->front != stop && strcmp(nq->elems[nq->front].lname, n.lname) < 0)
    {
      nq->rear = (nq->rear + 1) % MAX;
      nq->elems[nq->rear] = nq->elems[nq->front];
      nq->front = (nq->front + 1) % MAX;
    }

    nq->rear = (nq->rear + 1) % MAX;
    nq->elems[nq->rear] = n;

    while (nq->front != stop)
    {
      nq->rear = (nq->rear + 1) % MAX;
      nq->elems[nq->rear] = nq->elems[nq->front];
      nq->front = (nq->front + 1) % MAX;
    }

    status = true;
  }

  return status;
}