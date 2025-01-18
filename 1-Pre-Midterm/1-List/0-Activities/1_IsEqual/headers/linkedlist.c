#include "linkedlist.h"

boolean isEqualNotSorted(List A, List B) {
    List copyA;
    List *trav;

    initList(&copyA);

    // Copy List A to copyA
    for(;A != NULL; A = A->next) {
        insertFirst(&copyA, A->data);    
    }

    // While checking element, delete from copyA if found.
    for(trav = &copyA; B != NULL && *trav != NULL; B = B->next) {
        for(; (*trav) != NULL && (*trav)->data != B->data; trav = &(*trav)->next) {}

        if(*trav != NULL) {
            deleteFirst(trav);
            trav = &copyA; // for when trav becomes NULL after deleting
        }
    }

    return (B == NULL && copyA == NULL) ? TRUE : FALSE;
}


boolean isEqualSorted(List A, List B) {
    for(; 
        A != NULL && B != NULL && A->data == B->data;
        A = A->next, B = B->next) {}

    return (A == NULL && B == NULL) ? TRUE : FALSE;
}

void initList(List *L) {
    *L = NULL;
}

void insertFirst(List *L, int data) {
    List temp = (List)malloc(sizeof(struct node));
    
    if(temp != NULL) {
        temp->data = data;
        temp->next = *L;
        *L = temp;
    }
}

void deleteFirst(List *L) {
    if(*L != NULL) {
        List temp = *L;
        *L = temp->next;
        free(temp);
    }
}

void populate(List *L, int arr[], int size) {
    for(int i = 0; i < size; i++) {
        insertFirst(L, arr[i]);
    }
}

void sort(List L) {
    for(List curr = L; curr != NULL; curr = curr->next) {
        List smallest = curr;

        for(List curr2 = curr->next; curr2 != NULL; curr2 = curr2->next) {
            if(curr2->data < smallest->data) {
                smallest = curr2;
            }
        }

        if(smallest != curr) {
            int temp = curr->data;
            curr->data = smallest->data;
            smallest->data = temp;
        }
    }
}

void printList(List L) {
    if(L == NULL) {
        printf("EMPTY");
    }

    for(List curr = L; curr != NULL; curr = curr->next) {
        printf("%d ", curr->data);
    }

    printf("\n");
}

void freeAll(List *L) {
    List del;

    while(*L != NULL) {
        del = *L;
        *L = (*L)->next;
        free(del);
    }
    
}