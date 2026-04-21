#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreavl.h"

int main()
{
    struct NoAVL* arv = NULL;

    /*arv = inserirAVL(arv, 5, "Micael");
    arv = inserirAVL(arv, 3, "Lucas");
    arv = inserirAVL(arv, 2, "Leo");

    printf("\nArvore 01: ");
    imprimir(arv);
    printf("\nArvore 01 - FB: ");
    imprimirFB(arv);

    arv = inserirAVL(arv, 10, "Paulo");
    arv = inserirAVL(arv, 5, "Pedro");
    arv = inserirAVL(arv, 59, "Tiago");
    arv = inserirAVL(arv, -54, "Joao");
    arv = inserirAVL(arv, -63, "Marcos");

    printf("\n\nArvore 02: ");
    imprimir(arv);
    printf("\nArvore 02 - FB: ");
    imprimirFB(arv);*/

    /*arv = inserirAVL(arv, 10, "Micael");
    arv = inserirAVL(arv, 20, "Micael");
    arv = inserirAVL(arv, 30, "Micael");
    arv = inserirAVL(arv, 40, "Micael");
    arv = inserirAVL(arv, 50, "Micael");
    arv = inserirAVL(arv, 25, "Micael");
    arv = inserirAVL(arv, 60, "Micael");
    arv = inserirAVL(arv, 70, "Micael");
    arv = inserirAVL(arv, 80, "Micael");
    arv = inserirAVL(arv, 90, "Micael");*/

    int num[] = { 74, 15, 88, 42, 6, 93, 37, 52, 19, 80, 2, 66, 49, 13, 25 };
    //int num[] = { 74, 15, 88 };

    int rem = 25;

    for (int i = 0; i < sizeof(num) / sizeof(int); i++)
    {
        if(num[i] == rem) arv = inserirAVL(arv, num[i], "Micael");
        else  arv = inserirAVL(arv, num[i], "Nome");        
    }

    printf("\n\nArvore: ");
    imprimir(arv);
    printf("\n\nArvore - FB: ");
    imprimirFB(arv);

    char* nome = NULL;

    arv = removerAVL(arv, rem, &nome);

    if(nome != NULL) printf("\n\nNome: %s", nome);

    printf("\n\nArvore: ");
    imprimir(arv);
    printf("\n\nArvore - FB: ");
    imprimirFB(arv);

    /*arv = removerAVL(arv, -34, nome);

    printf("\n\nArvore: ");
    imprimir(arv);
    printf("\n\nArvore - FB: ");
    imprimirFB(arv);*/

    return 0;
}
