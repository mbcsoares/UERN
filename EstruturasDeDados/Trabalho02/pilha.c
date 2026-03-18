#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

/* Lista encadeada PILHA
Rafael Manna e Micael Bruno
*/

/*
Push: Insere um nome na pilha.
A função retorna um ponteiro para a pilha atualizada. 
  struct No *push(struct No *pilha, char *nome);
*/
struct No *push(struct No *pilha, char *nome)
{
    struct No *novo = (struct No*) malloc(sizeof(struct No));
    
    if (novo == NULL || nome == NULL) return pilha;
    
    novo->nome = strdup(nome); // cópia da string
    novo->prox = pilha;
    
    return novo;
}

/*
Pop: Remove um elemento da pilha. O nome removido da pilha deve ser retornado pelo 
parâmetro nome. Caso não seja possível remover um elemento da pilha, o valor NULL é 
retornado através do parâmetro nome. A função retorna um ponteiro para a pilha 
atualizada. Cabe ao usuário da biblioteca liberar a memória utilizada pelo nome retornado. 
  struct No *pop(struct No *pilha, char **nome);
*/
struct No *pop(struct No *pilha, char **nome)
{
	if (nome == NULL) return pilha;
    if (pilha == NULL)
	{
        *nome = NULL;
        return pilha;
    }
    
    struct No *aux = pilha;
    
    *nome = aux->nome;    
    pilha = aux->prox;
    
    free(aux);
    
    return pilha;
}

/*
Tamanho: Retorna a quantidade atual de elementos contidos na pilha. 
int tamanho(struct No *pilha); 
*/
int tamanho(struct No *pilha)
{
    int i = 0;
    
    while (pilha != NULL)
	{
        pilha = pilha->prox;
        i++;
    }
    
    return i;
}

/*
Imprimir: Imprime os elementos da pilha começando do topo da pilha e terminando da 
base da pilha. 
int imprimir(struct No *pilha);
*/
int imprimir(struct No *pilha) {
    if (pilha == NULL) {
        printf("LISTA VAZIA\n");
        return 0;
    }

    struct No *atual = pilha;
    int i = 1;

    while (atual != NULL) {
        printf("%d. Nome: %s\n", i, atual->nome);
        atual = atual->prox;
        i++;
    }
    return 1;
}

/*
Destruir: Destrói a pilha passada por parâmetro liberando a memória alocada. 
void destruir(struct No *pilha);
*/
void destruir(struct No *pilha)
{
    struct No *proximo = NULL;
    
    while (pilha != NULL)
	{
        proximo = pilha->prox;
        
        free(pilha->nome); // libera a string
        free(pilha);       // libera o nó
        
        pilha = proximo;
    }
}

/* Programa principal para teste */

