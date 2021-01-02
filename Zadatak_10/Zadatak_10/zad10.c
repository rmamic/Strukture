#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cvor;
struct stog;
typedef struct cvor *pozicija;
typedef struct stog *stogPozicija;

typedef struct cvor {
	char* el;
	pozicija D;
	pozicija L;
}Cvor;

typedef struct stog {
	pozicija elCvor;
	stogPozicija next;
}Stog;

void push(stogPozicija, pozicija);
pozicija pop(stogPozicija);
void infix(pozicija);
void postfix(pozicija);
void infixfile(pozicija, FILE*);

int main()
{
	FILE* fp = fopen("postfix.txt", "r");
	FILE* fo = fopen("infix.txt", "w");
	pozicija root = NULL;
	stogPozicija postf;

	postf = malloc(sizeof(Stog));
	postf->next = postf->elCvor = NULL;

	if (fp == NULL || fo == NULL) {
		puts("ERROR");
		return 0;
	}

	while (!feof(fp)) {
		pozicija novi = malloc(sizeof(Cvor));

		novi->el = malloc(sizeof(char) * 5);
		novi->el[4] = '\0';
		fscanf(fp, " %s", novi->el, 4);
		novi->D = novi->L = NULL;

		if (atoi(novi->el) || isalpha(novi->el[0])) {
			push(postf, novi);
		}
		else {
			novi->D = pop(postf);
			novi->L = pop(postf);
			push(postf, novi);
		}
	}
	fclose(fp);

	root = pop(postf);

	printf("\n\n Inorder ispis : \t");
	infix(root->L);
	printf(" %s", root->el);
	infix(root->D);
	printf("\n\n Postorder ispis : \t");
	postfix(root);
	printf("\n\n");
	free(postf);

	infixfile(root->L, fo);
	fprintf(fo, " %s", root->el);
	infixfile(root->D, fo);

	fclose(fo);
	return 0;
}

void push(stogPozicija S, pozicija C)
{
	stogPozicija novi;
	novi = malloc(sizeof(Stog));

	novi->elCvor = C;
	novi->next = S->next;
	S->next = novi;
}

pozicija pop(stogPozicija S)
{
	stogPozicija temp;
	pozicija novi;

	temp = S->next;
	S->next = temp->next;
	novi = temp->elCvor;
	free(temp);
	return novi;
}

void infix(pozicija C)
{
	if (C != NULL) {
		if (!(atoi(C->el) || isalpha(C->el[0]))) {
			printf("(");
		}
		infix(C->L);
		printf(" %s ", C->el);
		infix(C->D);
		if (!(atoi(C->el) || isalpha(C->el[0]))) {
			printf(")");
		}
	}
}

void postfix(pozicija C)
{
	if (C != NULL) {
		postfix(C->L);
		postfix(C->D);
		printf(" %s", C->el);
	}
}

void infixfile(pozicija C, FILE* fp)
{
	if (C != NULL) {
		if (!(atoi(C->el) || isalpha(C->el[0]))) {
			fprintf(fp, "(");
		}
		infixfile(C->L, fp);
		fprintf(fp, " %s ", C->el);
		infixfile(C->D, fp);
		if (!(atoi(C->el) || isalpha(C->el[0]))) {
			fprintf(fp, ")");
		}
	}
}