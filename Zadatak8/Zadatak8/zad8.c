#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAX (256)

struct direktorij;
typedef struct direktorij* pozicija;
typedef struct direktorij {
	char ime[MAX];
	pozicija brat;
	pozicija dijete;
}Dir;

struct stog;
typedef struct stog* stogPozicija;
typedef struct stog {
	pozicija data;
	stogPozicija next;
}Stog;

void makni(pozicija); //izaci iz programa
void md(pozicija, char*); //napriviti direktorij
pozicija cd(stogPozicija, pozicija, char*); //promijeniti trenutni direktorij
pozicija cd__(stogPozicija, pozicija); //otici na direktorij prije
void dir(pozicija); //ispisati direktorij


int main()
{
	char c[MAX];
	char IME[MAX];
	pozicija trenutni = malloc(sizeof(Dir));
	stogPozicija stog = malloc(sizeof(Stog));
	trenutni->brat = trenutni->dijete = NULL;
	stog->data = stog->next = NULL;
	strcpy(trenutni->ime, "");
	stogPozicija novi = malloc(sizeof(Stog));
	novi->data = trenutni;
	novi->next = stog->next;
	stog->next = novi;

	while (1) {
		printf("C:\ %s\>", trenutni->ime);

		scanf("%s", c);

		if (!strcmp(c, "md")) {
			scanf("%s", IME);
			md(trenutni, IME);
		}
		else if (!strcmp(c, "cd")) {
			scanf("%s", IME);
			trenutni = cd(stog, trenutni, IME);
		}
		else if (!strcmp(c, "dir")) {
			dir(trenutni->dijete);
		}
		else if (!strcmp(c, "cd..") || !strcmp(c, "cd ..")) {
			trenutni = cd__(stog, trenutni);
		}
		else if (!strcmp(c, "exit")) {
			while (stog->next->next != NULL)
				trenutni = cd__(stog, trenutni);
			free(stog->next);
			free(stog);
			makni(trenutni);
			return 0;
			}
		else
			printf("kriva komanda...");
	}
	return 0;
}

void makni(pozicija trenutni) {
	if (trenutni == NULL)
		return;
	makni(trenutni->brat);
	makni(trenutni->dijete);
	free(trenutni);
}

void md(pozicija trenutni, char* ime)
{
	if (trenutni->dijete == NULL) {

		pozicija novi = malloc(sizeof(Dir));
		strcpy(novi->ime, ime);
		novi->dijete = novi->brat = NULL;
		trenutni->dijete = novi;
	}

	else if (!strcmp(trenutni->dijete->ime, ime))

		printf("direktorij s ovakvim imenom već postoji...");

	else if (strcmp(trenutni->dijete->ime, ime) > 0) {

		pozicija novi = malloc(sizeof(Dir));
		novi->dijete = NULL;
		strcpy(novi->ime, ime);
		novi->brat = trenutni->dijete;
		trenutni->dijete = novi;
	}

	else
	{
		pozicija prethodni = trenutni->dijete;
		pozicija sadasnji = trenutni->dijete->brat;
		while (sadasnji != NULL) {
			if (strcmp(sadasnji->ime, ime) > 0) {
				break;
				prethodni = prethodni->brat;
				sadasnji = sadasnji->brat;
			}
		}
		pozicija novi = malloc(sizeof(Dir));
		strcpy(novi->ime, ime);
		novi->dijete = NULL;
		novi->brat = prethodni->brat;
		prethodni->brat = novi;
	}
}

pozicija cd(stogPozicija stog, pozicija trenutni, char* ime)
{
	pozicija temp = trenutni->dijete;
	while (temp != NULL)
	{
		if (!strcmp(temp->ime, ime))
		{
			stogPozicija novi = malloc(sizeof(Stog));
			novi->data = temp;
			novi->next = stog->next;
			stog->next = novi;
			return temp;
		}
		temp = temp->brat;
	}
	printf("Direktorij ne postoji...");
	return trenutni;
}

void dir(pozicija trenutni)
{
	printf("\n");
	while (trenutni != NULL)
	{
		printf("\t\t\t-%s\n", trenutni->ime);
		trenutni = trenutni->brat;
	}
}

pozicija cd__(stogPozicija stog, pozicija trenutni)
{
	if (strcmp(stog->next->data->ime, "") != 0)
	{
		stogPozicija temp = stog->next;
		pozicija novi = temp->next->data;
		stog->next = temp->next;
		free(temp);
		return novi;
	}
	else
		return trenutni;
}