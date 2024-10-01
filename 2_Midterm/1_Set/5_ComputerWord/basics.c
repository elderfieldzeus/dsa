#include <stdio.h>
#include <stdlib.h>
#define MAX (sizeof(unsigned int) * 8)

// LEFT TO RIGHT IMPLEMENTATION FOR SET
typedef unsigned int Set; // 32 bits

void init(Set *S);
void displayBitPattern(Set S);

void insertElem(Set *S, int elem);
void deleteElem(Set *S, int elem);
void displayElem(Set S);

int main()
{
    printf("\033[H\033[J");

    Set S;

    init(&S);
    insertElem(&S, 1);
    insertElem(&S, 2);
    insertElem(&S, 31);

    insertElem(&S, 24);
    // deleteElem(&S, 24);

    displayElem(S);
    displayBitPattern(S);
}

void init(Set *S)
{
    *S = 0;
}

void displayBitPattern(Set S)
{

    for (int shift = MAX - 1; shift >= 0; shift--)
    {
        if ((shift + 1) % 4 == 0)
        {
            printf(" ");
        }
        printf("%d", S >> shift & 1);
    }

    printf("\n");
}

void insertElem(Set *S, int elem)
{
    if (elem < MAX)
    {
        *S |= (1 << elem);
    }
}

void deleteElem(Set *S, int elem)
{
    if (elem < MAX)
    {
        *S &= ~(1 << elem);
    }
}

void displayElem(Set S)
{
    printf("[ ");

    for (int i = 0; i < MAX; i++)
    {
        if (((S >> i) & 1) == 1)
        {
            printf("%d ", i);
        }
    }

    printf("]\n");
}