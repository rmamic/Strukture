#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>


struct stog;
typedef struct stog* Position;
typedef struct stog {
	int el;
	Position next;
}Stog;

void pop(Position, int*);
void push(Position, int);
int racunaj(char, int, int);

int main() {
	FILE* fp;
	Stog S;
	int val = 0;
	char* buffer = NULL;
	int x = 0, y = 0, r = 0;
	int br, pr = 1, velicina, pr2 = 0;
	char c;
	S.next = NULL;
	fp = fopen("postfix.txt", "r");
	buffer = (char *)malloc(1000 * sizeof(char));

	if (!fp)
		return 1;

	while (!feof(fp)) {
		fgets(buffer, 1000, fp);
	}

	velicina = strlen(buffer);

	while (pr2 < velicina) {
		pr = sscanf(buffer, "%d %n", &br, &val);
		if (pr != 0 && pr != EOF) {
			push(&S, br);
		}
		else {
			pr = sscanf(buffer, "%c %n", &c, &val);
			pop(&S, &y);
			pop(&S, &x);
			r = racunaj(c, x, y);
			push(&S, r);
		}
		buffer += val;
		pr2 += val;
	}

	printf("Rezultat je: %d \n", S.next->el);

	fclose(fp);
	system("pause");
	return 0;
}


void push(Position S, int c)
{
	Position p;

	p = (Position)malloc(sizeof(struct stog));
	if (p)
	{
		p->el = c;
		p->next = S->next;
		S->next = p;
	}
}

void pop(Position S, int* x)
{
	Position temp;

	if (S->next != NULL) {
		temp = S->next;
		S->next = temp->next;
		*x = temp->el;
		free(temp);
	}
}

int racunaj(char op, int x, int y)
{
	int r = 0;
	switch (op)
	{
	case '+':
		r = x + y;
		break;
	case '-':
		r = x - y;
		break;
	case '*':
		r = x * y;
		break;
	case '/':
		if (y > 0)
			r = x / y;
		break;
	default:
		printf("Greska");
	}
	return r;
}