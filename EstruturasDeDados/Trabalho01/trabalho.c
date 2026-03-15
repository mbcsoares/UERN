#include <stdlib.h>
#include <stdio.h>
#include "trabalho.h"

//========= FUNÇÕES AUXILIARES ==========//

char CoverterParaMaiusculo(char c)
{
	if(c >= 'a' && c <= 'z') return c - 32;
	else return c;
}

int LetraValida(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int OrdemAlfabeticaDesc(char* palavraA, char* palavraB)
{
	int i;
	char cA = '\0';
	char cB = '\0';
	
	for(i = 0; palavraA[i] != '\0' && palavraB[i] != '\0'; i++)
	{
		if(LetraValida(palavraA[i]) && LetraValida(palavraB[i]))
		{
			cA = CoverterParaMaiusculo(palavraA[i]);
			cB = CoverterParaMaiusculo(palavraB[i]);
			
			if(cA != cB) break;
		}
	}
	
	return cA > cB;
}

char* CopiarPalavra(char* palavra)
{
	char* temp;
		
	if(palavra != NULL)
	{
		int i = 0, j = 0;
		
		while(palavra[i] != '\0') i++;
		
		temp = (char*)malloc(i * sizeof(char));
		
		if(temp == NULL) return NULL;
		
		while(j <= i)
		{
			temp[j] = palavra[j];
			j++;
		}
	}
	else return NULL;
	
	return temp;
}

int PalavrasIguais(char* palavraA, char* palavraB)
{
	int i = 0;
	char cA, cB;

	do
	{
		cA = CoverterParaMaiusculo(palavraA[i]);
		cB = CoverterParaMaiusculo(palavraB[i]);

		if (palavraA[i] == '\0' || palavraB[i] == '\0') break;

		i++;

	} while (cA == cB);

	return cA == cB;
}

void ImprimirLista(struct No* lista)
{
	while (lista != NULL)
	{
		printf("Nome: %s\n", lista->nome);
		printf("Matrícula: %d\n", lista->mat);
		printf("\n");

		lista = lista->prox;
	}
}

void LimparLista(struct No* lista)
{
	struct No* temp;

	while (lista != NULL)
	{
		temp = lista->prox;
		free(lista);
		lista = temp;
	}
}

//=====================================//

//========== FUNÇÕES PRINCIPAIS =========//

struct No* inserir(struct No* lista, int mat, char* nome)
{
	struct No* temp = lista;
	struct No* novo = (struct No*)malloc(sizeof(struct No));
	
	novo->nome = nome;
	novo->mat = mat;
	novo->prox = NULL;
	novo->ant = NULL;
	
	//Primeiro elemento NULL (lista vazia)
	
	if(temp == NULL)
	{
	    return novo;
	}
	
	while(temp != NULL)
	{
	    if(OrdemAlfabeticaDesc(nome, temp->nome))
		{
			novo->prox = temp;
			novo->ant = temp->ant;
			
			if(temp->ant != NULL) temp->ant->prox = novo;
			else lista = novo;
			
			temp->ant = novo;
			
			break;
		}
		else if(temp->prox == NULL)
		{
		    temp->prox = novo;
		    novo->ant = temp;
		    
		    break;
		}
		
		temp = temp->prox;
	}
	
	return lista;
}

struct No* remover(struct No* lista, int mat)
{
	struct No* temp = lista;
	
	while(temp != NULL)
	{
		if(temp->mat == mat)
		{
			if(temp->ant == NULL && temp->prox == NULL)
			{
				lista = NULL;
			}
			else if(temp->ant == NULL)
			{
				temp->prox->ant = temp->ant;
				lista = temp->prox;
			}
			else if(temp->prox == NULL)
			{
				temp->ant->prox = temp->prox;
			}
			else
			{
				temp->prox->ant = temp->ant;
				temp->ant->prox = temp->prox;
			}
						
			free(temp);
			break;
		}
		
		temp = temp->prox;
	}

	if (temp == NULL) return NULL;
	else return lista;
}


struct No* buscarMatricula(struct No* lista, int mat)
{
	while (lista != NULL)
	{
		if (lista->mat == mat) break;

		lista = lista->prox;
	}

	return lista;
}


struct No* buscarNome(struct No* lista, char* nome)
{
	while (lista != NULL)
	{
		if(PalavrasIguais(lista->nome, nome)) break;

		lista = lista->prox;
	}

	return lista;
}

int tamanho(struct No* lista)
{
	int cont = 0;

	while (lista != NULL)
	{
		cont++;
		lista = lista->prox;
	}

	return cont;
}
