#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS // Adicione esta linha para o strdup

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"



static int semente_inicializada = 0; //garente que a semente do srand() seja inicializada smente uma vez


int* VetorAleatorio(int tam)
{
    int* novo = (int*)malloc(tam * sizeof(int));

    if (novo != NULL)
    {
        int i, j;

        if (!semente_inicializada)
        {
            srand(time(NULL)); //Garante que srand() seja iniciado somente uma vez.

            semente_inicializada = 1;
        }

        //srand(time(NULL)); //Chamdas sucessivas da função criar podem comprometer a aleatoriedade

        for (i = 0; i < tam; i++)
        {
            novo[i] = rand() % (10 * tam) + 1; //o 10 reduz a chance de o mesmo numero ser escolhido duas vezes

            j = 0;

            while (j < i)
            {
                if (novo[j] == novo[i])
                {
                    i--; //o proximo loop for será para a posição i atual
                    break;
                }

                j++;
            }

        }
    }

    return novo;
}

struct LL** VetorLL(int tam)
{
    struct LL** novo = (struct LL**)malloc(tam * sizeof(struct LL*));

    if (novo != NULL)
    {
        int i;

        for (i = 0; i < tam; i++) novo[i] = NULL;
    }

    return novo;
}

struct tabela_hash* hash_criar(int tam, int maxp)
{
    if (tam < 1 || maxp < 1) return NULL;
        
    struct tabela_hash* novo = (struct tabela_hash*)malloc(sizeof(struct tabela_hash));

    if (novo == NULL) return NULL;

    novo->pesos = VetorAleatorio(maxp);

    if (novo->pesos == NULL)
    {
        free(novo);

        return NULL;
    }

    novo->v = VetorLL(tam);

    if (novo->v == NULL)
    {
        free(novo->pesos);
        free(novo);

        return NULL;
    }

    novo->tam = tam;
    novo->maxp = maxp;
    novo->ocup = 0;


    return novo;
}

void DestruirVetorLL(struct tabela_hash* t)
{
    if (t != NULL)
    {
        int i = 0, cont = 0;
        struct LL* atual = NULL;

        while (i < t->tam && cont < t->ocup)
        {
            while (t->v[i] != NULL)
            {
                atual = t->v[i];
                t->v[i] = t->v[i]->prox;

                free(atual->chave);
                free(atual);

                cont++;
            }

            i++;
        }

        free(t->v);
    }    
}

void hash_destruir(struct tabela_hash* t)
{
    if (t != NULL)
    {
        DestruirVetorLL(t);

        free(t->pesos);
        free(t);
    }
    
}

int ConverterChave(int tam, int* pesos, char* chave) //recebe tamanho máximo da chave
{
    int resultado = 0;

    if (pesos != NULL && chave != NULL)
    {
        int i;

        for (i = 0; i < tam && chave[i] != '\0'; i++)
        {
            resultado = resultado + pesos[i] * (int)chave[i];
        }
    }

    return resultado;
}

int Hash(int tam, int chave) //função hash simples (resto)
{
    return (chave % tam);
}

void ExpandirTabela(struct tabela_hash* t)
{
    struct LL** novo = NULL;

    if (t != NULL)
    {
        if ((float)t->ocup / t->tam > 0.75)
        {
            novo = VetorLL(2 * t->tam);

            if (novo != NULL)
            {
                struct LL* atual = NULL;
                int i = 0, cont = 0;

                int novaChave, indice;

                while (i < t->tam && cont < t->ocup)
                {
                    while (t->v[i] != NULL)
                    {
                        novaChave = ConverterChave(t->maxp, t->pesos, t->v[i]->chave);
                        indice = Hash(2 * t->tam, novaChave);

                        atual = novo[indice];

                        novo[indice] = t->v[i];
                        t->v[i] = t->v[i]->prox;
                        novo[indice]->prox = atual;

                        cont++;
                    }

                    i++;
                }

                free(t->v);

                t->v = novo;
                t->tam = 2 * t->tam;
            }
        }
    }
}

int hash_inserir(struct tabela_hash* t, char* chave, int dado) //retorna 1 se êxito, retorna 0 se falha
{
    int msg = 0;
    
    if (t != NULL && chave != NULL)
    {
        struct LL* novo = (struct LL*)malloc(sizeof(struct LL));

        if (novo != NULL)
        {
            int novaChave = ConverterChave(t->maxp, t->pesos, chave);
            int indice = Hash(t->tam, novaChave);

            novo->chave = strdup(chave); //novo->chave =  chave pode ser usado?

            if (novo->chave != NULL)
            {
                novo->dado = dado;

                hash_remover(t, chave);

                novo->prox = t->v[indice];
                t->v[indice] = novo;

                t->ocup++;

                ExpandirTabela(t);

                msg = 1;
            }
            else
            {
                free(novo);
            }
        }        
    }

    return msg;
}

int hash_remover(struct tabela_hash* t, char* chave)
{
    int msg = 0;

    if (t != NULL && chave != NULL)
    {
        int novaChave = ConverterChave(t->maxp, t->pesos, chave);
        int indice = Hash(t->tam, novaChave);

        struct LL *ant = NULL, *atual = t->v[indice];

        while (atual != NULL)
        {
            if (!strcmp(chave, atual->chave)) break;

            ant = atual;
            atual = atual->prox;
        }

        if (atual != NULL)
        {
            if (ant != NULL) ant->prox = atual->prox;
            else t->v[indice] = atual->prox;

            free(atual->chave);
            free(atual);

            t->ocup--;
            msg = 1;
        }
    }

    return msg;
}

int hash_buscar(struct tabela_hash* t, char* chave, int* dado)
{
    int msg = 0;

    if (t != NULL && chave != NULL && dado != NULL)
    {
        int novaChave = ConverterChave(t->maxp, t->pesos, chave);
        int indice = Hash(t->tam, novaChave);

        struct LL* atual = t->v[indice];

        while (atual != NULL)
        {
            if (!strcmp(chave, atual->chave)) break;

            atual = atual->prox;
        }

        if (atual != NULL)
        {
            *dado = atual->dado;

            msg = 1;
        }
    }

    return msg;
}
