#ifndef pilha_h
#define pilha_h

typedef struct Pilha
{
	int dado;
	struct Pilha *prox;	
} Pilha;

Pilha *Inserir(Pilha *pilha, int dado);
Pilha *Remover(Pilha *pilha);
void Consultar(Pilha *pilha);
void Esvaziar(Pilha *pilha);

#endif
