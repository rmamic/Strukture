#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct broj* Pozicija;

typedef struct broj {
	int br;
	Pozicija next;
}Broj;

Broj unija(Pozicija, Pozicija);
Broj presjek(Pozicija, Pozicija);
Pozicija novi_broj(int);
void unos_pocetak(Pozicija, Pozicija);
void unos_kraj(Pozicija, Pozicija);
void sort_unos(Pozicija, int);
void ispis(Pozicija);
void ucitan_file(char*, Pozicija);
void preradi_kod(Pozicija);

int main()
{
	Broj head1, head2, presj, unij;
	head1.next = NULL;
	head2.next = NULL;
	ucitan_file("lista1.txt", &head1);
	ucitan_file("lista2.txt", &head2);
	presj = presjek(&head1, &head2);
	unij = unija(&head1, &head2);
	printf("Presjek lista: \n");
	ispis(&presj);
	printf("Unija lista: \n");
	ispis(&unij);

	return 0;
}

Pozicija novi_broj(int c) {
	Pozicija q = (Pozicija)malloc(sizeof(Broj));

	q->br = c;
	q->next = NULL;
	return q;
}

void unos_pocetak(Pozicija head, Pozicija c) {
	c->next = head->next;
	head->next = c;
}

void unos_kraj(Pozicija head, Pozicija c) {
	while (head->next != NULL)
		head = head->next;
	unos_pocetak(head, c);
}

void sort_unos(Pozicija head, int x) {
	while (head->next != NULL && head->next->br < x)
		head = head->next;
	Pozicija q = (Pozicija)malloc(sizeof(Broj));
	q->br = x;
	unos_pocetak(head, q);
}

void preradi_kod(Pozicija head)
{
	Pozicija prev = head;
	head = head->next;
	while (head->next != NULL) {
		if (head->br == head->next->br) {
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

void ispis(Pozicija head) {

	for (head = head->next; head != NULL; head = head->next)
		printf("%d", head->br);

	printf("\n");
}

void ucitan_file(char* file, Pozicija head)
{
	FILE* fp = fopen(file, "r");
	int broj;

	if (fp == NULL)
		printf("\ngreska");
	while (!feof(fp)) {
		fscanf(fp, "%d", &broj);
		Pozicija n = novi_broj(head, broj);
		sort_unos(head, broj);
		preradi_kod(head);
	}
	ispis(head);
	fclose(fp);
}

Broj unija(Pozicija head1, Pozicija head2) {
	Broj vraca;
	vraca.next = NULL;
	head1 = head1->next;
	head2 = head2->next;

	while (head1 != NULL && head2 != NULL) {
		if (head1->br < head2->br) {
			unos_kraj(&vraca, novi_broj(head1->br));
			head1 = head1->next;
		}
		else if (head1->br > head2->br) {
			unos_kraj(&vraca, novi_broj(head2->br));
			head2 = head2->next;
		}
		else if (head1->br == head2->br) {
			unos_kraj(&vraca, novi_broj(head1->br));
			head1 = head1->next;
			head2 = head2->next;
		}
	}
	if (head2 == NULL) {
		while (head1 != NULL) {
			unos_kraj(&vraca, novi_broj(head1->br));
			head1 = head1->next;
		}
	}
	if (head1 == NULL) {
		while (head2 != NULL) {
			unos_kraj(&vraca, novi_broj(head2->br));
			head2 = head2->next;
		}
	}
	return vraca;
}

Broj presjek(Pozicija head1, Pozicija head2) {
	Broj vraca;
	vraca.next = NULL;
	head1 = head1->next;
	head2 = head2->next;

	while (head1 != NULL && head2 != NULL) {
		if (head1->br < head2->br) {
			head1 = head1->next;
		}
		else if (head1->br > head2->br) {
			head2 = head2->next;
		}
		else if (head1->br == head2->br) {
			unos_kraj(&vraca, novi_broj(head1->br));
			head1 = head1->next;
			head2 = head2->next;
		}
	}
	return vraca;
}
