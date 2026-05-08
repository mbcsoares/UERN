#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


struct Heap* criar(int tam)
{
	struct Heap* novo = (struct Heap*)malloc(sizeof(struct Heap));

	if (novo == NULL) return NULL;

	novo->v = (int*)malloc(tam * sizeof(int));

	if (novo->v == NULL)
	{
		free(novo);
		return NULL;
	}

	novo->tam = tam;
	novo->qtd = 0;

	return novo;
}

int inserir(struct Heap* h, int num)
{
	int ret = 0;

	if (h != NULL)
	{
		if (h->qtd < h->tam)
		{
			int no = h->qtd, temp;

			h->v[no] = num;

			h->qtd++;

			int pai = (no - 1) / 2;

			while (pai >= 0)
			{
				if (h->v[pai] <= h->v[no]) break;

				temp = h->v[pai];
				h->v[pai] = h->v[no];
				h->v[no] = temp;

				no = pai;
				pai = (no - 1) / 2;
			}

			ret = 1;
		}
	}

	return ret;
}

int remover(struct Heap* h, int* num)
{
	int ret = 0;

	if (h != NULL)
	{
		if (h->qtd > 0)
		{
			int no = 0, temp;

			*num = h->v[no];

			h->v[no] = h->v[h->qtd - 1]; //o último valor ocupa o lugar do nó raiz removido
			h->qtd--; //Retira-se o último elemento

			int filho = 2 * no + 1;

			while (filho < h->qtd) //Enquanto houver filhos
			{
				if (filho + 1 < h->qtd) //se há dois filhos
				{
					if (h->v[filho] > h->v[filho + 1]) //escolher o menor filho
					{
						filho = filho + 1;
					}
				}

				if (h->v[filho] >= h->v[no]) break; //se o menor filho for maior do que o pai, para o loop

				temp = h->v[no];
				h->v[no] = h->v[filho];
				h->v[filho] = temp;

				no = filho;
				filho = 2 * no + 1;
			}

			ret = 1;
		}
	}

	return ret;
}

void construir(struct Heap* h, int* vet, int tam, int qtd)
{
	if (h != NULL && vet != NULL && tam > 0 && qtd >= 0) //verificações críticas
	{
		if (qtd > 1)
		{
			int ultPai = (qtd - 2) / 2, temp, cont = 0;
			int no, pai, filho;

			no = ultPai; //ultimo no

			while (no >= 0)
			{
				do
				{
					filho = 2 * no + 1;

					if (filho < qtd)
					{
						if (filho + 1 < qtd)
						{
							if (vet[filho] > vet[filho + 1])
							{
								filho = filho + 1;
							}
						}

						if (vet[no] <= vet[filho]) break;

						temp = vet[no];
						vet[no] = vet[filho];
						vet[filho] = temp;
					}

					no = filho;

				} while (no < qtd);

				//printf("\n\n%d\n\n", no);

				cont++;
				no = ultPai - cont;
			}
		}

		h->tam = tam;
		h->qtd = qtd;
		h->v = vet;
	}
}

void destruir(struct Heap* h)
{
	free(h->v);
	free(h);
}


void imprimir(struct Heap* h)
{
	int i = 0;

	while (i < h->qtd)
	{
		printf("%d\n", h->v[i]);

		i++;
	}
}