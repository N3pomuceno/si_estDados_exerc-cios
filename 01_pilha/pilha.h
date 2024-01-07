#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED
#include<stdlib.h>


// Baseado no codigo de Introdução a Estruturas de Dados - programacão em C
// Waldemar Celes, Renato Cerqueira e José Lucas Rangel
// Elsevier 2a Edição


typedef void* TElem;

typedef struct pilha{int dim; //tam
                     TElem p; // p é um array implementado como void *p
                     int n; //topo
                    }TPilha;

TPilha *pilha_criar(int dim, size_t tam_elem);

int pilha_verificar_vazia(TPilha *pilha);

void pilha_empilhar(TPilha *pilha, TElem e, size_t tam_elem);

void pilha_desempilhar(TPilha *pilha, TElem e, size_t tam_elem);

TPilha *pilha_liberar(TPilha *pilha);

void pilha_dump(TPilha *pilha, size_t tam_elem, void (imprimir_elem)(TElem e));

#endif // PILHA_H_INCLUDED

