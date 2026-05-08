#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

int main()
{
	int qtd = 0, tam = 15, x;
	
	struct Heap* h = criar(tam);
	
	printf("TESTE INSERÇÃO:\n\n");
	
	srand(time(NULL));

	for (qtd = 0; qtd < tam; qtd++)
	{
		if(inserir(h, rand() % 101) != 1) printf("Erro na inserção!\n");		
	}
	
	imprimir(h);	
	printf("\n\n");
	
	printf("TESTE REMOÇÃO:\n\n");
	
	for (qtd = 0; qtd < tam; qtd++)
	{
		if(remover(h, &x) != 1) printf("Erro na remoção!\n");		
	}
	
	imprimir(h);	
	printf("\n\n");
	
	if(remover(h, &x) != 1) printf("Erro na remoção OK - vetor vazio!\n");
	
	imprimir(h);
	printf("\n\n");
	
	
	printf("TESTE DE CONSTRUÇÃO:\n\n");
	
	free(h->v);
	h->qtd = 0;
	
	h->v = (int*)malloc(tam * sizeof(int));
	
	srand(time(NULL));

	for(qtd = 0; qtd < tam; qtd++)
	{
		h->v[qtd] = rand() % 101;
		printf("%d: %d\n", qtd, h->v[qtd]);
	}

	printf("\n\n");

	construir(h, h->v, tam, qtd);

	imprimir(h);
	printf("\n\n");

	destruir(h);
	
	

	return 0;
}
