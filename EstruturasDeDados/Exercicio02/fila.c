#include <stdlib.h>
#include <stdio.h>
#include "fila.h"


struct Fila *criar(int tam)
{
	struct Fila* novo = NULL;
	
	if (tam > 0)
	{
		novo = (struct Fila*)malloc(sizeof(struct Fila));
	
		novo->tam = tam;
		novo->vet = (int*)malloc(tam * sizeof(int));
		
		novo->qtd = 0;
		novo->ini = 0;
		novo->fim = novo->ini + novo->qtd;
	}
		
	return novo;
}

int inserir(struct Fila *f, int num)
{
	int vrf = 0;
	
	if (f != NULL)
	{
		
		if (f->qtd < f->tam)
		{
			f->vet[f->fim] = num;
			f->qtd++;
			f->fim++;
			
			if (f->fim > f->tam - 1) f->fim = f->fim - f->tam;
			
			vrf = 1;
			
			//printf("\nPassou aqui\n");
			
		}
	}
	
	return vrf;
}

int remover(struct Fila *f, int *num)
{
	int vrf = 0;
	
	if(f != NULL && num != NULL)
	{
		if(f->qtd > 0)
		{
			*num = f->vet[f->ini];
			f->qtd--;
			f->ini++;
			
			if (f->ini > f->tam - 1) f->ini = f->ini - f->tam;
			
			vrf = 1;
		}		
	}
	
	return vrf;	
}

void imprimir(struct Fila *f)
{
	if(f != NULL)
	{
		int i, pos;
		
		for(i = 0; i < f->qtd; i++)
		{
			pos = f->ini + i;
			
			if(pos > f->tam - 1) pos = pos - f->tam;
			
			printf("%d - %d\n", i, f->vet[pos]);
		}
	}
}

void destruir(struct Fila *f)
{
	free(f->vet);
	free(f);
}



