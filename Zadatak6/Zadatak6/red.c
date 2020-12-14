#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#define MIN 10
#define MAX 100 

struct red;
typedef struct red* Position;
typedef struct red {
	int el;
	Position next;
}Red;

int pop(Position);
Position novi_clan(void);
void Ispis(Position);
void push(Position, Position);
int random(int, int);

int main() {
	Red R;
	Position d;
	char c;
	int broj;
	R.next = NULL;

	srand((unsigned)time(NULL));

	while (1) {
		printf("upisi u red: (+) brisi iz reda: (-) ispisi: (i) izadji: (b)\n");
		scanf(" %c", &c);
		switch (c) {
		case '+':
			d = noviclan();
			postavi(&R, d);
			break;
		case '-':
			broj = pop(&R);
			Ispis(&R);
			printf("izvadili smo broj %d \n", broj);
			break;
		case 'i':
			Ispis(&R);
			break;
		case 'b':
			return 0;
		default:
			printf("Greska!");
			return 1;
		}
	}
	system("pause");
	return 0;
}


Position novi_clan(void)
{
	Position p;
	int el;

	el = random(MIN, MAX);

	p = (Position)malloc(sizeof(struct red));
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

void Ispis(Position R)
{
	printf("elementi reda: ");
	R = R->next;
	for (R; R != NULL; R = R->next) {
		printf("%d \n\t\t", R->el);
	}
	printf("\r\n\n");
}

void push(Position R, Position p)
{
	p->next = R->next;
	R->next = p;
}

int pop(Position R)
{
	int x;
	Position temp;
	if (R->next != NULL) {
		Position pret = R;
		R = R->next;
		while (R->next != NULL) { R = R->next; pret = pret->next; }
		x = R->el;
		R = pret->next;
		pret->next = R->next;
		free(R);
		return x;
	}
	return -1;
}