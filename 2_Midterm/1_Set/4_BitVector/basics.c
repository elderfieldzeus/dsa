#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef int Set[MAX]; // only ones and zeroes

void populateSet(Set S);
void printSet(Set S);
Set *Union(Set A, Set B);
Set *Intersection(Set A, Set B);
Set *Difference(Set A, Set B);

int main() {
    printf("\033[H\033[J");

    Set A = {};
    Set B = {};

    populateSet(A);
    populateSet(B);

    printf("Set A: ");
    printSet(A);

    printf("Set B: ");
    printSet(B);

    Set *U = Union(A, B);
    printf("\nUnion: ");
    printSet(*U);

    Set *I = Intersection(A, B);
    printf("Intersection: ");
    printSet(*I);

    Set *D = Difference(A, B);
    printf("(A - B): ");
    printSet(*D);

    D = Difference(B, A);
    printf("(B - A): ");
    printSet(*D);

    return 0;
}

void populateSet(Set S) {
    for (int i = 0; i < MAX; i++) {
        int data;
        printf("Element %d: ", i);
        scanf("%d", &data);

        if(data >= 0 && data < MAX) {
            S[data] = 1;
        }
    }
    printf("\n");
}

void printSet(Set S) {
    for (int i = 0; i < MAX; i++) {
        if(S[i] == 1) {
            printf("%d ", i);
        }
    }

    printf("\n");
}

Set *Union(Set A, Set B) {
    Set *S = (Set *)malloc(sizeof(Set));

    if(S != NULL) {
        for (int i = 0; i < MAX; i++) {
            (*S)[i] = A[i] | B[i];
        }
    }

    return S;
}

Set *Intersection(Set A, Set B) {
    Set *S = (Set *)malloc(sizeof(Set));

    if(S != NULL) {
        for (int i = 0; i < MAX; i++) {
            (*S)[i] = A[i] & B[i];
        }
    }

    return S;
}

Set *Difference(Set A, Set B) {
    Set *S = (Set *)malloc(sizeof(Set));

    if(S != NULL) {
        for (int i = 0; i < MAX; i++) {
            (*S)[i] = A[i] & (~B[i]);
        }
    }
}