#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int set[MAX];
    int size;
} Set;

void insertToSet(Set *S, int data);
void deleteFromSet(Set *S, int data);
void populateSet(Set *S);
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

    int temp;
    printf("\nRemove an element from set A: ");
    scanf(" %d", &temp);

    deleteFromSet(&A, temp);
    printf("A without '%d': ", temp);
    printSet(A);

    return 0;
}

void insertToSet(Set *S, int data) {
    if(S->size < MAX) {
        int i;

        for(i = 0; i < S->size && S->set[i] != data; i++) {}

        if(i == S->size) {
            S->set[S->size++] = data;
        }
    }
}

void deleteFromSet(Set *S, int data) {
    if(S->size > 0) {
        int i;

        for(i = 0; i < S->size && S->set[i] != data; i++) {}

        if(i < S->size) {
            S->size--;

            if(S->size > 0) {
                S->set[i] = S->set[S->size];
            }
        }
    }
}

void populateSet(Set *S) {
    printf("Enter number\n");

    for (; S->size < MAX / 2;){
        int data;
        printf("Element %d: ", S->size);
        scanf("%d", &data);

        insertToSet(S, data);
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
    Set S = A;

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