#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
	int children[MAX];
	int lastNdx;
} Tree;

void initTree(Tree *T);
void populateTree(Tree *T, int arr[], int size);
void insertTree(Tree *T, int data); // utilizes Balanced Tree insertion but not unique
void preOrder(Tree T, int index);
void inOrder(Tree T, int index);
void postOrder(Tree T, int index);

void visualize(Tree T);
int pow(int base, int exponent);

int main()
{
	Tree T;
	int arr[] = {4, 2, 5, 2, 1};
	int size = sizeof(arr) / sizeof(arr[0]);

	initTree(&T);
	populateTree(&T, arr, size);

	printf("Pre-order: ");
	preOrder(T, 0);

	printf("\nIn-order: ");
	inOrder(T, 0);

	printf("\nPost-order: ");
	postOrder(T, 0);

	printf("\n\nVisualization:");
	visualize(T);
	return 0;
}

void initTree(Tree *T) {
	T->lastNdx = -1;
}

void populateTree(Tree *T, int arr[], int size) {
	for (int i = 0; i < size; i++) {
		insertTree(T, arr[i]);
	}
}

void insertTree(Tree *T, int data) {
	if(T->lastNdx + 1 < MAX) {
		T->children[++T->lastNdx] = data;
	}
}

void preOrder(Tree T, int index) {
	if(index <= T.lastNdx) {
		printf("%d ", T.children[index]);
		preOrder(T, index * 2 + 1);
		preOrder(T, index * 2 + 2);
	}
}

void inOrder(Tree T, int index) {
	if(index <= T.lastNdx) {
		inOrder(T, index * 2 + 1);
		printf("%d ", T.children[index]);
		inOrder(T, index * 2 + 2);
	}
}

void postOrder(Tree T, int index) {
	if(index <= T.lastNdx) {
		postOrder(T, index * 2 + 1);
		postOrder(T, index * 2 + 2);
		printf("%d ", T.children[index]);
	}
}

void visualize(Tree T) {
	int level = 0;

	int trav = 0;

	while (trav <= T.lastNdx) {
		printf("\nLevel %d: ", level);

		int stopper = trav + pow(2, level++);

		while(trav <= T.lastNdx && trav < stopper) {
			printf("%d ", T.children[trav++]);
		}
	}
}

int pow(int base, int exponent) { // made a pow function because math.h doesnt work on ubuntu for some reason ahaha
	int ans = 1;

	for (int i = 0; i < exponent; i++) {
		ans *= base;
	}

	return ans;
}