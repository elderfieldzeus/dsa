#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX 0XA

typedef enum
{
	EMPTY = -1,
	DELETED = -2
} DictStatus;

typedef int Dictionary[MAX];

void initDict(Dictionary D);
int hash(int data);
void insert(Dictionary D, int data);
void delete(Dictionary D, int data);
bool isMember(Dictionary D, int data);

int main()
{
	Dictionary D;
	initDict(D);

	char op;
	int temp;
	do
	{
		printf("\n+ = insert\n- = delete\n* = find\nP = print\nS = end\n\nEnter operation: ");
		scanf(" %c", &op);

		switch(toupper(op)) {
			case '+':
				printf("Insert data: ");
				scanf("%d", &temp);

				insert(D, temp);
				break;
			case '-':
				printf("Delete data: ");
				scanf("%d", &temp);

				delete(D, temp);
				break;
			case '*':
				printf("Enter number: ");
				scanf("%d", &temp);

				printf("%d %s in the Dictionary.\n", temp, (isMember(D, temp)) ? "IS" : "IS NOT");
				break;
			case 'P':
				for (int i = 0; i < MAX; i++) {
					printf("%d: %d\n", i, D[i]);
				}
		}
	} while (toupper(op) != 'S');

	return 0;
}

void initDict(Dictionary D)
{
	for (int i = 0; i < MAX; i++)
	{
		D[i] = EMPTY;
	}
}

int hash(int data)
{
	return data % MAX;
}

void insert(Dictionary D, int data)
{
	int hashValue = hash(data);
	int firstAvail = -1;
	int trav = hashValue;
	bool backToStart = false;

	while (!backToStart && D[trav] != data && D[trav] != EMPTY)
	{
		if (D[trav] == DELETED)
		{
			firstAvail = trav;
		}

		trav = (trav + 1) % MAX;

		if (trav == hashValue)
		{
			backToStart = true;
		}
	}

	if (D[trav] == EMPTY || (backToStart && firstAvail != -1))
	{
		D[(firstAvail == -1) ? trav : firstAvail] = data;
	}
	else if(backToStart) {
		printf("Dictionary is FULL.\n");
	}
}

void delete(Dictionary D, int data)
{
	int hashValue = hash(data);
	int trav = hashValue;
	bool backToStart = false;

	while (!backToStart && D[trav] != data && D[trav] != EMPTY)
	{
		trav = (trav + 1) % MAX;

		if (trav == hashValue)
		{
			backToStart = true;
		}
	}

	if (D[trav] == data)
	{
		D[trav] = DELETED;
	}
}

bool isMember(Dictionary D, int data)
{
	int hashValue = hash(data);
	int trav = hashValue;
	bool backToStart = false;

	while (!backToStart && D[trav] != data)
	{
		trav = (trav + 1) % MAX;

		if (trav == hashValue)
		{
			backToStart = true;
		}
	}

	return D[trav] == data ? true : false;
}