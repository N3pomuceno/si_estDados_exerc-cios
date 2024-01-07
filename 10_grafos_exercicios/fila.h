#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include<stdlib.h>

/*
typedef struct fila{
  int n, ini, tam;
  int *vet;
}TF;

void TF_insere(TF *f, int elem);
int TF_vazia(TF *f);
void TF_libera(TF *f);
TF *TF_inicializa(void);
int TF_retira(TF *f);
void TF_imprime(TF *f);
*/

// Baseado no codigo de Introdução a Estruturas de Dados - programacão em C
// Waldemar Celes, Renato Cerqueira e José Lucas Rangel
// Elsevier 2a Edição


typedef void* TElem;

typedef struct fila{int tam; //tam
                    int n; //n elementos
                    int ini; //ini fila
                    TElem vet; // vet é um array implementado como void *vet

                    }TFila;

TFila *fila_criar(int tam, size_t tam_elem);

int fila_verificar_vazia(TFila *fila);

void fila_inserir(TFila *fila, TElem e, size_t tam_elem);

void fila_retirar(TFila *fila, TElem e, size_t tam_elem);

TFila *fila_liberar(TFila *fila);

void fila_dump(TFila *fila, size_t tam_elem, void (imprimir_elem)(TElem e));

#endif // PILHA_H_INCLUDED

