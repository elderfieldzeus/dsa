#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int set[MAX];
    int size;
} Set;

void
populateSet(Set *S);
void printSet(Set S);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main() {
    printf("\033[H\033[J");

    Set A = {{}, 0};
    Set B = {{}, 0};

    populateSet(&A);
    populateSet(&B);

    printf("Set A: ");
    printSet(A);

    printf("Set B: ");
    printSet(B);

    Set U = Union(A, B);
    printf("\nUnion: ");
    printSet(U);

    Set I = Intersection(A, B);
    printf("Intersection: ");
    printSet(I);

    Set D = Difference(A, B);
    printf("(A - B): ");
    printSet(D);

    D = Difference(B, A);
    printf("(B - A): ");
    printSet(D);

    return 0;
}


void populateSet(Set *S) {
    printf("Enter number (0 - %d)\n", MAX - 1);

    for (; S->size < MAX / 2;){
        int data;
        printf("Element %d: ", S->size);
        scanf("%d", &data);
        
        if(data >= 0 && data < MAX) {
            int j;
            for (j = 0; j < S->size && S->set[j] != data; j++){}

            if(j == S->size) {
                S->set[S->size++] = data;
            }
        }
    }

    printf("\n");

    S->size = MAX / 2;
}

void printSet(Set S) {
    for(int i = 0; i < S.size; i++) {
        printf("%d ", S.set[i]);
    }

    printf("\n");
}

Set Union(Set A, Set B) {
    Set S = {{}, A.size};

    //copy A
    for (int i = 0; i < A.size; i++) {
        S.set[i] = A.set[i];
    }

    //add elements in B but not in A
    for (int i = 0; i < B.size; i++) {
        int j;
        for (j = 0; j < S.size && B.set[i] != S.set[j]; j++){}

        if(j == S.size) {
            S.set[S.size++] = B.set[i];
        }
    }

    return S;
}

Set Intersection(Set A, Set B) {
    Set S = {{}, 0};

    for (int i = 0; i < A.size; i++) {
        int j;
        for (j = 0; j < B.size && A.set[i] != B.set[j]; j++){}

        // if in both A and B, add to S
        if(j != B.size) {
            S.set[S.size++] = A.set[i];
        }
    }

    return S;
}

Set Difference(Set A, Set B) {
    Set S = {{}, 0};

    for (int i = 0; i < A.size; i++) {
        int j;

        for (j = 0; j < B.size && A.set[i] != B.set[j]; j++) {}

        if(j == B.size) {
            S.set[S.size++] = A.set[i];
        }
    }

    return S;
}