#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"


Pilha *Inserir(Pilha *pilha, int dado)
{
	Pilha *topo = (Pilha*)malloc(sizeof(Pilha));
	
	topo->dado = dado;
	topo->prox = pilha;
	
	return topo;
}

Pilha *Remover(Pilha *pilha)
{
	if(pilha != NULL)
	{
		Pilha *aux = pilha;
	
		pilha = pilha->prox;
		free(aux);
	}	
	
	return pilha;
}

void Consultar(Pilha *pilha)
{
	while(pilha != NULL)
	{
		printf("%d\n", pilha->dado);
		pilha = pilha->prox;
	}
}

void Esvaziar(Pilha *pilha)
{
	Pilha *aux = NULL;
	
	while(pilha != NULL)
	{
		aux = pilha;
		pilha = pilha->prox;
		free(aux);
	}
}





