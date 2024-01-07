#include<stdio.h>
#include<stdlib.h>
#include"abb.h"


TABB * abb_criar_vazia(){
    return NULL;
}

TABB * abb_criar(int chave, TABB * fe, TABB * fd){
    TABB * novo_no;
    novo_no = (TABB*)malloc(sizeof(TABB));
    novo_no->chave = chave;
    novo_no->fe = fe;
    novo_no->fd = fd;

    return novo_no;
}


TABB* abb_criar_chaves(int *chaves,int ini, int fim){
    TABB* raiz = NULL;

    if (ini<=fim){
        int meio = (ini+fim)/2;
        int chave = chaves[meio];
        raiz = abb_inserir(raiz,chave);
        raiz->fe = abb_criar_chaves(chaves,ini,meio-1);
        raiz->fd = abb_criar_chaves(chaves,meio+1,fim);
    }
    return raiz;
}

int abb_vazia(TABB * raiz){
    return raiz == NULL;
}

TABB * abb_desalocar(TABB *raiz){
    if (!abb_vazia(raiz)){
        raiz->fe = abb_desalocar(raiz->fe);
        raiz->fd = abb_desalocar(raiz->fd);
        free(raiz);
    }
    return NULL;
}

int abb_altura(TABB * raiz){
    int alt1,alt2;
    if (abb_vazia(raiz))
        return 0;
    else{
        alt1 = abb_altura(raiz->fe);
        alt2 = abb_altura(raiz->fd);
        if (alt1>alt2)
            return alt1+1;
        else
            return alt2+1;
    }
}

void _abb_imprimir(TABB *raiz,int profundidade, int direita){
    int i;
    if (!abb_vazia(raiz)){
            if (direita){
                printf("------>");
            }
            else{
                for (i=0;i<profundidade;i++){
                    printf(" |         ");
                }
            }
            printf("(%2.d)",raiz->chave);
            _abb_imprimir(raiz->fd,profundidade+1,1);
            for (i=0;i<profundidade+1;i++){
                printf(" |         ");
            }
            printf("\n");
            for (i=0;i<profundidade+1;i++){
                printf(" |         ");
            }
            printf("\n");
            _abb_imprimir(raiz->fe,profundidade,0);
    }
    else{
        if (direita){
            printf("------>NULL\n");
            }
        else{
            for (i=0;i<profundidade;i++){
                printf(" |         ");
            }
            printf(" |-------->NULL\n");
        }
    }
}


void abb_imprimir(TABB *raiz){
    printf("----------------------------------------------------------------\n");
    _abb_imprimir(raiz,0,0);
    printf("----------------------------------------------------------------\n");
}

TABB * abb_inserir(TABB * raiz, int chave){
    TABB * novo_no = NULL;

    if (abb_vazia(raiz)){
        novo_no = (TABB*)malloc(sizeof(TABB));
        novo_no->fe = NULL;
        novo_no->fd = NULL;
        novo_no->chave = chave;
        raiz = novo_no;
    }
    else if (chave == raiz->chave){
        printf("no ja existente\n");
    }
    else if (chave<raiz->chave){
        raiz->fe = abb_inserir(raiz->fe,chave);
    }
    else{
        raiz->fd = abb_inserir(raiz->fd,chave);
    }

    return raiz;
}

TABB * abb_buscar(TABB *raiz, int chave){
    TABB * pt;

    if (abb_vazia(raiz)){
        pt = NULL;
    }
    else if (raiz->chave == chave){
        pt = raiz;
    }
    else if (chave<raiz->chave){
        pt = abb_buscar(raiz->fe,chave);
    }
    else{
        pt = abb_buscar(raiz->fd,chave);
    }
    return pt;
}

TABB * abb_encontrar_filho_mais_a_direita(TABB *raiz){

   if (raiz==NULL)
        return NULL;

   while (raiz->fd!=NULL)
        raiz = raiz->fd;

   return raiz;
}



TABB * abb_remover(TABB *raiz, int chave){

    TABB *rmc_pt = NULL, *aux_pt;

    if (raiz==NULL){
        return NULL;
    }
    else if (chave<raiz->chave){
        raiz->fe = abb_remover(raiz->fe,chave);
    }
    else if (chave>raiz->chave){
        raiz->fd = abb_remover(raiz->fd,chave);
    }
    else{/*raiz->chave == chave */
        if ((raiz->fe == NULL)&&(raiz->fd == NULL)){ //No folha
            free(raiz);
            raiz = NULL;
        }
        else if (raiz->fd == NULL){// No com subarvore direita vazia
            aux_pt = raiz;
            raiz = raiz->fe;
            free(aux_pt);
        }
        else if (raiz->fe == NULL){// No com subarvore esquerda vazia
            aux_pt = raiz;
            raiz = raiz->fd;
            free(aux_pt);
        }
        else{ // No interno com duas subarvores nao vazias
            rmc_pt = abb_encontrar_filho_mais_a_direita(raiz->fe);
            raiz->chave = rmc_pt->chave;
            rmc_pt->chave = chave;
            raiz->fe = abb_remover(raiz->fe,chave);
        }
    }
    return raiz;
}


TABB * abb_sucessor(TABB * raiz, int chave){
    TABB * s;

    if (!raiz) return NULL;

    if (raiz->chave>chave){
        s = abb_sucessor(raiz->fe,chave);
        if (!s){
            s = raiz;
        }
    }
    else if (raiz->chave<chave){
        s = abb_sucessor(raiz->fd,chave);
    }
    else{// no com chave encontrado
        s = raiz->fd; // a partir do filho direito, caso exista navegar sempre a esquerda
        if (s!=NULL){
            while (s->fe!=NULL){
                s = s->fe;
            }
        }
    }
    return s;
}

