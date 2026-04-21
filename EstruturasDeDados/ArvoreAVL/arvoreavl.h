#ifndef ARVOREAVL_H
#define ARVOREAVL_H

struct NoAVL
{
    int chave;
    char* nome;
    int FB;
    struct NoAVL* fesq;
    struct NoAVL* fdir;
};

struct NoAVL* inserirAVL(struct NoAVL* arv, int chave, char* nome);
struct NoAVL* removerAVL(struct NoAVL* arv, int chave, char** nome);

#endif
