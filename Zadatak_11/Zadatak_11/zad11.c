#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*Napisati kod koji za zadane podatke studenata (matični broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
ključ računa da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim računa
ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. Studenti s istim
ključem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem ključu se nalaze
koji podaci) te ponuditi mogućnost da se za određenog studenta (prezime i ime) ispiše
njegov matični broj.*/

#define MAX (20)

struct student;
typedef struct student* pozicija;
typedef struct student {
	int matBroj;
	char ime[MAX];
	char prezime[MAX];
	pozicija next;
}Student;

int hash(char*, int);
void dodaj(pozicija, char*, char*, int);
void dodajN(pozicija, char*, char*, int);
void pronadji(pozicija, char*, char*);
void ispisi(pozicija);

int main()
{
	int velTab = 11;
	char c;
	char ime[MAX], prezime[MAX];
	int matBroj, kljuc;
	pozicija head[11];

	for (int i = 0; i < 11; i++) {
		head[i] = NULL;
		head[i] = malloc(sizeof(Student));
		head[i]->next = NULL;
	}

	printf(" Za dodati studenta - 'd'\n Za pronaci mat.broj odredjenog studenta - 'b'\n Za izaci - 'e'\n Za ispisati - 'i'\n");

	while (1) {
		scanf(" %c", &c);

		switch (c) {
		case 'd':
			printf("Unesite ime, prezime i maticni broj studenta: ");
			scanf("%s %s %d", ime, prezime, &matBroj);
			kljuc = hash(prezime, velTab);
			dodaj(head[kljuc], ime, prezime, matBroj);
			break;
		case 'b':
			printf("Unesite ime i prezime studenta: ");
			scanf("%s %s", ime, prezime);
			kljuc = hash(prezime, velTab);
			pronadji(head[kljuc], ime, prezime);
			break;
		case 'e':
			return 0;
		case 'i':
			ispisi(head);
			break;
		default:
			printf("Upisali ste krivu komandu, pokusajte ponovno...\n");
			break;
		}
	}

	return 0;
}

int hash(char* slovo, int velTab)
{
	int HashV = 0;
	int i = 0;
	while(i < 5 && slovo[i] != '\0'){
			HashV += slovo[i];
			i++;
	}
	return (HashV % velTab);
}

void dodaj(pozicija hash, char*i, char*p, int m)
{
	if (hash->next == NULL) {
		dodajN(hash, p, i, m);
	}

	while (hash->next != NULL) {
		if (hash->matBroj == m) {
			printf("Student s ovakvim maticnim brojem vec postoji...");
			return;
		}
		else if (strcmp(p, hash->prezime) < 0) {
			dodajN(hash, i, p, m);
			return;
		}
		else if (!strcmp(p, hash->prezime)) {
			if (!strcmp(i, hash->ime)) {
				printf("Student postoji. ");
				return;
			}
			else if (strcmp(i, hash->ime) < 0) {
				dodajN(hash, i, p, m);
				return;
			}
		}
		hash = hash->next;
	}
}

void dodajN(pozicija hash, char* i, char* p, int m)
{
	pozicija novi = malloc(sizeof(Student));

	if (novi == NULL)
		return;

	strcpy(novi->ime, i);
	strcpy(novi->prezime, p);
	novi->matBroj = m;
	novi->next = hash->next;
	hash->next = novi;
}

void pronadji(pozicija head, char* ime, char* prezime)
{
	while (head != NULL) {
		if (!strcmp(head->prezime, prezime))
			if (!strcmp(head->ime, ime)) {
				printf("Maticni broj studenta %s %s: %d\n", ime, prezime, head->matBroj);
				return;
			}
		head = head->next;
	}
	printf("Student ne postoji.\n");
}

void ispisi(pozicija head[])
{
	int i = 0;

	printf(" KLJUC\tPREZIME\t IME \tMATICNI BROJ\n");

	for (i; i < 11; i++) {
		printf(" %d", i);
		if (head[i]->next == NULL) {
			printf("\tPrazno...\n\n");
		}
		else {
			pozicija temp = head[i]->next;
			while (temp->next != NULL) {
				printf("\t%s\t %s \t%d \n", temp->prezime, temp->ime, temp->matBroj);
				temp = temp->next;
			}
			printf("\n");
		}
	}
}