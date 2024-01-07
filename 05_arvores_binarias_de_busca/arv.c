#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<ctype.h>
#include"arv.h"




TArv * arv_criar_vazia(){
    return NULL;
}

TArv * arv_criar(int chave, int n_filhos,...){
    va_list ap; //lista variavel de argumentos

    va_start(ap, n_filhos); // determina o ultimo argumento fixo da lista de argumentos
                           // (no caso o parametro n)

    TArv * no = (TArv*)malloc(sizeof(TArv));   
    no->chave = chave;
    no->n_filhos = n_filhos;
    no->filhos = NULL;
    if (n_filhos>0){
        no->filhos = (TArv**)malloc(no->n_filhos*sizeof(TArv*));
        for (int i=0;i<n_filhos;i++){
            no->filhos[i] = va_arg(ap, TArv*);
        }
    }
    

    va_end(ap);

    return no;

}

void arv_imprimir(TArv *raiz){
    if (raiz!=NULL){
        if (raiz->n_filhos>0){
            printf("(");
        }
        printf("%d",raiz->chave);
        if (raiz->n_filhos>0){
            printf("-->");
        }
        for(int i=0;i<raiz->n_filhos;i++){
            arv_imprimir(raiz->filhos[i]);
            if (i<raiz->n_filhos-1){
                printf(",");
            }
        }
        if (raiz->n_filhos>0){
            printf(")");
        }
    }
}

void arv_imprimir2(TArv *raiz){
    if (raiz!=NULL){
        printf("( ");
        printf("%d ",raiz->chave);

        if (raiz->n_filhos>0){
            printf("( ");
            for(int i=0;i<raiz->n_filhos;i++){
                arv_imprimir2(raiz->filhos[i]);
            }        
            printf(" ) ");
        }
     
        printf(")");

    }
}

int pegar_chave(char *s, int *p){
    int chave = 0;

    while (s[*p]==' '){
        (*p)++;
    }

    if (!isdigit(s[*p])){
        printf("pos:%d - Erro: chave invalida",p);
    }
    else{
        
        while(isdigit(s[*p])){
            chave = chave*10+(s[*p]-48);
            (*p)++;
        }    
    }
    return chave;
}
char token(char * s, int *p){
    
    while (s[*p]==' '){
        (*p)++;
    }

    char token = s[*p]; 

    if ((token!='(') && (token!=')')){
        printf("pos:%d - %c e um token invalido",*p,token);
        exit(1);
    }

    return s[(*p)];

}

TArvFEID * arv_criar_feid(char * rep_par, int *pos){

    TArvFEID * novo_no = NULL;
    int chave;
    
    if (token(rep_par,pos)=='('){
        (*pos)++;
        chave = pegar_chave(rep_par,pos);
        
        novo_no = (TArvFEID*)malloc(sizeof(TArvFEID));
        novo_no->chave = chave;
        novo_no->id = NULL;
        novo_no->fe = NULL;
    
        if (token(rep_par,pos)=='('){
            (*pos)++;
            novo_no->fe = arv_criar_feid(rep_par,pos); //converte a primeira arvore

            TArvFEID *aux = novo_no->fe;
            while(token(rep_par,pos) == '(') { // converte demais arvores da lista
                aux->id = arv_criar_feid(rep_par, pos);
                aux = aux->id;
            }
                // fecha a lista de filhos
            if (token(rep_par,pos)!=')'){
                printf("pos:%d - Lista nao fechada apropriadamente",pos);
                exit(1);
            }
            (*pos)++;
        }
        
        if (token(rep_par,pos)!=')'){// fecha a arvore
            printf("pos:%d - Arvore nao fechada apropriadamente",pos);
            exit(1);
        }
        (*pos)++;  
        
    }
    else{
        printf("pos:%d - Arvore nao aberta apropriadamente",pos);
        exit(1);
    }

    return novo_no;
}


