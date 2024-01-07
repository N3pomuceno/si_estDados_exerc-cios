#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "THeap.h"


/* 
   Esta implementacao do heap permite manipular uma lista de prioridades e dados satélites vinculados
   a cada prioridade. Os dados satélite podem ser de qualque tipo e podem ser adicionados ao heap ou nao
   Baseado no código original da Prof. Vanessa Braganholo 
*/

int pai(int i){
    return ((i-1)/2);
}

int esq(int i){
    return (i*2+1);
}

int dir(int i){
    return (i*2+2);
}

//troca os dados satelite da posicao i com j
void troca_info(unsigned char *info, int i, int j, int tam_info){
    unsigned char * temp = malloc(tam_info);

    memcpy(temp,info + i*tam_info,tam_info);
    memcpy(info + i*tam_info, info + j*tam_info,tam_info);
    memcpy(info + j*tam_info,temp,tam_info);
    free(temp);


}

void heap_descer(THeap *h, int i, int n){

    int e = esq(i);
    int d = dir(i);
    int maior = i;
    if (e<n && h->p[e] > h->p[i]) {
        maior=e;
    }
    if (d<n && h->p[d] > h->p[maior]) {
        maior=d;
    }
    if (maior != i){
        int temp = h->p[i];
        h->p[i] = h->p[maior];
        h->p[maior]=temp;

        //Se houver dado satelite faz a troca da mesma forma como o dado de prioridades
        if (h->info){
            troca_info(h->info,i,maior,h->tam_info);
        }
        heap_descer(h, maior, n);
    }
}



void heap_subir(THeap *h, int i){
    int j = pai(i);
    if (j >= 0) {
        if (h->p[i] > h->p[j]) {
            int temp = h->p[i];
            h->p[i] = h->p[j];
            h->p[j]=temp;

            //Se houver dado satelite faz a troca da mesma forma como o dado de prioridades
            if (h->info){
                troca_info(h->info,i,j,h->tam_info);
            }
            heap_subir(h, j);
        }
    }
}


THeap * heap_constroi_heap_maximo(int *p, void *info, int tam_info, int n){

    THeap * h = (THeap*)malloc(sizeof(THeap));
    h->n = n;
    h->tam = n;
    h->tam_info = tam_info;
    
    //Se existir um vetor de prioridades, faz uma copia interna no heap
    if (p){
        h->p = (int*)malloc(n*sizeof(int));
        memcpy(h->p,p,n*sizeof(int));
    }
    else{//Senao, aloca um heap vazio
        h->p = (int*)malloc(n*sizeof(int));
        memset(h->p,0,n*sizeof(int));
    }

    //Se existir um dado auxiliar, faz uma copia interna deste dado
    if (info){
        h->info = malloc(n*tam_info);
        memcpy(h->info,info,n*tam_info);
    }
    else{
        h->info = NULL;
    }

    int i;
    int j=(h->n/2);

    for(i=j;i>=0;i--)
        heap_descer(h, i, h->n);

    return h;
}



THeap * heap_liberar(THeap *h){
    free(h->p);
    if (h->info){
        free(h->info);
    }
    free(h);
}

void heap_imprime(THeap *h){
    for(int i = 0; i <= h->n-1; i++) {
        printf("%d ", h->p[i]);
    }
    printf("\n");
}

int heap_insere(THeap *h, int novo, void *info){    
    //redimensiona o array se necessario
    if (h->n==h->tam){
        h->tam *=2;
        h->p = (int *) realloc(h->p, sizeof(int) * (h->tam));
        
        if (h->info){
            h->info = (void*)realloc(h->info,h->tam_info*h->tam);
        }
    }
        
    h->p[h->n] = novo;

    //Se houver dado satelite insere o novo dado na ultima posicao (h->n)
    if (info){
        unsigned char * h_info = h->info;
        memcpy(h_info+ h->n*h->tam_info,info,h->tam_info);
    }

    h->n++;

    heap_subir(h, h->n-1);
  
    return h->n;
}


int heap_exclui(THeap *h, int *elem, void *info){
    *elem = h->p[0];
    h->p[0] = h->p[h->n-1];

    //Se houver dado satelite copia o dado da posicao zero de h->info para info
    //E copia o dadona ultima posicao para a primeira (posicao 0)
    if (h->info){
        unsigned char *h_info = (unsigned char*)h->info;
        memcpy(info,h_info,h->tam_info);
        memcpy(h_info,h_info + (h->n-1)*h->tam_info,h->tam_info);
    }

    h->n--;
  
    heap_descer(h, 0, h->n);
  
    return h->n;
}


void heap_sort(int *v, void *info, int tam_info, int n){

    int i;
    int j=n;

    THeap * h = heap_constroi_heap_maximo(v,info,tam_info,n);

    for(i=h->n-1;i>0;i--){
        //troca o ultimo  elemento (posicao i) com o primeiro
        int temp = h->p[i];
        h->p[i]=h->p[0];
        h->p[0]=temp;

        //Se houver dado satelite move o dado da posicao 0 para a posicao i (a posicao do elemento ordenado)
        if (h->info){
        
            troca_info(h->info,i,0,h->tam_info);
        }

        //reduz o tamanho do vetor a ser ordenado pois mais um elemento foi colocado na posicao correta
        j--;
        //corrige o elemento na raiz fazendo a descida se necessario
        heap_descer(h, 0, j);

    }

    if (v){
        memcpy(v,h->p,h->n*sizeof(int));
    }

    if (info){
        memcpy(info,h->info,h->n*h->tam_info);
    }

    heap_liberar(h);
}


