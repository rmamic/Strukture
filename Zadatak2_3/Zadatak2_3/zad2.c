#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M (256)

struct person;
typedef struct person* Position;
typedef struct person {
	char ime[M];
	char prezime[M];
	int godina;
	Position next;
}Person;

Position noviStudent(char*, char*, int);
void Ispis(Position);
void unosPocetak(Position, Position);
void unosKraj(Position, Position);
void unosIza(Position, Position, char*);
void unosIspred(Position, Position, char*);

Position pronalazak(Position, char*);
Position pronalazakPret(Position, char*);

void brisi(Position, char*);
void sortUnos(Position, Position);
void sortiraj_listu(Position);

void upisi_u_file(Position, char*);
void cita_iz_filea(char*);

int main() {
	Position head = (Position)malloc(sizeof(struct person));

	Position s3 = noviStudent("Ante", "Antic", 2000);
	Position s2 = noviStudent("Mate", "Matic", 2000);
	Position s1 = noviStudent("Stipe", "Stipic", 2000);

	unosPocetak(head, s1);
	unosKraj(head, s2);
	unosKraj(head, s3);

	sortiraj_listu(head);

	Ispis(head);
	brisi(head, "Antic");

	s3 = noviStudent("Ante", "Antic", 2000);
	unosIspred(head, s3, "Stipic");

	Position s4 = noviStudent("Peder", "Veliki", 2000);
	unosIza(head, s4, "Stipic");

	Ispis(head);

	upisi_u_file(head, "lista.txt");

	cita_iz_filea("lista.txt");

	return 0;
}

Position noviStudent(char* Ime, char* Prezime, int god)
{
	Position p;

	p = (Position)malloc(sizeof(struct person));

	p->godina = god;
	strcpy(p->ime, Ime);
	strcpy(p->prezime, Prezime);
	p->next = NULL;

	return p;
}

void Ispis(Position head)
{
	Position p = NULL;

	printf("KONTENT LISTE: \n\n");
	for (p = head->next; p != NULL; p = p->next) {
		printf("\t %s %s %d \n", p->ime, p->prezime, p->godina);
	}
	printf("\r\n");
}

void unosPocetak(Position head, Position new_element)
{
	new_element->next = head->next;
	head->next = new_element;
}

void unosKraj(Position p, Position n)
{
	while (p->next != NULL) {
		p = p->next;
	}
	unosPocetak(p, n);
}

Position pronalazak(Position p, char* prez) {
	Position temp;
	for (temp = p->next; temp != NULL; temp = temp->next) {
		if (strcmp(temp->prezime, prez) == 0) {
			return temp;
		}
	}
	return NULL;
}

Position pronalazakPret(Position p, char* prezimen) {
	Position temp;
	Position before = p;

	for (temp = p->next; temp != NULL; temp = temp->next) {
		if (strcmp(temp->prezime, prezimen) == 0) {
			return before;
		}

		before = temp;
	}
	return NULL;
}

void brisi(Position p, char* prezimen) {
	Position prev;
	prev = pronalazakPret(p, prezimen);

	if (prev != NULL) {
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
}
void unosIza(Position p, Position n, char* prezimen)
{
	Position k;
	k = pronalazak(p, prezimen);
	if (k == NULL) {
		printf("ne postoji!\n");
		return NULL;
	}
	else unosPocetak(k, n);
}

void unosIspred(Position p, Position n, char* prezimen)
{
	Position k;
	k = pronalazakPret(p, prezimen);
	if (k == NULL) {
		printf("ne postoji!\n");
		return NULL;
	}
	else unosPocetak(k, n);
}

void sortUnos(Position p, Position n)
{
	while (p->next != NULL && strcmp(n->prezime, p->next->prezime))
		p = p->next;
	unosPocetak(p, n);
}

void sortiraj_listu(Position head) {
	Position temp1, temp2, swap1, swap2;


	for (temp1 = head->next; temp1 != NULL; temp1 = temp1->next) {
		for (temp2 = head->next; temp2->next != NULL; temp2 = temp2->next) {

			char* p1_val = temp2->prezime;
			char* p2_val = temp2->next->prezime;

			if (strcmp(p1_val, p2_val) > 0) {
				swap1 = temp2;
				swap2 = temp2->next;

				Position prethodni = pronalazakPret(head, swap1->prezime);

				prethodni->next = swap2;
				Position temp_swap = swap2->next;
				swap2->next = swap1;
				swap1->next = temp_swap;
				break;
			}
		}
	}
}

void upisi_u_file(Position head, char* ime)
{
	FILE* fp = fopen(ime, "w");

	if (fp == NULL) {
		printf("nije stvorilo");
		return 0;
	}
	fprintf(fp, "IME	PREZIME	GODINA");
	while (head->next != NULL) {
		fprintf(fp, "%s\t%s %d", head->ime, head->prezime, head->godina);
		head = head->next;
	}
	fclose(fp);
}

void cita_iz_filea(char* file)
{
	FILE* fp = fopen(file, "r");
	char ime[30];
	char prezime[30];
	int god;

	while (fgetc(fp) != '\n');
	while (!feof(fp)) {
		fscanf(fp, " %s %s %d", ime, prezime, &god);
		printf("\n%s %s %d", ime, prezime, god);
	}
	fclose(fp);
}