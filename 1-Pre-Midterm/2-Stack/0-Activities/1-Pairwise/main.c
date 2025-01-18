#include "./headers/stackArr.h"
// #include "./headers/stackLL.h"

int main() {
    printf("\033[H\033[J");

    Stack S;

    init(&S);
    print(&S);

    push(&S, 1);
    print(&S);

    push(&S, 2);
    push(&S, 3);
    push(&S, 4);
    push(&S, 5);
    print(&S);
    
    pop(&S);
    print(&S);

    pop(&S);
    pop(&S);
    pop(&S);
    pop(&S);
    print(&S);

    return 0;
}