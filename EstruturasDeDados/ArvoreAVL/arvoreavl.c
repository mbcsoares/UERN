#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreavl.h"

int Modulo(int num)
{
    if (num < 0) return (-1 * num);

    return num;
}

int Maximo(int a, int b)
{
    if (a > b) return a;

    return b;
}

int Minimo(int a, int b)
{
    if (a < b) return a;

    return b;
}

void imprimir(struct NoAVL* arv)
{
    printf("(");

    if (arv != NULL)
    {
        printf(" %d - %s", arv->chave, arv->nome);

        imprimir(arv->fesq);
        imprimir(arv->fdir);
    }

    printf(")");
}

void imprimirFB(struct NoAVL* arv)
{
    printf("(");

    if (arv != NULL)
    {
        printf(" %d - [ %d ]", arv->chave, arv->FB);

        imprimirFB(arv->fesq);
        imprimirFB(arv->fdir);
    }

    printf(")");
}

struct NoAVL* atribuir(int chave, char* nome)
{
    struct NoAVL* novo = NULL;

    if (nome != NULL)
    {
        novo = (struct NoAVL*)malloc(sizeof(struct NoAVL));

        if (novo != NULL)
        {
            novo->FB = 0;

            novo->fesq = NULL;
            novo->fdir = NULL;

            novo->chave = chave;

            novo->nome = (char*)malloc((strlen(nome) + 1) * sizeof(char));

            if (novo->nome != NULL)
            {
                strcpy(novo->nome, nome);
            }
            else
            {
                free(novo);
                novo = NULL;
            }
        }
    }

    return novo;
}

struct NoAVL* RotacaoEsquerda(struct NoAVL* arv) //O pai se torna o filho esquerdo do filho direito
{
    struct NoAVL* filho = NULL;

    if (arv != NULL)
    {
        if (arv->fdir != NULL)
        {
            filho = arv->fdir;

            arv->fdir = filho->fesq;
            filho->fesq = arv;

            arv->FB = arv->FB + 1 - Minimo(filho->FB, 0);
            filho->FB = filho->FB + 1 + Maximo(arv->FB, 0);

            arv = filho;
        }
    }

    return arv;
}

struct NoAVL* RotacaoDireita(struct NoAVL* arv) //O pai se torna o filho direito do filho esquerdo
{
    struct NoAVL* filho = NULL;

    if (arv != NULL)
    {
        if (arv->fesq != NULL)
        {
            filho = arv->fesq;

            arv->fesq = filho->fdir;
            filho->fdir = arv;

            arv->FB = arv->FB - 1 - Maximo(filho->FB, 0);
            filho->FB = filho->FB - 1 + Minimo(arv->FB, 0);

            arv = filho;
        }
    }

    return arv;
}

struct NoAVL* Balancear(struct NoAVL* arv)
{
    if (arv != NULL)
    {
        if (arv->FB < -1) //Rotacionar a direita
        {
            if (arv->fdir->FB > 0) //Caso necesite de rotação dupla - Se o filho da direita está pendendo para a esquerda
            {
                arv->fdir = RotacaoDireita(arv->fdir);
            }

            arv = RotacaoEsquerda(arv);
        }
        else if (arv->FB > 1) //Rotacionar a esquerda
        {
            //printf("%s esteve aqui\n", arv->nome);

            if (arv->fesq->FB < 0) //Caso necessite de rotação dupla - Se o filho da esquerda está pendendo para a direita
            {
                arv->fesq = RotacaoEsquerda(arv->fesq);
            }

            arv = RotacaoDireita(arv);
        }
    }

    return arv;
}

struct NoAVL* inserirAVL(struct NoAVL* arv, int chave, char* nome)
{
    if (arv == NULL)
    {
        arv = atribuir(chave, nome);
    }
    else if (chave != arv->chave)
    {
        int fbAnt;

        if (arv->chave < chave)
        {
            if (arv->fdir == NULL)
            {
                arv->FB--;
                arv->fdir = inserirAVL(arv->fdir, chave, nome);
            }
            else
            {
                fbAnt = arv->fdir->FB;

                arv->fdir = inserirAVL(arv->fdir, chave, nome);

                if ((Modulo(arv->fdir->FB) - Modulo(fbAnt)) > 0)
                {
                    arv->FB--;
                }
            }

        }
        else if (arv->chave > chave)
        {
            if (arv->fesq == NULL)
            {
                arv->FB++;
                arv->fesq = inserirAVL(arv->fesq, chave, nome);

                //printf("%s esteve aqui\n", arv->nome);
            }
            else
            {
                fbAnt = arv->fesq->FB;

                arv->fesq = inserirAVL(arv->fesq, chave, nome);

                if ((Modulo(arv->fesq->FB) - Modulo(fbAnt)) > 0)
                {
                    arv->FB++;
                }
            }
        }

        arv = Balancear(arv);
    }

