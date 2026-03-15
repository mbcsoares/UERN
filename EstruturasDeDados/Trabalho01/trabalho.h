#ifndef trabalho_h
#define trabalho_h

struct No
{
	int mat;
	char* nome;
	struct No* ant;
	struct No* prox;
};

struct No* inserir(struct No* lista, int mat, char* nome);
struct No* remover(struct No* lista, int mat);
struct No* buscarMatricula(struct No* lista, int mat);
struct No* buscarNome(struct No* lista, char* nome);
int tamanho(struct No* lista);

#endif
