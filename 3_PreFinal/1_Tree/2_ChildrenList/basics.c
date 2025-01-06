/*
    NOTICE: THIS IMPLEMENTATION IS BASED SOLELY ON MY IDEA OF CHILDREN LIST TREES. USE WISELY.
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node {
    int child;
    struct node *next;
} *Node;

typedef Node Tree[MAX];

void initTree(Tree T);
void insertTree(Node *N, int label);
void dfs(Tree T, int root);

int main() {
    Tree T;

    initTree(T);
    
    // set root to 0 and insert it into tree
    int root = 0;
    
    // make 1 a child of 0
    insertTree(T + root, 1);

    // make 2 a child of 1
    insertTree(T + 1, 2);

    // make 3 a child of 0
    insertTree(T + root, 3);

    // make 5 a child of 2
    insertTree(T + 2, 5);

    // depth first search
    dfs(T, root);
    return 0;
}

void initTree(Tree T) {
    for(int i = 0; i < MAX; i++) {
        T[i] = NULL;
    }
}

void insertTree(Node *N, int label) {
    Node temp = (Node)malloc(sizeof(struct node));
    
    if(temp != NULL && label >= 0 && label < MAX) {
        temp->child = label;
        temp->next = *N;
        *N = temp;
    }
}

void dfs(Tree T, int root) {
    printf("%d ", root);
    if(T[root] != NULL) {
        for(Node curr = T[root]; curr != NULL; curr = curr->next) {
            dfs(T, curr->child);
        }
    }
}