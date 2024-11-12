#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int data[MAX];
    int lastNdx;
} HeapList;

void listToHeap(HeapList *H);

int main() {
    return 0;
}

void listToHeap(HeapList *H) {
    int i = (H->lastNdx - 1) / 2;

    for(; i >= 0; i--) {
        int parent = i;
        int largest = parent;

        while(largest == parent) {
            int Lchild = parent * 2 + 1;
            int Rchild = Lchild + 1;

            if(Lchild <= H->lastNdx && H->data[largest] < H->data[Lchild]) {
                largest = Lchild;
            }

            if(Rchild <= H->lastNdx && H->data[largest] < H->data[Rchild]) {
                largest = Rchild;
            }

            if(largest != parent) {
                int temp = H->data[parent];
                H->data[parent] = H->data[largest];
                H->data[largest] = temp;
                parent = largest;
            }
            else {
                largest = -1; // flag
            }
        }
    }
}