TArvFEID * arv_converter_gen_feid(TArv *arv){
    TArvFEID *arv_feid = NULL;
    if (arv){ 
        arv_feid = (TArvFEID*)malloc(sizeof(TArvFEID));
        arv_feid->chave = arv->chave;
        arv_feid->fe = NULL;
        arv_feid->id = NULL;
        if (arv->n_filhos!=0){
            arv_feid->fe = arv_converter_gen_feid(arv->filhos[0]);
            TArvFEID * aux = arv_feid->fe;
            for (int i=1;i<arv->n_filhos;i++){
                aux->id = arv_converter_gen_feid(arv->filhos[i]);    
                aux = aux->id; 
            }
        }
    }
    return arv_feid;
}

TArvFEID * arv_converter_arvbin_feid(TArvBin * arv){
    TArvFEID *arv_feid = NULL;
    if (arv){ 
        arv_feid = (TArvFEID*)malloc(sizeof(TArvFEID));
        arv_feid->chave = arv->chave;
        arv_feid->fe = NULL;
        arv_feid->id = NULL;
        
        if (arv->fe){
            arv_feid->fe = arv_converter_arvbin_feid(arv->fe);
            arv_feid->fe->id = arv_converter_arvbin_feid(arv->fd);
        }
        else if (arv->fd){
            arv_feid->fe = arv_converter_arvbin_feid(arv->fd);
        }
    }
    return arv_feid;
}


TArvFEID * arv_converter_abb_feid(TABB * arv){
    TArvFEID *arv_feid = NULL;
    if (arv){ 
        arv_feid = (TArvFEID*)malloc(sizeof(TArvFEID));
        arv_feid->chave = arv->chave;
        arv_feid->fe = NULL;
        arv_feid->id = NULL;
        
        if (arv->fe){
            arv_feid->fe = arv_converter_abb_feid(arv->fe);
            arv_feid->fe->id = arv_converter_abb_feid(arv->fd);
        }
        else if (arv->fd){
            arv_feid->fe = arv_converter_abb_feid(arv->fd);
        }
    }
    return arv_feid;
}


int arv_feid_vazia(TArvFEID *raiz){
    return raiz == NULL;
}

int arv_checar_arv_feid_arvbin(TArvFEID *raiz){
    int result = 1;
    if (raiz){
        int num_filhos = 0;
        TArvFEID * filho = raiz->fe;
        while(filho!=NULL){
            num_filhos++;
            filho=filho->id;
            if ( (num_filhos>2) || (!arv_checar_arv_feid_arvbin(filho))){
                result = 0;
                break;
            }
        }
    }
    return result;
}


void _arv_converter_rep_paren(TArvFEID *raiz, int *pos, char *s){
    if (raiz){
        s[(*pos)++]='(';
        char buffer[10];
        sprintf(buffer,"%d",raiz->chave);
        for (int i=0;i<strlen(buffer);i++){
            s[(*pos)++]=buffer[i];
        }
        if (raiz->fe){
            s[(*pos)++]='(';
            _arv_converter_rep_paren(raiz->fe,pos,s);
            TArvFEID *aux = raiz->fe;
            while (aux->id!=NULL){
                _arv_converter_rep_paren(aux->id,pos,s);
                aux = aux->id;
            }
            s[(*pos)++]=')';
        }    
        s[(*pos)++]=')';
    }
}

void arv_converter_rep_parentizada(TArvFEID *raiz, char *s){
    int pos = 0;
    _arv_converter_rep_paren(raiz,&pos,s);
    s[pos]='\0';
}

void _arv_feid_imprimir(TArvFEID *raiz,int profundidade, int direita){
    int i;
    if (!arv_feid_vazia(raiz)){
            if (direita){
                printf("------>");
            }
            else{
                for (i=0;i<profundidade;i++){
                    printf(" |         ");
                }
            }
            printf("(%2d)",raiz->chave);
            _arv_feid_imprimir(raiz->id,profundidade+1,1);
            for (i=0;i<profundidade+1;i++){
                printf(" |         ");
            }
            printf("\n");
            for (i=0;i<profundidade+1;i++){
                printf(" |         ");
            }
            printf("\n");
            _arv_feid_imprimir(raiz->fe,profundidade,0);
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

void arv_feid_imprimir(TArvFEID *raiz){
    printf("----------------------------------------------------------------\n");
    _arv_feid_imprimir(raiz,0,0);
    printf("----------------------------------------------------------------\n");
}



