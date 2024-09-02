#include "./headers/stackArr.h"

int main() {
    printf("\033[H\033[J");

    Stack S = initStack();

    getInput(&S);

    printf("Given IS%sa palindrome.", isPalindrome(S) ? " " : " NOT ");

    return 0;
}