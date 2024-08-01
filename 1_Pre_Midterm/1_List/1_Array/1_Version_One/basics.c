#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int data;
} Element;

typedef struct {
    Element Elements[MAX];
    int count;
} Version_One;

// Initialize, insert, delete, member, locate, and other operations
void init(Version_One *List);
void read(Version_One List);
void insert(Version_One *List, int data);
void delete(Version_One *List, int data);
bool member(Version_One List, int data);
int locate(Version_One List, int data);


int main() {
    Version_One List;
    
    printf("\033[H\033[J"); // clear screen
    
    init(&List);
    read(List);

    insert(&List, 1);
    read(List);

    delete(&List, 1);
    read(List);

    printf("%s\n", member(List, 1) ? "TRUE" : "FALSE");

    printf("%d\n", locate(List, 1));

    return 0;
}

void init(Version_One *List) {
    List->count = 0;
}

void read(Version_One List) {
    printf("List: ");
    for(int i = 0; i < List.count; i++) {
        printf("%d%s", List.Elements[i].data, (i !=  List.count - 1) ? ", " : ".\n");
    }
    if(List.count == 0) {
        printf("EMPTY\n");
    }
}

void insert(Version_One *List, int data) {
    if(List->count < MAX) {
        List->Elements[List->count++].data = data; 
    }
}

void delete(Version_One *List, int data) {
    int i = 0;
    for(; i < List->count && List->Elements[i].data != data; i++) {}

    if(i != List->count) {
        for(i++; i <= List->count; i++) {
            List->Elements[i - 1].data = List->Elements[i].data;
        }
        List->count--;
    }
}

bool member(Version_One List, int data) {
    int i;
    for(i = 0; i < List.count && List.Elements[i].data != data; i++) {}
    return (i == List.count) ? false : true;
}

int locate(Version_One List, int data) {
    int i;
    for(i = 0; i < List.count && List.Elements[i].data != data; i++) {}
    return (i == List.count) ? -1 : i;
}