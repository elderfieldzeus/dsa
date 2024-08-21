#include <stdio.h>
#define MAX 10
 
typedef struct {
	int elem[MAX];
	int top;
} Stack;
 
// STACK 
 
void initStack(Stack *S);
void push(Stack *S, int elem);
int pop(Stack *S);
int peek(Stack S);
int isFullS(Stack S);
int isEmptyS(Stack S); 
void printStack(Stack S);
 
int main() {
	Stack S;
 
	int i;
	initStack(&S);
 
	// STACK
 
	push(&S, 1);
	printStack(S);
 
	for(i = 2; i < 5; i++) {
		push(&S, i);
	}
 
	printStack(S);
 
	pop(&S);
	printStack(S);
 
	for(i = 2; i < 5; i++) {
		pop(&S);
	}
 
	printStack(S);
 
	return 0;
}

void initStack(Stack *S) {
	S->top = -1;
}
 
void push(Stack *S, int elem) {
	if(!isFullS(*S)) {
		S->elem[++S->top] = elem;
	}
}
 
int pop(Stack *S) {
	int def = -1;
 
	if(!isEmptyS(*S)) {
		def = S->elem[S->top--];
	}
 
	return def;
}
 
int peek(Stack S) {
	int def = -1;
 
	if(!isEmptyS(S)) {
		def = S.elem[S.top];
	}
 
	return def;
}
 
int isFullS(Stack S) {
	return (S.top == MAX - 1) ? 1 : 0;
}
 
int isEmptyS(Stack S) {
	return (S.top == -1) ? 1 : 0;
}
 
void printStack(Stack S) {
	if(isEmptyS(S)) {
		printf("EMPTY");
	}
 
	while(!isEmptyS(S)) {
		printf("%d ", pop(&S));
	}
 
	printf("\n");
}