#include<stdio.h>
#include<memory.h>
#include"fila.h"


/*
TF *TF_inicializa (void){
  TF *f = (TF *) malloc(sizeof (TF));
  f->tam = 1;
  f->vet = (int *) malloc(sizeof(int) * f->tam);
  f->n = f->ini = 0;
  return f;
}

int incr (int ind, int n){
  return (ind + 1) % n;
}


int fila_vazia (TFila *f){
  return f->n == 0;
}
*/

int incr (int ind, int n){
  return (ind + 1) % n;
}


TFila *fila_criar(int tam, size_t tam_elem){
    TFila * fila = (TFila*)malloc(sizeof(TFila));
    fila->tam = tam;
    fila->vet = calloc(fila->tam,tam_elem);
    fila->n = fila->ini = 0; 
    return fila;
}

int fila_verificar_vazia(TFila *fila){
    return (fila->n==0);
}


/*
void TF_insere (TF *f, int x){
  if(f->n == f->tam){
    int *vet = (int *) malloc(sizeof(int) * f->n * 2);
    int i = f->ini, j = 0;
    while(j < f->n){
      vet[j++] = f->vet[i];
      i = incr(i, f->tam);
    }
    f->ini = 0;
    f->tam *= 2;
    int *aux = f->vet;
    f->vet = vet;
    free(aux);
  }
  int fim = (f->ini + f->n++) % f->tam;
  f->vet[fim] = x;
}
*/

void fila_inserir(TFila *fila, TElem e, size_t tam_elem){
    if (fila->n == fila->tam){
        unsigned char * vet_dest = (unsigned char*)calloc(tam_elem * fila->n * 2, sizeof(unsigned char));
        unsigned char * vet_orig = fila->vet;

        int i = fila->ini*tam_elem, j = 0;
        while(j < fila->n*tam_elem){
            vet_dest[j++] = vet_orig[i];
            i = incr(i, fila->tam*tam_elem);
        }
        fila->ini = 0;
        fila->tam *= 2;
        TElem aux = fila->vet;
        fila->vet = (void*)vet_dest;
        free(aux);
    }
    unsigned char *v = fila->vet; //base da pilha
    int fim = (fila->ini + fila->n++) % fila->tam;
    int offset = fim*tam_elem; //o que precisamos somar para alcançar o topo
    memcpy(v+offset,e,tam_elem);

}

/*
int TF_retira (TF *f){
  if(TF_vazia(f)) exit(1);
  int resp = f->vet[f->ini];
  f->ini = incr(f->ini, f->tam);
  f->n--;
  return resp;
}

void TF_libera (TF *f){
  free(f->vet);
  free(f);
}
*/

void fila_retirar(TFila *fila, TElem e, size_t tam_elem){
    if (fila_verificar_vazia(fila)){
      printf("\nFila vazia\n");
      exit(1);
    };

    unsigned char * v = fila->vet;
    int offset = (fila->ini)*(tam_elem);
    memcpy(e,v+offset,tam_elem);
    fila->ini = incr(fila->ini,fila->tam);
    fila->n--;
}

TFila * fila_liberar(TFila *fila){
    free(fila->vet);
    free(fila);
    return NULL;
}

void fila_dump(TFila *fila, size_t tam_elem, void (*imprimir_elem)(TElem e)){
    printf("conteudo da fila:");
    for (int i = 0, j = fila->ini; i<fila->n;i++){
        
        unsigned char * vet = fila->vet;
        imprimir_elem(vet+j*tam_elem);
        j = incr(j,fila->tam);
    }
    printf("\n");
/*
    printf("memoria da  fila:");
    for (int i = 0; i<fila->tam;i++){
        
        unsigned char * vet = fila->vet;
        imprimir_elem(vet+i*tam_elem);
    }
    printf("\n");*/
}


