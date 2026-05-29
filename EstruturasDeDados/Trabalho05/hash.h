#ifndef HASH_H
#define HASH_H


struct LL {
    char* chave;
    int dado;
    struct LL* prox;
};

struct tabela_hash {
    struct LL** v; // vetor interno
    int* pesos; // vetor de pesos aleatórios para função hash
    int tam; // tamanho do vetor interno
    int maxp;
    int ocup;
};

struct tabela_hash* hash_criar(int tam, int maxp);
void hash_destruir(struct tabela_hash* t);
int hash_inserir(struct tabela_hash* t, char* chave, int dado);
int hash_remover(struct tabela_hash* t, char* chave);
int hash_buscar(struct tabela_hash* t, char* chave, int* dado);


#endif