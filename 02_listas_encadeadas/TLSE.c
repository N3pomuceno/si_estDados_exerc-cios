#include <stdio.h>
#include <stdlib.h>

typedef struct lse{
    int info;
    struct lse *prox;
} TLSE;

//Cria lista vazia
TLSE* inicializa(void);

//Insere no início
TLSE* ins_ini(TLSE *l, int x);

//Imprime a lista
void imprime(TLSE *l);

//Busca primeira vez de x
TLSE* busca(TLSE *l, int x);

//Liberação da lista
void libera(TLSE *l);

//Retira a primeira vez de x
TLSE* retira(TLSE *l, int x);

//Inserção ordenada de x
TLSE* ins_ord(TLSE *l, int x);


TLSE* inicializa(void){
    return NULL;
}

TLSE* ins_ini(TLSE *l, int x){
    TLSE * novo = (TLSE*)malloc(sizeof(TLSE));
    novo->info = x;
    novo->prox = l;
    return novo;
}

void imprime(TLSE *l){
    printf("[ ");
    while (l!=NULL){
        printf("[%2d|  ]->",l->info);
        l=l->prox;
    }
    printf(" NULL ]\n");
}


//Busca primeira vez de x
TLSE* busca(TLSE *l, int x){
    TLSE *resp = l;

    while ((resp)&&(resp->info!=x)){
        resp = resp->prox;
    }

    return resp;

}

TLSE* retira(TLSE *l, int x){
    TLSE * ant = NULL, *p = l;


    while ((p!=NULL)&&(p->info<x)){
        ant = p;
        p = p->prox;
    }

    if (!p) return l;
    if(!ant){
        l = l->prox;
    }
    else{
        ant->prox = p->prox;
    }

    free(p);

    return l;   
}

void libera(TLSE*l){
    TLSE * p;
    while (l!=NULL){
        p = l;
        l = l->prox;
        free(p);
    }
}

TLSE* ins_ord(TLSE *l, int x){
    
    TLSE * novo, *ant = NULL, *p = l;
    
    novo = (TLSE*)malloc(sizeof(TLSE));
    novo->info = x;

    while ((p!=NULL)&&(p->info<x)){
        ant = p;
        p = p->prox;
    }

    if (!ant){
        novo->prox = l;
        l = novo;
    }
    else{
        //Atencao a ordem
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return l;
}

int main(){
    TLSE *l = inicializa();
    l = ins_ini(l, 9);
    l = ins_ini(l, 7);
    l = ins_ini(l, 5);
    l = ins_ini(l, 3);
    l = ins_ini(l, 2);
    l = ins_ini(l, 1);

    l = ins_ord(l, 6);
    l = ins_ord(l, 0);
    l = ins_ord(l, 10);
    l = ins_ord(l, 4);

    imprime(l);
    

    l = retira(l, 2);
    l = retira(l, 0);
    l = retira(l, 10);

    imprime(l);


    //...
    //Antes de terminar a execução
    libera(l);
    return 0;
}
