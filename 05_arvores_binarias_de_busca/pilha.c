#include<stdio.h>
#include"pilha.h"

TPilha *pilha_criar(int dim){
    TPilha * pilha = (TPilha*)malloc(sizeof(TPilha));
    pilha->dim = dim;
    pilha->n=0;
    pilha->p = (TElem*)malloc(pilha->dim*sizeof(TElem));
 
    return pilha;
}

int pilha_verificar_vazia(TPilha *pilha){
    return (pilha->n==0);
}

void pilha_empilhar(TPilha *pilha, TElem e){
    if (pilha->n == pilha->dim){
        pilha->dim *=2;
        pilha->p = (TElem*)realloc(pilha->p, pilha->dim*sizeof(TElem));
    }
    pilha->p[pilha->n++] = e;
}

TElem pilha_desempilhar(TPilha *pilha){
   
    return   pilha->p[--pilha->n];
}

TPilha * pilha_liberar(TPilha *pilha){
    free(pilha->p);
    free(pilha);
    return NULL;
}

void pilha_dump(TPilha *pilha){
    for (int i = 0; i<pilha->n;i++){
        printf("%c",pilha->p[i]);
    }
}


