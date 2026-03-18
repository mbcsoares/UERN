#ifndef pilha_h
#define pilha_h


struct No
{
    char *nome;
    struct No *prox;
};


struct No *push(struct No *pilha, char *nome);
struct No *pop(struct No *pilha, char **nome);
int tamanho(struct No *pilha);
int imprimir(struct No *pilha);
void destruir(struct No *pilha);

#endif
