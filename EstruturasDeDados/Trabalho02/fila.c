#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "fila.h"
#include <string.h>


struct No* inserir(struct No* fila, char* nome)
{
	if (fila != NULL && nome != NULL)
	{
		struct No* aux = fila;
		struct No* novo = (struct No*)malloc(sizeof(struct No));

		if (novo == NULL) return fila;

		novo->prox = NULL;
		novo->nome = (char*)malloc(strlen(nome) + 1);

		if (novo->nome == NULL)
		{
			free(novo);
			return fila;
		}

		strcpy(novo->nome, nome);

		while (aux->prox != NULL) aux = aux->prox;

		aux->prox = novo;	
	}
	else if (nome != NULL)
	{
		fila = (struct No*)malloc(sizeof(struct No));

		if (fila == NULL) return NULL;

		fila->prox = NULL;
		fila->nome = (char*)malloc(strlen(nome) + 1);

		if (fila->nome == NULL)
		{
			free(fila);
			return NULL;
		}

		strcpy(fila->nome, nome);
	}
	
	return fila;
}

struct No* remover(struct No* fila, char** nome)
{
	if (fila != NULL && nome != NULL)
	{
		struct No* aux = fila;

		*nome = fila->nome;
		fila = fila->prox;

		free(aux);
	}
	else if (nome != NULL)
	{
		*nome = NULL;
	}

	return fila;
}

int tamanho(struct No* fila)
{
	int i = 0;

	while (fila != NULL)
	{
		i++;
		fila = fila->prox;
	}

	return i;
}

void imprimir(struct No* fila)
{
	int i = 0;

	while (fila != NULL)
	{
		printf("%d - %s\n", ++i, fila->nome);
		fila = fila->prox;
	}
}

void destruir(struct No* fila)
{
	struct No* aux = NULL;

	while (fila != NULL)
	{
		aux = fila->prox;

		free(fila->nome);
		free(fila);

		fila = aux;
	}
}


/*

struct No* remover(struct No* fila, char** nome);
int tamanho(struct No* fila);
void imprimir(struct No* fila);
void destruir(struct No* fila);
*/