#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include"fila.h"
#include"pilha.h"
#include"grafo.h"

/* Basea do no código obtido do curso da Prof. Vanessa Braganholo */

/*
 * Esse código assume que o grafo é íntegro (não existem arestas para nós que não existem
 */


TGrafo *grafo_inicializa(){
    return NULL;
}

void grafo_imprime(TGrafo *g){
    while(g != NULL){
        printf("Vertice %d\n", g->id_vertice);
        printf("Vizinhos: ");
        TVizinho *v = g->prim_vizinho;
        while(v != NULL){
            printf("%d ", v->id_vizinho);
            v = v->prox;
        }
        printf("\n\n");
        g = g->prox;
    }
}

void grafo_libera_vizinho(TVizinho *v){
    if(v != NULL) {
        grafo_libera_vizinho(v->prox);
        free(v);
    }
}

void grafo_libera(TGrafo *g){
    if(g != NULL){
        grafo_libera_vizinho(g->prim_vizinho);
        grafo_libera(g ->prox);
        free(g);
    }
}

TGrafo* grafo_busca_vertice(TGrafo* g, int x){
    while((g != NULL) && (g->id_vertice != x)) {
        g = g->prox;
    }
    return g;
}

TVizinho* grafo_busca_aresta(TGrafo *g, int v1, int v2){
    TGrafo *pv1 = grafo_busca_vertice(g,v1);
    TGrafo *pv2 = grafo_busca_vertice(g,v2);
    TVizinho *resp = NULL;
    //checa se ambos os vértices existem
    if((pv1 != NULL) && (pv2 != NULL)) {
        //percorre a lista de vizinhos de v1 procurando por v2
        resp = pv1->prim_vizinho;
        while ((resp != NULL) && (resp->id_vizinho != v2)) {
            resp = resp->prox;
        }
    }
    return resp;
}

TGrafo *grafo_insere_vertice(TGrafo *g, int x){
    TGrafo *p = grafo_busca_vertice(g, x);
    if(p == NULL){
        p = (TGrafo*) malloc(sizeof(TGrafo));
        p->id_vertice = x;
        p->prox = g;
        p->prim_vizinho = NULL;
        g = p;
    }
    return g;
}

void grafo_insere_um_sentido(TGrafo *g, int v1, int v2){
    TGrafo *p = grafo_busca_vertice(g, v1);
    TVizinho *nova = (TVizinho *) malloc(sizeof(TVizinho));
    nova->id_vizinho = v2;
    nova->prox = p->prim_vizinho;
    p->prim_vizinho = nova;
}

void grafo_insere_aresta(TGrafo *g, int v1, int v2){
    TVizinho *v = grafo_busca_aresta(g, v1, v2);
    if(v == NULL) {
        grafo_insere_um_sentido(g, v1, v2);
        grafo_insere_um_sentido(g, v2, v1);
    }
}

void grafo_retira_um_sentido(TGrafo *g, int v1, int v2){
    TGrafo *p = grafo_busca_vertice(g, v1);
    if(p != NULL) {
        TVizinho *ant = NULL;
        TVizinho *atual = p->prim_vizinho;
        while ((atual) && (atual->id_vizinho != v2)) {
            ant = atual;
            atual = atual->prox;
        }
        if (ant == NULL) //v2 era o primeiro nó da lista de vizinhos
            p->prim_vizinho = atual->prox;
        else
            ant->prox = atual->prox;
        free(atual);
    }
}

void grafo_retira_aresta(TGrafo *g ,int v1, int v2){
    TVizinho* v = grafo_busca_aresta(g,v1,v2);
    if(v != NULL) {
        grafo_retira_um_sentido(g, v1, v2);
        grafo_retira_um_sentido(g, v2, v1);
    }
}

TGrafo *grafo_retira_vertice(TGrafo *g, int v){
// A implementar
}

void imprimir_int(TElem x){
    int * i = (int*)x;
    printf("%d ",*i);
}

void grafo_percurso_em_largura(TGrafo *g, int x){

    //A implementar

}

void empilhar_vizinhos_pilha(TVizinho *v, TPilha *p){
    //A implementar de forma recursiva
}

void grafo_percurso_em_profundidade(TGrafo *g, int x){

    // A implementar

}

