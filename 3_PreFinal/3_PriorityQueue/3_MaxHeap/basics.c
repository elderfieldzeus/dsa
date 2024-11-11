#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

// prioritized by elements
typedef struct {
    int elements[MAX];
    int lastIndex;
} MaxHeap;

void initTree(MaxHeap *T);
void populateTree(MaxHeap *T, int arr[], int size);
void insertTree(MaxHeap *T, int data);
int deleteMax(MaxHeap *T);
void displayTree(MaxHeap T);

int main() {
    MaxHeap T;
	int arr[] = {4, 2, 5, 2, 1};
	int size = sizeof(arr) / sizeof(arr[0]);

    initTree(&T);
	populateTree(&T, arr, size);

    printf("Elements in order: ");
    displayTree(T);

    return 0;
}

void initTree(MaxHeap *T) {
    T->lastIndex = -1;
}

void populateTree(MaxHeap *T, int arr[], int size) {
    for(int i = 0; i < size; i++) {
        insertTree(T, arr[i]);
    }
}

void insertTree(MaxHeap *T, int data) {
    if(T->lastIndex + 1 < MAX) {
        int child = ++T->lastIndex;
        int parent = (child - 1) / 2;

        while(child > 0 && T->elements[parent] < data) {
            // shift
            T->elements[child] = T->elements[parent];

            child = parent;
            parent = (parent - 1) / 2;
        }

        T->elements[child] = data;
    }
}

int deleteMax(MaxHeap *T) {
    int temp = -1;
    if(T->lastIndex >= 0) {
        temp = T->elements[0];
        int data = T->elements[T->lastIndex--];

        int parent = 0;
        int LC = parent * 2 + 1;
        int RC = LC + 1;

        // 'child' variable stores the index of the child with the higher priority (in this case it is the bigger element)
        int child = T->elements[LC] > T->elements[RC] ? LC : RC;

        // while 'child' is still in range of elements and data is lesser than child, shift elements
        while(child <= T->lastIndex && T->elements[child] > data) {
            T->elements[parent] = T->elements[child];

            parent = child;
            LC = parent * 2 + 1;
            RC = LC + 1;
            child = T->elements[LC] < T->elements[RC] ? LC : RC;
        }

        T->elements[parent] = data; // data is stored in its proper position
    }

    return temp;
}

void displayTree(MaxHeap T) {
    int temp;
    while((temp = deleteMax(&T)) != -1) {
        printf("%d ", temp);
    }
}