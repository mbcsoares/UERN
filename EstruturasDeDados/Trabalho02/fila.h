#ifndef fila_h
#define fila_h


struct No {
	char* nome;
	struct No* prox;
};

struct No* inserir(struct No* fila, char* nome);
struct No* remover(struct No* fila, char** nome);
int tamanho(struct No* fila);
void imprimir(struct No* fila);
void destruir(struct No* fila);


#endif