#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include <time.h>


int main(int argc, char *argv[])
{
	int tam = 10;
	struct Fila* fila = criar(tam);
	
	srand(time(NULL));
	
	int dado, i, vrf = 0;	
	
	for(i = 0; i < tam; i++)
	{
		dado = -500 + rand() % (1001);
		vrf = inserir(fila, dado);
		
		printf("%d - %d\n", i, vrf);
	}
	
	printf("\n\n");
	
	imprimir(fila);
	
	vrf = remover(fila, &dado);
	printf("\n%d - %d\n", vrf, dado);
	
	printf("\n\n");
	
	imprimir(fila);
	vrf = inserir(fila, 46);
	vrf = inserir(fila, 47);
	
	printf("\n\n");
	
	imprimir(fila);
	printf("\n\n");
	
	destruir(fila);
	
	
	return 0;
}
