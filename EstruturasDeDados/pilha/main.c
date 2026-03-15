#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilha.h"

int main()
{
    Pilha *pilha = NULL;

    pilha = Inserir(pilha, 10);

    srand(time(NULL));

    int dado, i, qnt = 20;
    int min = -1000, max = 1000;


    for (i = 0; i < qnt; i++)
    {
        dado = min + rand() % (max - min + 1);

        pilha = Inserir(pilha, dado);
    }

    printf("--- DADOS NA PILHA ---");
    printf("\n\n");
    Consultar(pilha);

    printf("\n\n");

    printf("--- REMOÇÃO DE TOPO DA PILHA ---");
    printf("\n\n");
    pilha = Remover(pilha);
    printf("--- ATUALIZAÇÃO DE DADOS NA PILHA ---");
    printf("\n\n");
    Consultar(pilha);

    printf("\n\n");

    printf("--- ESVAZIAR PILHA ---");
    printf("\n\n");
    printf("endereço de pilha: %x\n", pilha);
    Esvaziar(pilha);
    printf("%d", pilha == NULL);

    printf("\n\n");


    return 0;
}
