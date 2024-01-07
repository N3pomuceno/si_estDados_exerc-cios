#include <stdlib.h>
#include <stdio.h>

/* Basea do no código obtido do curso da Prof. Vanessa Braganholo */

/*
 * Esse código assume que o grafo é íntegro (não existem arestas para nós que não existem
 */

typedef struct vizinho {
    int id_vizinho;
    struct vizinho *prox;
}TVizinho;

typedef struct grafo{
    int id_vertice;
    TVizinho *prim_vizinho;
    struct grafo *prox;
}TGrafo;

TGrafo *grafo_inicializa();

void grafo_imprime(TGrafo *g);

void grafo_libera_vizinho(TVizinho *v);

void grafo_libera(TGrafo *g);

TGrafo* grafo_busca_vertice(TGrafo* g, int x);

TVizinho* grafo_busca_aresta(TGrafo *g, int v1, int v2);

TGrafo *grafo_insere_vertice(TGrafo *g, int x);

void grafo_insere_um_sentido(TGrafo *g, int v1, int v2);

void grafo_insere_aresta(TGrafo *g, int v1, int v2);

void grafo_retira_um_sentido(TGrafo *g, int v1, int v2);

void grafo_retira_aresta(TGrafo *g ,int v1, int v2);

TGrafo *grafo_retira_vertice(TGrafo *g, int v);

void grafo_percurso_em_largura(TGrafo *g, int x);

void grafo_percurso_em_profundidade(TGrafo *g, int x);
