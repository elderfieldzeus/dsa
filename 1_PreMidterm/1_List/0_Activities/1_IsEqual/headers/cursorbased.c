#include "cursorbased.h"

boolean isEqualNotSorted(VHeap V, List A, List B) {
    List *trav;

    for(trav = &A; *trav != -1 && B != -1; B = V.Nodes[B].next) {
        for(; *trav != -1 && V.Nodes[B].data != V.Nodes[*trav].data; trav = &V.Nodes[*trav].next) {}

        if(*trav != -1) {
            deleteFirst(&V, trav);
            trav = &A;
        }
    }

    return (*trav == -1 && B == -1) ? TRUE : FALSE;
}

boolean isEqualSorted(VHeap V, List A, List B) {
    for(;
        A != -1 && B != -1 && V.Nodes[A].data == V.Nodes[B].data;
        A = V.Nodes[A].next, B = V.Nodes[B].next) {}

    return (A == -1 && B == -1) ? TRUE : FALSE;
}

void initVH(VHeap *V) {
    for(int i = 1; i < MAX; i++) {
        V->Nodes[i - 1].next = i;
    }

    V->Nodes[MAX - 1].next = -1;

    V->Avail = 0;
}

List mallocVH(VHeap *V) {
    List temp = V->Avail;

    if(temp != -1) {
        V->Avail = V->Nodes[temp].next;
    }

    return temp;
}

void freeVH(VHeap *V, int index) {
    if(index >= 0 && index < MAX) {
        V->Nodes[index].next = V->Avail;
        V->Avail = index;
    }
}

void initList(List *L) {
    *L = -1;
}

void insertFirst(VHeap *V, List *L, int data) {
    List temp = mallocVH(V);

    if(temp != -1) {
        V->Nodes[temp].data = data;
        V->Nodes[temp].next = *L;
        *L = temp;
    }
}

void deleteFirst(VHeap *V, List *L) {
    if(*L != -1) {
        List temp = *L;
        *L = V->Nodes[temp].next;
        freeVH(V, temp);
    }
}

void populate(VHeap *V, List *L, int arr[], int size) {
    for(int i = 0; i < size; i++) {
        insertFirst(V, L, arr[i]);
    }
}

void sort(VHeap *V, List L) {
    for(List trav = L; trav != -1; trav = V->Nodes[trav].next) {
        List smallest = trav;

        for(List trav2 = V->Nodes[trav].next; trav2 != -1; trav2 = V->Nodes[trav2].next) {
            if(V->Nodes[trav2].data < V->Nodes[smallest].data) {
                smallest = trav2;
            }
        }

        if(smallest != trav) {
            int temp = V->Nodes[trav].data;
            V->Nodes[trav].data = V->Nodes[smallest].data;
            V->Nodes[smallest].data = temp;
        }
    }
}

void printList(VHeap V, List L) {
    if(L == -1) {
        printf("EMPTY");
    }

    for(List curr = L; curr != -1; curr = V.Nodes[curr].next) {
        printf("%d ", V.Nodes[curr].data);
    }

    printf("\n");
}
void freeAll(VHeap *V, List *L) {
    List temp;

    while(*L != -1) {
        temp = *L;
        *L = V->Nodes[temp].next;
        freeVH(V, temp);
    }
}