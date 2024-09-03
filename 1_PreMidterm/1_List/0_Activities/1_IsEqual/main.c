#include "./headers/linkedlist.h"

int main() {
    printf("\033[H\033[J");

    int arr1[] = {5, 4, 6, 7, 8};
    int arr2[] = {4, 5, 6 ,7, 8};

    List A, B;

    initList(&A);
    initList(&B);

    //if you want to test for EMPTY list just comment out the populate() functions
    populate(&A, arr1, sizeof(arr1) / sizeof(arr1[0]));
    populate(&B, arr2, sizeof(arr2) / sizeof(arr2[0]));

    printf("Before Sorting:\n");
    printList(A);
    printList(B);

    printf("NOT SORTED: %s\n\n", (isEqualNotSorted(A, B) == TRUE) ? "EQUAL" : "NOT EQUAL");

    sort(A);
    sort(B);

    printf("After Sorting:\n");
    printList(A);
    printList(B);

    printf("SORTED: %s", (isEqualSorted(A, B) == TRUE) ? "EQUAL" : "NOT EQUAL");

    freeAll(&A);
    freeAll(&B);

    return 0;
}