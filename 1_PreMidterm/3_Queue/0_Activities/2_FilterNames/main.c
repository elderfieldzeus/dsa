#include "./headers/exercise.h"

int main() {
    printf("\033[H\033[J");

    NQueue Q;

    initNQueue(&Q);

    for(int i = 0; i < MAX; i++) {
        Name temp;
        printf("Enter first name: ");
        scanf(" %[^\n]", temp.fname);

        printf("Enter last name: ");
        scanf(" %[^\n]", temp.lname);
        printf("\n");

        if(!insertSorted(&Q, temp)) {
            printf("Queue is FULL!\n\n");
        }
    }

    printf("QUEUE:\n");
    displayQueue(Q);

    char remove[100];
    printf("\nEnter last name to filter from queue: ");
    scanf(" %[^\n]", remove);

    Name *f = filterNames(&Q, remove);

    printf("\nQUEUE:\n");
    displayQueue(Q);

    printf("\nFILTERED NAMES:\n");
    for(int i = 0; strcmp(f[i].lname, "END") != 0; i++) {
        printf("%s %s\n", f[i].fname, f[i].lname);
    }

    return 0;
}