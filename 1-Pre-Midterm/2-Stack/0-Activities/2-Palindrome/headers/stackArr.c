#include "./stackArr.h"

bool isPalindrome(Stack S) {
    Stack temp = S;
    Stack reverse = initStack();

    while(!isEmpty(S)) {
        push(&reverse, peek(S));
        pop(&S);
    }

    for(; !isEmpty(temp) && (peek(temp) == peek(reverse)); pop(&temp), pop(&reverse)) {}

    return isEmpty(temp) ? true : false;
}

Stack initStack() {
    Stack s = {.top = -1};

    return s;
}

void getInput(Stack *S) {
    char temp[MAX + 1];
    
    printf("Enter word (MAX: %d letters): ", MAX);
    scanf("%s", temp);

    for(int i = 0; i < temp[i] != '\0'; i++) {
        push(S, temp[i]);
    }
}

void push(Stack *S, char elem) {
    if(!isFull(*S)) {
        S->elem[++S->top] = elem;
    }
}

void pop(Stack *S) {
    if(!isEmpty(*S)) {
        S->top--;
    }
}

char peek(Stack S) {
    return (isEmpty(S)) ? -1 : S.elem[S.top];
}

bool isFull(Stack S) {
    return S.top == (MAX - 1) ? true : false;
}

bool isEmpty(Stack S) { 
    return S.top == -1 ? true : false;
}

void printStack(Stack *S) {
    Stack temp = initStack();

    while(!isEmpty(*S)) {
        char data = peek(*S);

        printf("%c ", data);
        push(&temp, data);
        pop(S);
    }

    while(!isEmpty(temp)) {
        push(S, peek(temp));
        pop(&temp);
    }
}