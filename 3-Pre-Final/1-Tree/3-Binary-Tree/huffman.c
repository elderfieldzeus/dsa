#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5
#define PARENT '*'

typedef struct {
    char character;
    float weight;
} Element;

typedef struct node {
    Element data;
    struct node *left;
    struct node *right;
} *Tree;

typedef struct tree {
    Tree tree;
    struct tree *next;
} *Forest;

void getInput(Element elements[], float *total) {
    *total = 0;

    for(int i = 0; i < MAX; i++) {
        // I am too lazy to put input checker so pls input distinct elements haha
        printf("Enter disctinct character: ");
        scanf(" %c", &elements[i].character);

        printf("Enter weight: ");
        scanf("%f", &elements[i].weight);

        *total += elements[i].weight;
    }
}

void adjustWeight(Element elements[], float total) {
    for(int i = 0; i < MAX; i++) {
        elements[i].weight /= total; // transforms number into decimal form out of 1.00
    }
}

void initTree(Tree *T) {
    *T = NULL;
}

Tree createNode(char character, float weight, Tree left, Tree right) {
    Tree node = (Tree) malloc(sizeof(struct node));

    if(node != NULL) {
        node->data.character = character;
        node->data.weight = weight;
        node->left = left;
        node->right = right;
    }

    return node;
}

void insertForest(Forest *F, Tree T) {
    Forest temp = (Forest)malloc(sizeof(struct tree));

    if(temp != NULL) {
        temp->tree = T;
        temp->next = *F;
        *F = temp;
    }
}

void deleteForest(Forest *F) {
    Forest temp = *F;
    *F = temp->next;
    free(temp);
}

void populateTree(Tree *T, Element elements[]) {
    Forest F = NULL;

    // Populate Forest LinkedList (Similar to Queue implementation)
    for(int i = 0; i < MAX; i++) {
        Tree temp = createNode(elements[i].character, elements[i].weight, NULL, NULL);
        insertForest(&F, temp);
    }

    // while forest is not NULL and forest does not only have one node
    while(F != NULL && F->next != NULL) {
        Forest *trav = &F;
        Forest *smallestOne = NULL, *smallestTwo = NULL;

        while(*trav != NULL) {
            if(smallestOne == NULL) {
                smallestOne = trav;
            }
            else if(smallestTwo == NULL) {
                smallestTwo = trav;
            }
            else {
                // swap so that smallestOne and smallestTwo become the two trees with the smallest weight
                Forest *small = trav;

                if((*small)->tree->data.weight < (*smallestOne)->tree->data.weight) {
                    Forest* t = smallestOne;
                    smallestOne = small;
                    small = t;
                }

                if((*small)->tree->data.weight < (*smallestTwo)->tree->data.weight) {
                    Forest* t = smallestTwo;
                    smallestTwo = small;
                    small = t;
                }
            }

            trav = &(*trav)->next;
        }

        float newWeight = (*smallestOne)->tree->data.weight + (*smallestTwo)->tree->data.weight;
        Tree temp = createNode(PARENT, newWeight, (*smallestOne)->tree, (*smallestTwo)->tree);
        

        // delete smallestOne and smallestTwo from the linked list
        if((*smallestOne)->next == *smallestTwo) {
            deleteForest(smallestOne);
            deleteForest(smallestOne);
        }
        else if((*smallestTwo)->next == *smallestOne) {
            deleteForest(smallestTwo);
            deleteForest(smallestTwo);
        }
        else {
            deleteForest(smallestOne);
            deleteForest(smallestTwo);
        }

        // insert into forest
        insertForest(&F, temp);
    }

    if(F != NULL) {
        *T = F->tree;
    }
}

void preOrder(Tree T) {
    if(T != NULL) {
        printf("%c ", T->data.character);
        preOrder(T->left);
        preOrder(T->right);
    }
    else {
        printf("_ ");
    }
}

void dfs(Tree T, char str[]) {
    if(T != NULL && T->data.character != '*') {
        printf("%c: %s\n", T->data.character, str);
    }
    else if(T != NULL) {
        char left[MAX + 1] = "", right[MAX + 1] = "";

        strcpy(left, str);
        strcpy(right, str);

        strcat(left, "0");
        strcat(right, "1");

        dfs(T->left, left);
        dfs(T->right, right);
    }
}

int main() {
    Tree T;

    Element elements[MAX];
    float total = 0;

    initTree(&T);

    getInput(elements, &total);
    adjustWeight(elements, total);

    printf("\nRespective Weights out of 1.0:\n");
    for(int i = 0; i < MAX; i++) {
        printf("%c: %f\n", elements[i].character, elements[i].weight);
    }

    populateTree(&T, elements);

    printf("\nPre order: ");
    preOrder(T);
    printf("\n");

    printf("\nCode for different characters:\n");
    dfs(T, "");

    return 0;
}