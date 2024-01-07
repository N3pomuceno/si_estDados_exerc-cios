#include<stdio.h>
#include<stdlib.h>

typedef struct Aluno{int mat;
                     float cr;}TAluno;
                     
typedef struct no_arvbin{
                 int chave;
                 struct no_arvbin *fe;
                 struct no_arvbin *fd;
}TArvBin;


TArvBin *arvbin_criar_no(int chave, TArvBin *fe, TArvBin *fd){
  TArvBin * no = (TArvBin*)malloc(sizeof(TArvBin));
  no->chave =chave;
  no->fe = fe;
  no->fd = fd;
  return no;
}

int arvbin_vazia(TArvBin *raiz){
  return (raiz==NULL);
}

TArvBin * arvbin_criar_arv(int *chaves, int ini, int fim){
  
  if (ini>fim){
    return NULL;
  }
  else{
    int meio = (ini+fim)/2;
    TArvBin *no = arvbin_criar_no(chaves[meio],NULL,NULL);
    no->fe = arvbin_criar_arv(chaves,ini, meio-1);
    no->fd = arvbin_criar_arv(chaves,meio+1,fim);
    return no;
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




int main() {
  
  int chaves[10] = {1,4,7,9,15,17,23,34,35,47};
  
  /*TArvBin * a = arvbin_criar_no(10,NULL,NULL);
  
  a->fe = arvbin_criar_no(7,NULL,NULL);
  a->fd = arvbin_criar_no(15,NULL,NULL);
  
  a->fe->fd = arvbin_criar_no(3,NULL,NULL);
  a->fe->fe = arvbin_criar_no(9,NULL,NULL);
  */
  TArvBin * a = arvbin_criar_arv(chaves,0,4);
  arvbin_imprimir(a);
  
  return 0;

}