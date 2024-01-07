#ifndef ABB_H
#define ABB_H


typedef struct no_abb{int chave;
                       struct no_abb * fe;
                       struct no_abb * fd;}TABB;

TABB * abb_criar_vazia();
TABB * abb_criar_chaves(int * chaves, int ini, int fim);
int abb_vazia(TABB * raiz);
TABB * abb_desalocar(TABB *raiz);
int abb_altura(TABB * raiz);
void abb_imprimir(TABB *raiz);

TABB * abb_inserir(TABB * raiz, int chave);
TABB * abb_inserir_rec(TABB * raiz, int chave);
TABB * abb_buscar(TABB *raiz, int chave);
TABB * abb_encontrar_filho_mais_a_direita(TABB *raiz);
TABB * abb_remover(TABB *raiz, int chave);
TABB * abb_sucessor(TABB * raiz, int chave);


#endif 