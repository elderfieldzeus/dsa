#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef int Set;

typedef struct {
    int data;
    int next;
} Nodetype;

typedef struct {
    Nodetype nodes[MAX];
    int avail;
} VHeap;

void initVH(VHeap *V);
int mallocVH(VHeap *V);
void freeVH(VHeap *V, int index);

void populateSet(Set *S, VHeap *V);
void insert(Set *S, int data, VHeap *V);
void printSet(Set S, VHeap V);
Set Union(Set A, Set B, VHeap *V);
Set Intersection(Set A, Set B, VHeap *V);
Set Difference(Set A, Set B, VHeap *V);

int main() {
    // printf("\033[H\033[J");
    VHeap V;
    initVH(&V);

    Set A = -1;
    Set B = -1;

    populateSet(&A, &V);
    populateSet(&B, &V);

    printf("Set A: ");
    printSet(A, V);

    printf("Set B: ");
    printSet(B, V);

    Set U = Union(A, B, &V);
    printf("\nUnion: ");
    printSet(U, V);

    Set I = Intersection(A, B, &V);
    printf("Intersection: ");
    printSet(I, V);

    Set D = Difference(A, B, &V);
    printf("(A - B): ");
    printSet(D, V);

    D = Difference(B, A, &V);
    printf("(B - A): ");
    printSet(D, V);

    return 0;
}

void initVH(VHeap *V) {
    for(int i = 1; i < MAX; i++) {
        V->nodes[i - 1].next = i;
    }

    V->nodes[MAX - 1].next = -1;
    V->avail = 0;
}

int mallocVH(VHeap *V) {
    int temp = V->avail;

    if(temp != -1) {
        V->avail = V->nodes[temp].next;
    }
    else {
        printf("VHEAP IS FULL");
    }

    return temp;
}

void freeVH(VHeap *V, int index) {
    if(index >= 0 && index < MAX) {
        V->nodes[index].next = V->avail;
        V->avail = index;
    }
}

void populateSet(Set *S, VHeap *V) {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++){
        int data;
        printf("Element %d: ", i);
        scanf("%d", &data);
        insert(S, data, V);
    }

    printf("\n");
}

void insert(Set *S, int data, VHeap *V) {
    Set *trav;

    for(trav = S; *trav != -1 && V->nodes[*trav].data != data; trav = &V->nodes[*trav].next) {}

    if(*trav == -1) {
        Set temp = mallocVH(V);
        
        if(temp != -1) {
            V->nodes[temp].data = data;
            V->nodes[temp].next = -1;
            *trav = temp;
        }
    }
}

void printSet(Set S, VHeap V) {
    for(Set curr = S; curr != -1; curr = V.nodes[curr].next) {
        printf("%d ", V.nodes[curr].data);
    }

    printf("\n");
}

Set Union(Set A, Set B, VHeap *V) {
    Set U = -1;
    Set *trav = &U;

    for(Set curr = A; curr != -1; curr = V->nodes[curr].next) {
        Set temp = mallocVH(V);

        if(temp != -1) {
            V->nodes[temp].data = V->nodes[curr].data;
            *trav = temp;
            trav = &V->nodes[temp].next;
        }
    }

    *trav = -1;

    for(Set curr = B; curr != -1; curr = V->nodes[curr].next) {
        insert(&U, V->nodes[curr].data, V);
    }

    return U;
}

Set Intersection(Set A, Set B, VHeap *V) {
    Set I = -1;

    for(Set currA = A; currA != -1; currA = V->nodes[currA].next) {
        Set currB;
        for(currB = B; currB != -1 && V->nodes[currA].data != V->nodes[currB].data; currB = V->nodes[currB].next) {}

        if(currB != -1) {
            Set temp = mallocVH(V);

            if(temp != -1) {
                V->nodes[temp].data = V->nodes[currA].data;
                V->nodes[temp].next = I;
                I = temp;
            }
        }
    }
    
    return I;
}

Set Difference(Set A, Set B, VHeap *V) {
    Set D = -1;

    for(Set currA = A; currA != -1; currA = V->nodes[currA].next) {
        Set currB;
        for(currB = B; currB != -1 && V->nodes[currA].data != V->nodes[currB].data; currB = V->nodes[currB].next) {}

        if(currB == -1) {
            Set temp = mallocVH(V);

            if(temp != -1) {
                V->nodes[temp].data = V->nodes[currA].data;
                V->nodes[temp].next = D;
                D = temp;
            }
        }
    }
    
    return D;
}