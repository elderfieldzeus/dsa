/*
    TAKE NOTE: 
    In order to sort in ascending order, MaxHeap should be used.
    While descending order requires a MinHeap
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

// MAXHEAP IMPLEMENTATION
void maxHeapify(int arr[], int size, int index);
void heapSort(int arr[], int size);
void display(int arr[], int size);

int main() {
	int arr[] = {4, 2, 5, 2, 1};
	int size = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, size);
    display(arr, size);

    return 0;
}

// same logic algorithm when you deleteMin/Max()
void maxHeapify(int arr[], int size, int parent) {
    int largest = parent;
    int left = parent * 2 + 1;
    int right = left + 1;

    if(left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    if(right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    // if parent is not the largest element, then swap to follow POT
    if(largest != parent) {
        int temp = arr[largest];
        arr[largest] = arr[parent];
        arr[parent] = temp;

        // recursively heapify the new largest element
        maxHeapify(arr, size, largest);
    }
}

void heapSort(int arr[], int size) {
    // heapify from the parent of the last node up to the head
    for(int i = (size - 1) / 2; i >= 0; i--) {
        maxHeapify(arr, size, i);
    }

    int lastIndex = size - 1;

    // swap first element with last element
    while(lastIndex > -1) {
        int temp = arr[lastIndex];
        arr[lastIndex] = arr[0];
        arr[0] = temp;

        // heapify from root to maintain POT
        maxHeapify(arr, lastIndex--, 0);
    }
}

void display(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}