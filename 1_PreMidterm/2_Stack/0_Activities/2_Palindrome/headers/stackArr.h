#ifndef STACKARR_H
#define STACKARR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    char elem[MAX];
    int top;
} Stack;

bool isPalindrome(Stack S);

Stack initStack();
void getInput(Stack *S);


void push(Stack *S, char elem);
void pop(Stack *S);
char peek(Stack S);
bool isFull(Stack S);
bool isEmpty(Stack S);
void printStack(Stack *S);

#endif