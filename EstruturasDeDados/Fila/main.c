#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fila.h"


int main()
{
	/*Fila fila = {NULL, NULL};

	Remover(&fila);

	Inserir(&fila, 5);
	Inserir(&fila, 25);
	Inserir(&fila, 38);

	Consultar(&fila);*/

	FilaVetor filaV = { NULL, 0, 0, 0, 0, 0, 0};

	FVCriar(&filaV, 10);

	srand(time(NULL));

	int dado, i;
	int min = -1000, max = 1000;


	for (i = 0; i < filaV.capacidade; i++)
	{
		dado = min + rand() % (max - min + 1);

		FVInserir(&filaV, dado);
	}

	FVConcultar(&filaV);

	printf("\n\n");

	FVRemover(&filaV);
	FVRemover(&filaV);
	FVRemover(&filaV);
	FVInserir(&filaV, 523);
	FVInserir(&filaV, 523);
	FVInserir(&filaV, 523);
	FVInserir(&filaV, 523);

	FVConcultar(&filaV);

	for(i = 0; i < 9; i++) FVRemover(&filaV);

	printf("\n\n");
	FVInserir(&filaV, 32);
	FVConcultar(&filaV);
	FVInserir(&filaV, 32);


	FVEsvaziar(&filaV);
	FVEsvaziar(&filaV);

	FVConcultar(&filaV);

	return 0;
}
