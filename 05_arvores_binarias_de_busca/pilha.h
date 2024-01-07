#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED
#include<stdlib.h>


// Baseado no codigo de Introdução a Estruturas de Dados - programacão em C
// Waldemar Celes, Renato Cerqueira e José Lucas Rangel
// Elsevier 2a Edição


typedef char TElem;

typedef struct pilha{int dim;
                     TElem *p;
                     int n;
                     }TPilha;

TPilha *pilha_criar(int dim);

int pilha_verificar_vazia(TPilha *pilha);

void pilha_empilhar(TPilha *pilha, TElem e);

TElem pilha_desempilhar(TPilha *pilha);

TPilha *pilha_liberar(TPilha *pilha);

void pilha_dump(TPilha *pilha);

#endif // PILHA_H_INCLUDED

