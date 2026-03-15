#ifndef fila_h
#define fila_h

typedef struct No
{
	int dado;
	struct No* prox;
} No;

typedef struct Fila
{
	struct No *inicio;
	struct No *fim;
} Fila;

typedef struct FilaVetor
{
	int* vetor;
	int capacidade;
	int limInferior;
	int limSuperior;

	int quantidade;
	int inicio;
	int fim;
	
} FilaVetor;

void Inserir(Fila* fila, int dado);
void Remover(Fila* fila);
void Consultar(Fila* fila);
void Esvaziar(Fila* fila);

void FVCriar(FilaVetor* fila, int capacidade);
void FVInserir(FilaVetor* fila, int dado);
void FVRemover(FilaVetor* fila);
void FVConcultar(FilaVetor* fila);
void FVEsvaziar(FilaVetor* fila);

#endif
