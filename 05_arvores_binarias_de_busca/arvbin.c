
#include<stdio.h>
#include<stdlib.h>
#include"arvbin.h"


TArvBin * arvbin_criar_vazia(){
    return NULL;
}

TArvBin * arvbin_criar(int chave, TArvBin * fe, TArvBin * fd){
    TArvBin * novo_no;
    novo_no = (TArvBin*)malloc(sizeof(TArvBin));
    novo_no->chave = chave;
    novo_no->fe = fe;
    novo_no->fd = fd;

    return novo_no;
}

int arvbin_vazia(TArvBin * raiz){
    return raiz == NULL;
}

TArvBin * arvbin_desalocar(TArvBin *raiz){
    if (!arvbin_vazia(raiz)){
        raiz->fe = arvbin_desalocar(raiz->fe);
        raiz->fd = arvbin_desalocar(raiz->fd);
        free(raiz);
    }
    return NULL;
}

TArvBin * arvbin_buscar(TArvBin *raiz, int chave){
    TArvBin * pt;

    if (arvbin_vazia(raiz))
        return NULL;

    if (raiz->chave == chave)
        pt = raiz;
    else{
        // Tenta buscar a chave na subarvore esquerda
        pt = arvbin_buscar(raiz->fe,chave);
        
        if (pt==NULL) // Se nao houve sucesso, tenta buscar na subarvore direita
            pt = arvbin_buscar(raiz->fd,chave);
    }
    return pt;
}

int arvbin_altura(TArvBin * raiz){
    int alt1,alt2;
    if (arvbin_vazia(raiz))
        return 0;
    else{
        alt1 = arvbin_altura(raiz->fe);
        alt2 = arvbin_altura(raiz->fd);
        if (alt1>alt2)
            return alt1+1;
        else
            return alt2+1;
    }
}

void _arvbin_imprimir(TArvBin *raiz,int profundidade, int direita){
    int i;
    if (!arvbin_vazia(raiz)){
            if (direita){
                printf("------>");
            }
            else{
                for (i=0;i<profundidade;i++){
                    printf(" |         ");
                }
            }
            printf("(%2d)",raiz->chave);
            _arvbin_imprimir(raiz->fd,profundidade+1,1);
            for (i=0;i<profundidade+1;i++){
                printf(" |         ");
            }
            printf("\n");
            for (i=0;i<profundidade+1;i++){
                printf(" |         ");
            }
            printf("\n");
            _arvbin_imprimir(raiz->fe,profundidade,0);
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


void arvbin_imprimir(TArvBin *raiz){
    printf("----------------------------------------------------------------\n");
    _arvbin_imprimir(raiz,0,0);
    printf("----------------------------------------------------------------\n");
}

void arvbin_pre_ordem(TArvBin *raiz){
    if(raiz!=NULL){
        printf("%d ",raiz->chave);
        arvbin_pre_ordem(raiz->fe);
        arvbin_pre_ordem(raiz->fd);
    }
}
void arvbin_ordem_simetrica(TArvBin *raiz){
    if(raiz!=NULL){
        arvbin_ordem_simetrica(raiz->fe);
        printf("%d ",raiz->chave);
        arvbin_ordem_simetrica(raiz->fd);
    }


}

void arvbin_pos_ordem(TArvBin *raiz){
    if(raiz!=NULL){
        arvbin_pos_ordem(raiz->fe);
        arvbin_pos_ordem(raiz->fd);
        printf("%d ",raiz->chave);
    }
}

int arvbin_conta_nos(TArvBin *raiz){
    if (!raiz) return 0;

    return 1+arvbin_conta_nos(raiz->fe)+arvbin_conta_nos(raiz->fd);

}

int _arvbin_completa(TArvBin *raiz, int indice, int num_nos){
    if (!raiz) return 1;

    if (indice>=num_nos)
        return 0;

    return (_arvbin_completa(raiz->fe,2*indice+1,num_nos) && 
            _arvbin_completa(raiz->fd,2*indice+2,num_nos));

}


int arvbin_completa(TArvBin *raiz)
{
    int num_nos = arvbin_conta_nos(raiz);
    return (_arvbin_completa(raiz,0,num_nos));    
}
