#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "THeap.h"


int main(void){
    int *vet = (int *)malloc(sizeof(int)*10);
    vet[0] = 1;
    vet[1] = 45;
    vet[2] = 23;
    vet[3] = 12;
    vet[4] = 34;
    vet[5] = 78;
    vet[6] = 11;
    vet[7] = 9;
    vet[8] = 32;
    vet[9] = 10;
    
    char (*info)[10] = (char(*)[10])malloc(10*sizeof(char[10]));


    strcpy(info[0],"proc 0");
    strcpy(info[1],"proc 1");
    strcpy(info[2],"proc 2");
    strcpy(info[3],"proc 3");
    strcpy(info[4],"proc 4");
    strcpy(info[5],"proc 5");
    strcpy(info[6],"proc 6");
    strcpy(info[7],"proc 7");
    strcpy(info[8],"proc 8");
    strcpy(info[9],"proc 9");

    //Constroi um heap apenas com um array de prioridades dadas por numeros inteiros
    THeap * h = heap_constroi_heap_maximo(vet,NULL,0,10);
    heap_imprime(h);

    int pos = 1;
    printf("Diminuir a prioridade do elemento na posicao %d de %d para %d\n",pos,h->p[pos],h->p[pos]/2);
    h->p[pos] = h->p[pos]/2; 
    heap_descer(h,pos,h->n);
    heap_imprime(h);


    pos = 8;
    printf("Aumentar a prioridade do elemento na posicao %d de %d para %d\n",pos,h->p[pos],h->p[pos]*10);
    h->p[pos] = h->p[pos]*10; 
    heap_subir(h,pos);
    heap_imprime(h);

   
    int elem = 82;
    printf("Inserir o elemento %d\n",elem);
    heap_insere(h,elem,NULL);    
    heap_imprime(h);


    printf("Remover o elemento de maior prioridade\n");
    heap_exclui(h,&elem,NULL);    
    printf("Elem = %d\n",elem);
    heap_imprime(h);

    heap_liberar(h);


    printf("Ordenar vetor\n");


    vet[0] = 9;
    vet[1] = 6;
    vet[2] = 1;
    vet[3] = 2;
    vet[4] = 4;
    vet[5] = 7;
    vet[6] = 8;
    vet[7] = 3;
    vet[8] = 5;
    vet[9] = 0;

    printf("Original:\n");

    for (int i=0;i<10;i++)
        printf("%d ",vet[i]);
    printf("\n");

    //Ordena o vetor e os dados satelites (as strings indicando o numero do processo)
    heap_sort(vet,info,sizeof(char[10]),10);

    printf("Ordenado:\n");
    
    for (int i=0;i<10;i++)
        printf("%d ",vet[i]);
    printf("\n");


    for (int i = 0;i<10;i++){
        printf("%s\n",info[i]);
    }



    free(vet);
    free(info);

}
