#ifndef ARVBIN_H
#define ARVBIN_H


typedef struct no_arvbin{int chave;
                       struct no_arvbin * fe;
                       struct no_arvbin * fd;}TArvBin;

TArvBin * arvbin_criar_vazia();
TArvBin * arvbin_criar(int chave, TArvBin * fe, TArvBin * fd);
int arvbin_vazia(TArvBin * raiz);
TArvBin * arvbin_desalocar(TArvBin *raiz);
TArvBin * arvbin_buscar(TArvBin *raiz, int chave);
int arvbin_altura(TArvBin * raiz);
void arvbin_imprimir(TArvBin *raiz);
void arvbin_pre_ordem(TArvBin *raiz);
void arvbin_ordem_simetrica(TArvBin *raiz);
void arvbin_pos_ordem(TArvBin *raiz);

#endif 
