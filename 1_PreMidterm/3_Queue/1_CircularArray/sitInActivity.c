#include <stdio.h>
#define MAX 10
#define QUEUEMAX (MAX + 1)

typedef struct {
	int elem[QUEUEMAX];
	int front;
	int back;
}Queue;

// QUEUE
 
void initQueue(Queue *Q);
void enqueue(Queue *Q, int data);
int dequeue(Queue *Q);
int front(Queue Q);
int isFullQ(Queue Q);
int isEmptyQ(Queue Q);
void printQueue(Queue Q);
 
int main() {
	Queue Q;
 
	int i;
	initQueue(&Q);

	//QUEUE
 
	enqueue(&Q, 1);
	printQueue(Q);
 
 
	for(i = 2; i < 5; i++) {
		enqueue(&Q, i);
	}
 
	printQueue(Q);
 
	dequeue(&Q);
	printQueue(Q);
 
	for(i = 2; i < 5; i++) {
		dequeue(&Q);
	}
 
	printQueue(Q);
 
	return 0;
}

void initQueue(Queue *Q) {
	Q->front = 0;
	Q->back = -1;
}
 
void enqueue(Queue *Q, int data) {
	if(!isFullQ(*Q)) {
		Q->back = (Q->back + 1) % QUEUEMAX;
		Q->elem[Q->back] = data;
	}
}
 
int dequeue(Queue *Q) {
	int def = -1;
 
	if(!isEmptyQ(*Q)) {
		def = Q->elem[Q->front];
		Q->front = (Q->front + 1) % QUEUEMAX;
	}
 
	return def;
}
 
int front(Queue Q) {
	return (!isEmptyQ(Q)) ? Q.elem[Q.front] : -1;
}
 
int isFullQ(Queue Q) {
	return (Q.front == (Q.back + 2) % QUEUEMAX) ? 1 : 0;
}
 
int isEmptyQ(Queue Q) {
	return (Q.front == (Q.back + 1) % QUEUEMAX) ? 1 : 0;
}
 
void printQueue(Queue Q) {
	if(isEmptyQ(Q)) {
		printf("EMPTY");
	}
 
	while(!isEmptyQ(Q)) {
		printf("%d ", dequeue(&Q));
	}
 
	printf("\n");
}