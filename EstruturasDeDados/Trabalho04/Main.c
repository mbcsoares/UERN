#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

int main()
{
	int tam = 7, qtd;

	struct Heap* h = (struct Heap*)malloc(sizeof(struct Heap));
	int* vet = (int*)malloc(7 * sizeof(int));

	srand(time(NULL));

	for (qtd = 0; qtd < tam; qtd++)
	{
		vet[qtd] = rand() % 101;
		printf("%d\n", vet[qtd]);
	}

	printf("\n\n");

	construir(h, vet, tam, qtd);

	imprimir(h);



	destruir(h);

	return 0;
}
