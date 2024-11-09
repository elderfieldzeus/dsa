#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} *Tree;

void initTree(Tree *T);
void populateTree(Tree *T, int arr[], int size);
void insertTree(Tree *T, int data);
bool isFound(Tree T, int x);
bool isFoundRecursion(Tree T, int x);
void deleteWithOneChild(Tree *T);
void deleteElem(Tree *T, int x);
void preOrder(Tree T);

int main() {
    Tree T;
	int arr[] = {4, 2, 5, 2, 1};
	int size = sizeof(arr) / sizeof(arr[0]);

    initTree(&T);
	populateTree(&T, arr, size);

    int x = 4;
    printf("LOOP: %d %s in the tree\n", x, isFound(T, x) ? "IS" : "IS NOT");

    x = 2;
    printf("RECURSION: %d %s in the tree\n", x, isFound(T, x) ? "IS" : "IS NOT");

    x = 2;
    printf("\nBefore deleting %d: (Pre-order traversal)\n", x);
    preOrder(T);

    deleteElem(&T, x);

    printf("\nAfter deleting %d: (Pre-order traversal)\n", x);
    preOrder(T);

    return 0;
}

void initTree(Tree *T) {
	*T = NULL;
}

void populateTree(Tree *T, int arr[], int size) {
	for (int i = 0; i < size; i++) {
		insertTree(T, arr[i]);
	}
}

void insertTree(Tree *T, int data) {
	Tree temp = (Tree)malloc(sizeof(struct node));
	if(temp != NULL) {
		temp->data = data;
		temp->left = NULL;
		temp->right = NULL;

		Tree *trav;

		for (trav = T; *trav != NULL && (*trav)->data != data; 
				trav = (*trav)->data > data ? &(*trav)->left : &(*trav)->right){}

        if(*trav == NULL) {
            *trav = temp; // connect if element not found
        }
	}
}

bool isFound(Tree T, int x) {
    while(T != NULL && T->data != x) {
        if(T->data < x) {
            T = T->right;
        }
        else {
            T = T->left;
        }
    }

    return T == NULL ? false : true;
}

bool isFoundRecursion(Tree T, int x) {
    if(T == NULL) return false;
    if(T->data == x) return true;

    return (T->data < x) ? isFoundRecursion(T->right, x) : isFoundRecursion(T->left, x);
}  

void deleteWithOneChild(Tree *T) {
    Tree temp = *T;
    *T = (*T)->left != NULL ? (*T)->left : (*T)->right;
    free(temp);
}

void deleteElem(Tree *T, int x) {
    Tree* trav = T;

    while(*trav != NULL && (*trav)->data != x) {
        if((*trav)->data < x) {
            trav = &(*trav)->right;
        }
        else {
            trav = &(*trav)->left;
        }
    }

    

    if(*trav != NULL) {
        // check if element has two children
        if((*trav)->left != NULL && (*trav)->right != NULL) {
            // get another element nearest to the element to be deleted, so it can take its place
            Tree* nearest = &(*trav)->left;

            while((*nearest)->right != NULL) {
                nearest = &(*nearest)->right;
            }

            // closest element replaces the element to be deleted
            (*trav)->data = (*nearest)->data;

            // the closest element will be deleted using the one child deletion method
            // this is because we are sure that it no longer has a right child
            deleteWithOneChild(nearest);
        }
        // if element has at most one children, we can utilize the deleteWithOneChild() function
        else {
            deleteWithOneChild(trav);
        }
    }
}

// prints in a style similar to POT with _ as empty nodes
void preOrder(Tree T) { 
	if (T != NULL) {
        printf("%d ", T->data);
		preOrder(T->left);
		preOrder(T->right);
	}
    else {
        printf("_ ");
    }
}