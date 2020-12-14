#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
	char ime[20];
	char prezime[20];
	int bodovi;
}lista;

void ispis(int, lista*);

float relativan(int);

int main() {
	int i = 0, brojStud = 0;
	FILE* fp;
	fp = fopen("lista.txt", "r");
	lista* liste = NULL;

	if (fp == NULL) printf("Error pri otvaranju datoteke");

	while (fgetc(fp) != '\n');

	while (!feof(fp)) {
		if (fgetc(fp) == '\n') brojStud++;
	}
	liste = (lista*)malloc(brojStud * sizeof(lista));

	rewind(fp);

	while (fgetc(fp) != '\n');

	while (!feof(fp)) {
		fscanf(fp, " %s %s %d", liste[i].ime, liste[i].prezime, &(liste[i].bodovi));
		i++;
	}

	ispis(brojStud, liste);

	fclose(fp);

	system("pause");
	return 0;
}
void ispis(int brStud, lista* liste) {
	int i;

	printf("IME	PREZIME		BODOVI(APSOLUTNI)	BODOVI(RELATIVNI) \n");

	for (i = 0; i < brStud; i++) {
		printf("%s\t%s\t\t%d\t\t\t%.2f\n", liste[i].ime, liste[i].prezime, liste[i].bodovi, relativan(liste[i].bodovi));
	}
}
float relativan(int i) {
	return (float)i / 60 * 100;
}