#include "./headers/cursorbased.h"

int main() {
    printf("\033[H\033[J");

    int arr1[] = {5, 4, 6, 7, 8};
    int arr2[] = {4, 5, 6 ,7, 8};

    VHeap V;
    List A, B;

    initVH(&V);

    initList(&A);
    initList(&B);

    //if you want to test for EMPTY list just comment out the populate() functions
    populate(&V, &A, arr1, sizeof(arr1) / sizeof(arr1[0]));
    populate(&V, &B, arr2, sizeof(arr2) / sizeof(arr2[0]));

    printf("Before Sorting:\n");
    printList(V, A);
    printList(V, B);

    printf("NOT SORTED: %s\n\n", (isEqualNotSorted(V, A, B) == TRUE) ? "EQUAL" : "NOT EQUAL");
    sort(&V, A);
    sort(&V, B);

    printf("After Sorting:\n");
    printList(V, A);
    printList(V, B);

    printf("SORTED: %s", (isEqualSorted(V, A, B) == TRUE) ? "EQUAL" : "NOT EQUAL");

    freeAll(&V, &A);
    freeAll(&V, &B);

    return 0;
}