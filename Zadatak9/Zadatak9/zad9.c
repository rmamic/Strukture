#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct cvorstabla;
typedef struct cvorstabla* Stablo;
typedef struct cvorstabla {
	int el;
	Stablo L;
	Stablo D;
}Cvor;

Stablo stvori(int);
Stablo stvoriprazno(Stablo);
Stablo trazimin(Stablo);
Stablo trazimax(Stablo);
Stablo trazi(Stablo, int);
Stablo dodaj(Stablo, int);
Stablo brisi(Stablo, int);
void ispis(Stablo);

int main() {
	Stablo root = NULL;
	Stablo cvor = NULL;
	root = stvoriprazno(root);

	char c;
	int broj;

	printf("Odaberite:\n\td-dodaj novi broj u stablo\n\tb-brisi odredeni broj\n\tt-trazi odredeni broj\n\tm-trazi najmanji broj\n\tM-trazi najveci broj\n\ti-ispis brojeva\n\te-izlaz\n");

	while (1) {
		scanf(" %c", &c);
		switch (c)
		{
		case 'd':
			printf("Unesite broj koji zelite unijeti: ");
			scanf("%d", &broj);
			root = dodaj(root, broj);
			if (root == NULL)
				printf("Broj %d vec postoji.\n", broj);
			break;
		case 'b':
			printf("Unesite broj koji zelite obrisati: ");
			scanf("%d", &broj);
			cvor = brisi(root, broj);
			if (cvor == NULL)
				printf("Nema se sto izbrisati.\n");
			else printf("obrisali ste broj %d\n", broj);
			break;
		case 't':
			printf("Unesite koji broj zelite pretraziti: ");
			scanf("%d", &broj);
			cvor = trazi(root, broj);
			if (cvor == NULL)
				printf("Broj %d ne postoji u stablu\n", broj);
			else printf("Broj %d uspjesno pronaden\n", broj);
			break;
		case 'm':
			cvor = trazimin(root);
			if (cvor == NULL)
				printf("Stablo je prazno.\n");
			else printf("Najmanji broj je: %d\n", cvor->el);
			break;
		case 'M':
			cvor = trazimax(root);
			if (cvor == NULL)
				printf("Stablo je prazno.\n");
			else printf("Najveci broj je: %d\n", cvor->el);
			break;
		case 'i':
			printf("Ispis svih brojeva:\n");
			ispis(root);
			printf("\n");
			break;
		case 'e':
			printf("Izlaz!!!");
			root = stvoriprazno(root);
			if (root == NULL)
				printf("Uspjesno izbrisano!!\n");
			return 0;
		default:
			printf("Krivi odabir...\n");
			break;
		}


	}
	return 0;
}


Stablo stvoriprazno(Stablo S)
{
	if (S != NULL) {
		S->L = stvoriprazno(S->L);
		S->D = stvoriprazno(S->D);
		free(S);
	}
	return NULL;
}

Stablo trazimin(Stablo S)
{
	if (S == NULL)
		return NULL;

	else if (S->L == NULL)
		return S;

	return trazimin(S->L);

}

Stablo trazimax(Stablo S)
{
	if (S != NULL) {
		while (S->D != NULL)
			S = S->D;
	}
	return S;
}

Stablo trazi(Stablo S, int x)
{
	if (S == NULL)
		return NULL;

	else if (x > S->el)
		return trazi(S->D, x);

	else if (x < S->el)
		return trazi(S->L, x);

	return S;
}

Stablo dodaj(Stablo S, int x)
{
	if (S == NULL) {
		S = malloc(sizeof(Cvor));
		S->el = x;
		S->D = S->L = NULL;
	}
	else if (x < S->el)
		S->L = dodaj(S->L, x);

	else if (x > S->el)
		S->D = dodaj(S->D, x);

	else return NULL;

	return S;
}

Stablo brisi(Stablo S, int x)
{
	if (S == NULL)
		return NULL;

	else if (x < S->el)
		S->L = brisi(S->L, x);

	else if (x > S->el)
		S->D = brisi(S->D, x);

	else if (S->D && S->L != NULL)
	{
		Stablo temp = trazimin(S->D);
		S->el = temp->el;
		S->D = brisi(S->D, S->el);
	}
	else
	{
		Stablo temp = S;
		if (S->L == NULL)
			S = S->D;
		else 
			S = S->L;
		free(temp);
	}
	return S;
}

void ispis(Stablo S)
{
	if (S == NULL)
		return;
	ispis(S->L);
	printf("%d", S->el);
	ispis(S->D);
}