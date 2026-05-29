#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS // Adicione esta linha para o strdup

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

#define TESTE(cond, msg) \
    if (cond) printf("[OK]   %s\n", msg); \
    else      printf("[ERRO] %s\n", msg);

int main(void)
{
    struct tabela_hash* t;
    int dado;
    int i;
    char chave[64];

    printf("=== TESTE COMPLETO HASH ===\n\n");


    /*
        1) criação inválida
    */
    TESTE(hash_criar(0, 10) == NULL,
        "hash_criar(0,10)");

    TESTE(hash_criar(10, 0) == NULL,
        "hash_criar(10,0)");



    /*
        2) criação válida
    */
    t = hash_criar(4, 20);

    TESTE(t != NULL,
        "hash_criar valido");



    /*
        3) inserções simples
    */
    TESTE(hash_inserir(t, "ana", 10),
        "inserir ana");

    TESTE(hash_inserir(t, "bruno", 20),
        "inserir bruno");

    TESTE(hash_inserir(t, "carla", 30),
        "inserir carla");



    /*
        4) busca existente
    */
    TESTE(hash_buscar(t, "ana", &dado) &&
        dado == 10,
        "buscar ana");



    /*
        5) busca inexistente
    */
    TESTE(!hash_buscar(t, "joao", &dado),
        "buscar inexistente");



    /*
        6) atualizar chave
    */
    TESTE(hash_inserir(t, "ana", 99),
        "reinserir ana");

    TESTE(hash_buscar(t, "ana", &dado) &&
        dado == 99,
        "ana atualizada");



    /*
        7) string vazia
    */
    TESTE(hash_inserir(t, "", 42),
        "inserir string vazia");

    TESTE(hash_buscar(t, "", &dado) &&
        dado == 42,
        "buscar string vazia");



    /*
        8) remover existente
    */
    TESTE(hash_remover(t, "bruno"),
        "remover bruno");

    TESTE(!hash_buscar(t, "bruno", &dado),
        "bruno removido");



    /*
        9) remover inexistente
    */
    TESTE(!hash_remover(t, "naoexiste"),
        "remover inexistente");



    /*
        10) várias inserções
        força colisões + expansão
    */
    for (i = 0; i < 1000; i++)
    {
        sprintf(chave, "chave_%d", i);

        TESTE(hash_inserir(t, chave, i),
            "insercao em lote");
    }



    /*
        11) verificar todas
    */
    for (i = 0; i < 1000; i++)
    {
        sprintf(chave, "chave_%d", i);

        TESTE(hash_buscar(t, chave, &dado) &&
            dado == i,
            "busca em lote");
    }



    /*
        12) remover metade
    */
    for (i = 0; i < 1000; i += 2)
    {
        sprintf(chave, "chave_%d", i);

        TESTE(hash_remover(t, chave),
            "remocao em lote");
    }



    /*
        13) validar metade removida
    */
    for (i = 0; i < 1000; i++)
    {
        sprintf(chave, "chave_%d", i);

        if (i % 2 == 0)
        {
            TESTE(!hash_buscar(t, chave, &dado),
                "removidos ausentes");
        }
        else
        {
            TESTE(hash_buscar(t, chave, &dado) &&
                dado == i,
                "remanescentes presentes");
        }
    }



    /*
        14) parâmetros NULL
    */
    TESTE(!hash_inserir(NULL, "a", 1),
        "inserir NULL");

    TESTE(!hash_remover(NULL, "a"),
        "remover NULL");

    TESTE(!hash_buscar(NULL, "a", &dado),
        "buscar NULL");

    TESTE(!hash_buscar(t, NULL, &dado),
        "buscar chave NULL");

    TESTE(!hash_buscar(t, "a", NULL),
        "buscar dado NULL");



    /*
        15) destruir
    */
    hash_destruir(t);

    printf("\nFim dos testes.\n");

    return 0;
}