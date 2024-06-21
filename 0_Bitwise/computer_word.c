#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char Set;

void displayBit(Set a);
void insert(int off, Set *a);
void removeB(int off, Set *a);
bool isBitIn(int index, Set a);

int main() {
    Set main = '\0';
    displayBit(main);

    insert(0, &main);
    displayBit(main);

    insert(3, &main);
    displayBit(main);

    removeB(0, &main);
    displayBit(main);

    printf("%s", (isBitIn(6, main) ? "true" : "false"));
    return 0;
}

void displayBit(Set a) {
    int offset = sizeof(a) * 8 - 1; // 7 bits

    while (offset >= 0) {
        if(offset == 3) printf(" ");

        printf("%d", a >> offset & 1);

        offset--;
    }
    printf("\n");

}

void insert (int off, Set *a) {
    *a |= 1 << off;
}

void removeB(int off, Set *a) {
    *a &= ~(1 << off);
}

bool isBitIn(int index, Set a) {
    return (a >> index & 1) ? true : false;
}
