#include<stdio.h>
#include<stdlib.h>
#include"grafo.h"
#include"pilha.h"
#include"fila.h"

/*

     1-------------2
    / \           /|\       
   /    \       /  | \      
  /       \   /    |  \       
 4----------7------|---3-------8
  \       /   \    |  /     .´
   \    /       \  | /   .´ 
    \ /           \|/ .´
     5-------------6´

*/

int main(){
    TGrafo *g = grafo_inicializa();
    g = grafo_insere_vertice(g, 1);
    g = grafo_insere_vertice(g, 2);
    g = grafo_insere_vertice(g, 3);
    g = grafo_insere_vertice(g, 4);
    g = grafo_insere_vertice(g, 5);
    g = grafo_insere_vertice(g, 6);
    g = grafo_insere_vertice(g, 7);
    g = grafo_insere_vertice(g, 8);

    grafo_insere_aresta(g, 1, 2);
    grafo_insere_aresta(g, 1, 7);
    grafo_insere_aresta(g, 1, 4);
    grafo_insere_aresta(g, 2, 3);
    grafo_insere_aresta(g, 2, 6);
    grafo_insere_aresta(g, 2, 7);
    grafo_insere_aresta(g, 3, 6);
    grafo_insere_aresta(g, 3, 7);
    grafo_insere_aresta(g, 3, 8);
    grafo_insere_aresta(g, 4, 7);
    grafo_insere_aresta(g, 4, 5);
    grafo_insere_aresta(g, 5, 7);
    grafo_insere_aresta(g, 5, 6);
    grafo_insere_aresta(g, 6, 7);
    grafo_insere_aresta(g, 6, 8);
    
    grafo_imprime(g);

    grafo_percurso_em_largura(g, 1);

    grafo_percurso_em_profundidade(g, 1);

/*
    grafo_retira_aresta(g, 3, 2);
    printf("Grafo apos exclusao da aresta (3,2): \n\n");
    grafo_imprime(g);
    grafo_retira_vertice(g,2);
    printf("Grafo apos exclusao do vertice 2: \n\n");
    grafo_imprime(g);
    grafo_libera(g);
*/


}