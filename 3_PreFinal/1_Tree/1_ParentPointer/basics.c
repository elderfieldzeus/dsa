#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} *Tree;

typedef struct {
	Tree nodes[MAX];
	int front;
	int rear;
} Queue;

void initTree(Tree *T);
void populateTree(Tree *T, int arr[], int size);
void insertTree(Tree *T, int data); // utilizes BST insertion but not unique
void preOrder(Tree T);
void inOrder(Tree T);
void postOrder(Tree T);

// for visualizing using BFS
void initQueue(Queue *Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q);
void enqueue(Queue *Q, Tree D); // returns tree
Tree dequeue(Queue *Q);
void visualize(Tree T);

int main()
{
	Tree T;
	int arr[] = {4, 2, 5, 2, 1};
	int size = sizeof(arr) / sizeof(arr[0]);

	initTree(&T);
	populateTree(&T, arr, size);

	printf("Pre-order: ");
	preOrder(T);

	printf("\nIn-order: ");
	inOrder(T);

	printf("\nPost-order: ");
	postOrder(T);

	printf("\n\nVisualization:");
	visualize(T);
	return 0;
}

void initTree(Tree *T) {
	*T = NULL;
}

void populateTree(Tree *T, int arr[], int size) {
	for (int i = 0; i < size; i++) {
		insertTree(T, arr[i]);
	}
}

void insertTree(Tree *T, int data) {
	Tree temp = (Tree)malloc(sizeof(struct node));
	if(temp != NULL) {
		temp->data = data;
		temp->left = NULL;
		temp->right = NULL;

		Tree *trav;

		for (trav = T; *trav != NULL; 
				trav = (*trav)->data > data ? &(*trav)->left : &(*trav)->right){}

		*trav = temp; // connect
	}
}

void preOrder(Tree T) {
	if(T != NULL) {
		printf("%d ", T->data);
		preOrder(T->left);
		preOrder(T->right);
	}
}

void inOrder(Tree T) {
	if (T != NULL) {
		inOrder(T->left);
		printf("%d ", T->data);
		inOrder(T->right);
	}
}

void postOrder(Tree T) {
	if(T != NULL) {
		postOrder(T->left);
		postOrder(T->right);
		printf("%d ", T->data);
	}
}

// functions for visualization
void initQueue(Queue *Q) {
	Q->front = 1;
	Q->rear = 0;
}

bool isEmpty(Queue Q) {
	return (Q.rear + 1) % MAX == Q.front ? true : false;
}

bool isFull(Queue Q) {
	return (Q.rear + 2) % MAX == Q.front ? true : false;
}

void enqueue(Queue *Q, Tree D) {
	if(!isFull(*Q)) {
		Q->rear = (Q->rear + 1) % MAX;
		Q->nodes[Q->rear] = D;
	}
}
Tree dequeue(Queue *Q) {
	Tree temp = NULL;

	if (!isEmpty(*Q)){
		temp = Q->nodes[Q->front];
		Q->front = (Q->front + 1) % MAX;
	}

	return temp;
}

void visualize(Tree T) {
	int level = 0;
	Queue Q;
	initQueue(&Q);
	enqueue(&Q, T);

	// breadth first search
	while(!isEmpty(Q)) {
		printf("\nLevel %d: ", level++);

		int stopper = (Q.rear + 1) % MAX;

		while(Q.front != stopper) {
			Tree temp = dequeue(&Q);
			printf("%d ", temp->data);

			if(temp->left != NULL) {
				enqueue(&Q, temp->left);
			}
			
			if(temp->right != NULL) {
				enqueue(&Q, temp->right);
			}
		}
	}
}