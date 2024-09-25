/*
    I PREFER THIS CODE
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 0X5

typedef int Dictionary[MAX];

typedef enum {
    EMPTY = -1,
    DELETED = -2
} Status;

void initDict(Dictionary D);
int hash(int data);
void insert(Dictionary D, int data);
void delete(Dictionary D, int data);
bool isMember(Dictionary D, int data);
void printDict(Dictionary D);

int main() {
    printf("\033[H\033[J"); // clear screen

    Dictionary D;
    initDict(D);

    for(int i = 0; i < MAX; i++) {
        int temp;
        printf("Enter element %d: ", i + 1);
        scanf("%d", &temp);

        insert(D, temp);

        printf("Enter element to delete: ");
        scanf("%d", &temp);

        delete(D, temp);
    }

    int find;
    printf("Enter element to be searched: ");
    scanf("%d", &find);

    printf("\nElement %s in the Dictionary.\n\n", (isMember(D, find)) ? "IS" : "IS NOT");

    printDict(D);

    return 0;
}


void initDict(Dictionary D) {
    for(int i = 0; i < MAX; i++) {
        D[i] = EMPTY;
    }
}

int hash(int data) {
    return data % MAX;
}

void insert(Dictionary D, int data) {
    int temp = hash(data);
    int firstAvail = -1;
    int stop = (temp + MAX - 1) % MAX;

    int i;
    for(i = temp; i != stop && D[i] != EMPTY && D[i] != data; i = (i + 1) % MAX) {
        if(firstAvail == -1 && D[i] == DELETED) {
            firstAvail = i;
        }
    }

    if(D[i] != data && D[i] == EMPTY) {
        D[(firstAvail == -1) ? i : firstAvail] = data;
    }
}

void delete(Dictionary D, int data) {
    int temp = hash(data);

    int stop = (temp + MAX - 1) % MAX;
    int i;

    for(i = temp; i != stop && i != EMPTY && D[i]!= data; i = (i + 1) % MAX) {}

    if(D[i] == data) {
        D[i] = DELETED;
    }
}

bool isMember(Dictionary D, int data) {
    int temp = hash(data);

    int stop = (temp + MAX - 1) % MAX;
    int i;

    for(i = temp; i != stop && i != EMPTY && D[i]!= data; i = (i + 1) % MAX) {}    

    return (D[i] == data) ? true : false;
}

void printDict(Dictionary D) {
    for(int i = 0; i < MAX; i++) {
        printf("Index %d: ", i);
        if(D[i] == EMPTY) {
            printf("EMPTY");
        }
        else if(D[i] == DELETED) {
            printf("DELETED");
        }
        else {
            printf("%d", D[i]);
        }

        printf("\n");
    }
}