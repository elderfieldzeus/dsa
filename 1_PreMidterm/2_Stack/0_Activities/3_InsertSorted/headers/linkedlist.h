#ifndef LL_STACK
#define LL_STACK

typedef struct node {
    int data;
    struct node *next;
} *Stack;

void init(Stack *S);
void push(Stack *S, int data);
void pop(Stack *S);
int peek(Stack S);
Stack popNoFree(Stack *S);
void pushNoFree(Stack *S, Stack temp);
void insertSorted(Stack *S, int data);
void read(Stack S);

#endif