    return arv;
}

struct NoAVL* removerAVL(struct NoAVL* arv, int chave, char** nome)
{

    if (arv != NULL)
    {
        int fbAnt;

        if (arv->chave == chave)
        {
            struct NoAVL* temp = NULL;
            struct NoAVL* tempAnt = arv;

            *nome = arv->nome;

            if (arv->fdir != NULL)
            {
                temp = arv->fdir;

                while (temp->fesq != NULL)
                {
                    tempAnt = temp;
                    temp = temp->fesq;
                }

                arv->chave = temp->chave;
                arv->nome = temp->nome;

                if (temp == tempAnt->fdir)
                {
                    tempAnt->fdir = temp->fdir;
                    tempAnt->FB++;
                }
                else
                {
                    tempAnt->fesq = temp->fdir;
                    tempAnt->FB--;
                }

                free(temp);
            }
            else
            {
                temp = arv->fesq;
                free(arv);
                arv = temp;
            }
        }
        else if (arv->chave < chave && arv->fdir != NULL)
        {
            fbAnt = arv->fdir->FB;

            arv->fdir = removerAVL(arv->fdir, chave, nome);

            if (arv->fdir == NULL)
            {
                arv->FB++;
            }
            else if ((Modulo(arv->fdir->FB) - Modulo(fbAnt)) < 0)
            {
                arv->FB++;
            }
        }
        else if (arv->chave > chave && arv->fesq != NULL)
        {
            fbAnt = arv->fesq->FB;

            arv->fesq = removerAVL(arv->fesq, chave, nome);

            if (arv->fesq == NULL)
            {
                arv->FB--;
            }
            else if ((Modulo(arv->fesq->FB) - Modulo(fbAnt)) < 0)
            {
                arv->FB--;
            }
        }

        arv = Balancear(arv);
    }

    return arv;
}


/*struct NoAVL* removerAVL(struct NoAVL* arv, int chave, char** nome)
{

    if (arv != NULL && nome != NULL)
    {
        int fbAnt;

        if (arv->chave == chave)
        {                        
            if (arv->fdir != NULL || arv->fesq != NULL)
            {
                struct NoAVL* temp = arv;
                struct NoAVL* tempAnt = arv;

                if(arv->fdir != NULL) arv = arv->fdir;
                else arv = arv->fesq;

                while (temp->fdir != NULL || temp->fesq != NULL)
                {
                    if (temp->fdir != NULL)
                    {
                        tempAnt->fdir = temp->fdir;
                        tempAnt = RotacaoEsquerda(temp);                        
                    }
                    
                    if (temp->fesq != NULL)
                    {
                        tempAnt->fesq = temp->fesq;
                        tempAnt = RotacaoDireita(temp);                        
                    }
                }

                removerAVL(arv, chave, nome);
            }
            else
            {
                *nome = (char*)malloc(sizeof(char) * (strlen(arv->nome) + 1));
                strcpy(*nome, arv->nome);

                free(arv->nome);
                free(arv);
                arv = NULL;
            }
        }
        else if (arv->chave < chave && arv->fdir != NULL)
        {
            fbAnt = arv->fdir->FB;

            arv->fdir = removerAVL(arv->fdir, chave, nome);

            if (arv->fdir == NULL)
            {
                arv->FB++;
            }
            else if ((Modulo(arv->fdir->FB) - Modulo(fbAnt)) > 0)
            {
                arv->FB++;
            }
        }
        else if (arv->chave > chave && arv->fesq != NULL)
        {
            fbAnt = arv->fesq->FB;

            arv->fesq = removerAVL(arv->fesq, chave, nome);

            if (arv->fesq == NULL)
            {
                arv->FB--;
            }
            else if ((Modulo(arv->fesq->FB) - Modulo(fbAnt)) > 0)
            {
                arv->FB--;
            }
        }

        //arv = Balancear(arv);
    }

    return arv;
}*/


