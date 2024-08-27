#include "./headers/queueArr.h"
// #include "./headers/queueLL.h"

int main() {
    printf("\033[H\033[J");

    Queue Q;

    init(&Q);
    print(&Q);

    enqueue(&Q, 1);
    print(&Q);

    enqueue(&Q, 2);
    enqueue(&Q, 3);
    enqueue(&Q, 4);
    enqueue(&Q, 5);
    print(&Q);
    
    dequeue(&Q);
    print(&Q);

    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);
    print(&Q);

    return 0;
}