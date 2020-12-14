#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Polinom;
typedef struct Polinom* Pozicija;
typedef struct Polinom {
	int koef;
	int exp;
	Pozicija next;
}polinom;

void brisi(Pozicija, int);
Pozicija trazi_pret(Pozicija, int);
void unos_pocetak(Pozicija, Pozicija);
void unos_kraj(Pozicija, Pozicija);
void sort_unos(Pozicija, int, int);
Pozicija novi_clan(int, int);
void ucitan_file(char*, Pozicija);
void ispisi(Pozicija);
polinom zbrajanje(Pozicija, Pozicija);
polinom pomnozi(Pozicija, Pozicija);
void preradi_kod(Pozicija);
int duljina_liste(Pozicija);

int main()
{
	polinom head1, head2, z, p;
	head1.next = NULL;
	head2.next = NULL;

	ucitan_file("text1.txt", &head1);
	ucitan_file("text2.txt", &head2);

	z = zbrajanje(&head1, &head2);
	printf(" rezultat zbrajanja: \n");
	ispisi(&z);

	p = pomnozi(&head1, &head2);
	printf(" rezultat mnozenja je: \n");
	ispisi(&p);

	return 0;
}

void ucitan_file(char* file, Pozicija head)
{
	FILE* fp = fopen(file, "r");
	int KOEF, EXP;


	if (fp == NULL)
		printf("\ngreska");
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &KOEF, &EXP);
		Pozicija n = novi_clan(KOEF, EXP);
		sort_unos(head, KOEF, EXP);
		preradi_kod(head);
	}
	ispisi(head);
	fclose(fp);
}

Pozicija novi_clan(int k, int e)
{
	Pozicija p = malloc(sizeof(polinom));

	p->exp = e;
	p->koef = k;
	p->next = NULL;

	return p;
}

void unos_kraj(Pozicija head, Pozicija q)
{
	while (head->next != NULL) {
		head = head->next;
	}
	unos_pocetak(head, q);
}

void unos_pocetak(Pozicija head, Pozicija q)
{
	if (q->koef == 0) {
		free(q);
	}
	else {
		q->next = head->next;
		head->next = q;
	}
}

void sort_unos(Pozicija head, int koef, int exp)
{
	while (head->next != NULL && head->next->exp < exp)
		head = head->next;
	Pozicija q = (Pozicija)malloc(sizeof(polinom));

	q->exp = exp;
	q->koef = koef;

	unos_pocetak(head, q);
}

void ispisi(Pozicija head)
{
	head = head->next;
	for (head; head != NULL; head = head->next) {
		printf(" %dx^%d\n", head->koef, head->exp);
	}
	printf("\n");
}

Pozicija trazi_pret(Pozicija head, int exp)
{
	while (head->next != NULL && head->next->exp != exp)
		head = head->next;
	if (head == NULL)
		return NULL;
	return head;
}

void brisi(Pozicija p, int exp)
{
	Pozicija pret = trazi_pret(p, exp);

	if (pret != NULL) {
		p = pret->next;
		pret->next = p->next;
		free(p);
	}
}

void preradi_kod(Pozicija head)
{
	Pozicija prev = head;
	head = head->next;
	while (head->next != NULL) {
		if (head->exp == head->next->exp) {
			head->next->koef += head->koef;
			prev->next = head->next;
			free(head);
			head = prev->next;
		}
		else
		{
			head = head->next;
		}
		prev = prev->next;
	}
}

polinom zbrajanje(Pozicija head1, Pozicija head2)
{
	polinom c;
	c.next = NULL;
	head1 = head1->next;
	head2 = head2->next;

	while (head1 != NULL && head2 != NULL) {
		if (head1->exp == head2->exp) {
			unos_kraj(&c, novi_clan(((head1->koef) + (head2->koef)), head1->exp));
			head1 = head1->next;
			head2 = head2->next;
		}
		else if (head1->exp < head2->exp) {
			unos_kraj(&c, novi_clan(head1->koef, head1->exp));
			head1 = head1->next;
		}
		else if (head1->exp > head2->exp) {
			unos_kraj(&c, novi_clan(head2->koef, head2->exp));
			head2 = head2->next;
		}
	}
	if (head1 == NULL) {
		while (head2 != NULL) {
			unos_kraj(&c, novi_clan(head2->koef, head2->exp));
			head2 = head2->next;
		}
	}
	else if (head2 == NULL) {
		while (head1 != NULL) {
			unos_kraj(&c, novi_clan(head1->koef, head1->exp));
			head1 = head1->next;
		}
	}
	return c;
}
polinom pomnozi(Pozicija head1, Pozicija head2)
{
	int d1, d2;
	d1 = duljina_liste(head1);
	d2 = duljina_liste(head2);
	polinom c;
	c.next = NULL;
	Pozicija h2 = NULL, h1 = NULL;
	head1 = head1->next;
	head2 = head2->next;
	h1 = head1;
	h2 = head2;

	if (d1 <= d2) {
		while (head1 != NULL) {
			while (head2 != NULL) {
				sort_unos(&c, (head1->koef * head2->koef), (head1->exp + head2->exp));
				head2 = head2->next;
			}
			head2 = h2;
			head1 = head1->next;
		}
	}
	else {
		while (head2 != NULL) {
			while (head1 != NULL) {
				sort_unos(&c, (head2->koef * head1->koef), (head1->exp + head2->exp));
				head1 = head1->next;
			}
			head1 = h1;
			head2 = head2->next;
		}
	}

	return c;
}

int duljina_liste(Pozicija head)
{
	int brojac = 0;
	while (head->next != NULL) {
		brojac++;
		head = head->next;
	}
	return brojac;
}