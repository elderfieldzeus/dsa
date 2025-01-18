#include <stdio.h>
#include <stdlib.h>
#include "./headers/linkedlist.h"

int main() {
    Stack S;
    init(&S);

    insertSorted(&S, 2);
    insertSorted(&S, 5);
    insertSorted(&S, 3);
    insertSorted(&S, 4);
    insertSorted(&S, 1);

    read(S);
    read(S);

    return 0;
}