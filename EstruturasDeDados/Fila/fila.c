#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

//=======================================//
//============ FILA DINÂMICA ============//

void Inserir(Fila* fila, int dado)
{
	No* novo = (No*)malloc(sizeof(No));

	novo->dado = dado;
	novo->prox = NULL;

	if (fila->fim != NULL)
	{
		fila->fim->prox = novo;
		fila->fim = novo;
	}
	else
	{
		fila->inicio = novo;
		fila->fim = novo;
	}
}

void Remover(Fila* fila)
{
	if (fila->inicio != NULL)
	{
		No* aux = fila->inicio;

		fila->inicio = aux->prox;

		if (aux->prox == NULL) fila->fim = NULL;

		free(aux);
	}
}

void Consultar(Fila* fila)
{
	No* aux = fila->inicio;

	while (aux != NULL)
	{
		printf("%d\n", aux->dado);
		aux = aux->prox;
	}

	printf("\n\n");
}

void Esvaziar(Fila* fila)
{
	while (fila->inicio != NULL)
	{
		Remover(fila);
	}
}


//=======================================//
//============ FILA ESTÁTICA ============//

void FVCriar(FilaVetor* fila, int capacidade)
{
	if (capacidade > 0)
	{
		fila->vetor = (int*)malloc(capacidade * sizeof(int));
		fila->capacidade = capacidade;

		fila->limInferior = 0;
		fila->limSuperior = fila->capacidade - 1;

		fila->quantidade = 0;
		fila->inicio = 0;
		fila->fim = fila->inicio + fila->quantidade;
	}
}

void FVInserir(FilaVetor* fila, int dado)
{
	if (fila->capacidade > fila->quantidade)
	{
		fila->quantidade++;
		fila->vetor[fila->fim] = dado;
		fila->fim = fila->inicio + fila->quantidade;

		if (fila->fim > fila->limSuperior) fila->fim = (fila->fim - fila->limSuperior) - 1;
	}
}

void FVConcultar(FilaVetor* fila)
{
	int i, pos;

	for (i = 0; i < fila->quantidade; i++)
	{
		pos = fila->inicio + i;

		if (pos > fila->limSuperior) pos = (pos - fila->limSuperior) - 1;
		
		printf("%d\n", fila->vetor[pos]);
	}
}

void FVRemover(FilaVetor* fila)
{
	if (fila->quantidade > 0)
	{
		fila->quantidade--;
		fila->inicio++;

		if (fila->inicio > fila->limSuperior) fila->inicio = (fila->inicio - fila->limSuperior) - 1;
	}
}

void FVEsvaziar(FilaVetor* fila)
{
	if (fila->vetor != NULL)
	{
		free(fila->vetor);

		fila->vetor = NULL;
		fila->capacidade = 0;

		fila->limInferior = 0;
		fila->limSuperior = 0;

		fila->quantidade = 0;
		fila->inicio = 0;
		fila->fim = 0;
	}
}


/*
void FVInserir(FilaVetor* fila, int dado);
void FVRemover(FilaVetor* fila);
void FVConcultar(FilaVetor* fila);
void FVEsvaziar(FilaVetor* fila);
*/
