#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#define MIN 10
#define MAX 100 

struct stog;
typedef struct stog* Position;
typedef struct stog {
	int el;
	Position next;
}Stog;

int pop(Position);
Position novi_clan(void);
void Ispis(Position);
void push(Position, Position);
int random(int, int);

int main() {
	Stog S;
	Position d;
	char c;
	int broj;
	S.next = NULL;

	srand((unsigned)time(NULL));

	while (1) {
		printf("upisi na stog: (+) brisi sa stoga: (-) ispisi: (i) izadji: (b)\n");
		scanf(" %c", &c);
		switch (c) {
		case '+':
			d = novi_clan();
			push(&S, d);
			break;
		case '-':
			broj = pop(&S);
			Ispis(&S);
			printf("izbrisani broj je %d\n", broj);
			break;
		case 'i':
			Ispis(&S);
			break;
		case 'b':
			return 0;
		default:
			printf("Greska!");
			return 1;
		}
	}
	return 0;
}


Position novi_clan(void)
{
	Position p;
	int el;

	el = random(MIN, MAX);

	p = (Position)malloc(sizeof(struct stog));
	p->el = el;
	p->next = NULL;

	return p;
}

int random(int min, int max)
{
	int bm = max - min + 1;
	int gr = RAND_MAX - (RAND_MAX % bm);
	int rnd = rand();
	while (rnd > gr) rnd = rand();
	return (rnd % bm) + min;
}

void push(Position S, Position p)
{
	p->next = S->next;
	S->next = p;
}

void Ispis(Position S)
{
	printf("elementi stoga: ");
	S = S->next;
	for (S; S != NULL; S = S->next) {
		printf("%d \n\t\t", S->el);
	}
	printf("\r\n\n");
}


int pop(Position S)
{
	int x;
	Position temp;

	if (S->next != NULL) {
		x = S->next->el;
		temp = S->next;
		S->next = temp->next;
		free(temp);
		return x;
	}
	return -1;
}