#ifndef HEAP_H
#define HEAP_H

struct Heap
{
	int tam;
	int qtd;
	int* v; //ponteiro para o vetor 
};

struct Heap* criar(int tam);
int inserir(struct Heap* h, int num);
int remover(struct Heap* h, int* num);
void construir(struct Heap* h, int* vet, int tam, int qtd);
void destruir(struct Heap* h);

#endif









/*
struct Heap *criar(int tam);
int inserir(struct Heap *h, int num);
int remover(struct Heap *h, int *num);
void construir(struct Heap *h, int *vet, int tam, int qtd);
void destruir(struct Heap *h);
*/

/*
#include <stdio.h>
#include <stdlib.h>

struct Heap
{
	int tam;
	int qtd;
	int *v; //ponteiro para o vetor
};


struct Heap *criar(int tam)
{
	struct Heap* novo = (struct Heap*)malloc(sizeof(struct Heap));

	if(novo == NULL) return NULL;

	novo->v = (int*)malloc(tam * sizeof(int));

	if(novo->v == NULL)
	{
		free(novo);
		return NULL;
	}

	novo->tam = tam;
	novo->qtd = 0;

	return novo;
}

int inserir(struct Heap *h, int num)
{
	int ret = 0;

	if(h != NULL)
	{
		if(h->qtd < h->tam)
		{
			int no = h->qtd, temp;
			int pai = (no - 1)/2;

			h->v[no] = num;

			h->qtd++;

			while(pai >= 0)
			{
				if(h->v[pai] <= h->v[no]) break;

				temp = h->v[pai];
				h->v[pai] = h->v[no];
				h->v[no] = temp;

				no = pai;
				pai = (no - 1)/2;
			}

			ret = 1;
		}
	}

	return ret;
}

int Maximo(int a, int b)
{
	if(a > b) return a;

	return b;
}

int removerNum(struct Heap *h, int *num)
{
	int ret = 0;

	if(h != NULL)
	{
		if(h->qtd > 0)
		{
			int no = 0;

			while(h->v[no] != *num)
			{
				no++;

				if(no > h->qtd - 1) return ret;
			}

			*num = h->v[no];

			//printf("\n\n%d\n\n", h->v[no]);

			int filho;

			do
			{
				filho = 2 * no + 1;

				printf("\n\n%d\n\n", h->v[filho]);

				if(filho < h->qtd)
				{
					if(filho + 1 < h->qtd)
					{
						if(h->v[filho] > h->v[filho + 1])
						{
							filho = filho + 1;
						}
					}

					h->v[no] = h->v[filho];
				}
				else if(no % 2 == 0)
				{
					h->v[no] = h->v[no - 1];

					filho = no - 1;
				}
				else
				{
					h->qtd--;

					break;
				}

				no = filho;
			}
			while(h->qtd > 0 && no < h->qtd);

			ret = 1;
		}
	}

	return ret;
}

int remover(struct Heap *h, int *num)
{
	*num = h->v[0];

	if(removerNum(h, num) == 1)
	{
		return 1;
	}
	else
	{
		num = NULL;

		return 0;
	}
}

void imprimir(struct Heap *h)
{
	int i = 0;

	while(i < h->qtd)
	{
		printf("%d\n", h->v[i]);

		i++;
	}
}

void destruir(struct Heap *h)
{
	free(h->v);
	free(h);
}

int main()
{
	struct Heap* h = NULL;

	h = criar(5);

	inserir(h, 1008);
	inserir(h, 47);
	inserir(h, 10);
	inserir(h, 397);
	inserir(h, 53);


	imprimir(h);

	int* x;

	remover(h, x);
	imprimir(h);

	remover(h, x);
	imprimir(h);

	remover(h, x);
	imprimir(h);

	remover(h, x);
	imprimir(h);

	//remover(h, x);
	//imprimir(h);

	printf("\n\n%d\n\n", h->qtd);


	printf("\n\n");


	destruir(h);

	return 0;
}

*/

/*
struct Heap *criar(int tam);
int inserir(struct Heap *h, int num);
int remover(struct Heap *h, int *num);
void construir(struct Heap *h, int *vet, int tam, int qtd);
void destruir(struct Heap *h);
*/