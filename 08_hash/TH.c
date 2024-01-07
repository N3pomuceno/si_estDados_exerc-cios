#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<memory.h>
#include"TH.h" 

#define ATIVO 1

TPar * criar_par(void *chave, void *valor, int tam_chave, int tam_valor){
    TPar * par = (TPar*)malloc(sizeof(TPar));
    par->chave = malloc(sizeof(tam_chave));
    par->valor = malloc(sizeof(tam_valor));
    par->status = ATIVO;
    memcpy(par->chave,chave,tam_chave);
    memcpy(par->valor,valor,tam_valor);
    return par; 
}

//Converte os bytes de uma chave para um inteiro
//efetuando ou-exclusivo entre grupos de 4 bytes

int chave_para_inteiro(void *chave, int tam_chave){
    unsigned char *_chave = (unsigned char*)chave;
    int k=0;
    int resultado = 0;
    int janela = 0;

    //Se a chave ocupar menos que 4 bytes, nao usa o metodo da dobra
    //Ja retorna o proprio valor como inteiro
    if (tam_chave<=sizeof(int)){
        return (int)(*_chave);
    }


    while (k<=tam_chave+sizeof(int)){
        memcpy(&janela,_chave+k,sizeof(int));    
        resultado = resultado ^ janela;
        
        k+=sizeof(int);
    }

    return resultado;
}

int hash(void *chave, int tam_chave, int n){
    int _chave = chave_para_inteiro(chave, tam_chave);
    return _chave % n;
}

int hash_linear(void *chave, int n, int tam_chave, int k){
    return (hash(chave,tam_chave,n)+k)%n;
}


TTabHash * TH_criar(int n, int tam_chave, int tam_valor){
    TTabHash* t = (TTabHash*)malloc(sizeof(TTabHash));

    t->n = n;
    t->tam_chave = tam_chave;
    t->tam_valor = tam_valor;
    t->ocupacao = 0;

    t->elem = (TPar**)malloc(n*sizeof(TPar*));
    
    for (int i=0;i<n;i++){
        t->elem[i] = NULL;
    }
    
    return t;
}




void TH_set_callback_comparar(TTabHash *t,int (*comp)(void*a,void*b)){
    t->comp = comp;
}

void TH_set_callback_imprimir_chave(TTabHash *t,void (*imprimir)(void*a)){
    t->imprimir_chave = imprimir;
}
void TH_set_callback_imprimir_valor(TTabHash *t,void (*imprimir)(void*a)){
    t->imprimir_valor = imprimir;
}


TPar * TH_inserir(TTabHash *t, void *chave, void *valor){ 
    int k = 0;
    int prim_pos_livre = -1;

    if (t->ocupacao == t->n){
        printf("Sem espaço na hash\n");
        exit(1);
        //A implementar o redimensionamento
    }

    do{
        //Calcula o indice via a funcao hash
        int index = hash_linear(chave,t->n,t->tam_chave, k++);

        //Se o elemento existir na hash e estiver ativo (não removido)
        if ((t->elem[index])&&(t->elem[index]->status == ATIVO)){
            TPar *par = t->elem[index];
            //Compara se a chave é identica
            if (t->comp(chave,par->chave)==0){
                //Atualiza o valor do par na tabela hash
                memcpy(par->valor,valor,t->tam_valor);
                //Retorna o par
                return par;    
            }
        }
        else{
            //Se a posicao nao estiver alocada ou se a posicao corresponde a um par removido
            //Guarda a posicao de insercao (primeira posicao livre)
            if (prim_pos_livre == -1){
                prim_pos_livre = index;
            }
            //Se nao houver um par alocado alocado na posicao pode encerrar a busca
            //caso contrario continua pois ele pode aparecer em uma posicao futura da 
            //sequencia de hashing
            if (!t->elem[index]){
                break;
            }
        }
    }while (k < t->n);

    TPar *par;
    //Se é uma posição inativa, simplemente sobre-escreve o valor do par e o ativa
    if (t->elem[prim_pos_livre]){
        par = t->elem[prim_pos_livre];
        memcpy(par->valor,valor,t->tam_valor);
        par->status = ATIVO;
    }
    else{//Senão cria um novo par
        par = criar_par(chave,valor,t->tam_chave,t->tam_valor);
        t->elem[prim_pos_livre] = par;
    }

    t->ocupacao++;
        
    return par;
}

TPar * TH_remover(TTabHash *t, void *chave){ 
    int k = 0;
    do{
        //Calcula o indice via a funcao hash
        int index = hash_linear(chave,t->n,t->tam_chave, k++);

        //Se o elemento existir e estiver ativo
        if ((t->elem[index])&&(t->elem[index]->status == ATIVO)){
            TPar *par = t->elem[index];
            //Se for a mesma chave, o par foi encontrado
            if (t->comp(chave,par->chave)==0){
                //t->elem[index] == NULL;    
                t->elem[index]->status = ~ATIVO;
                t->ocupacao--;
                return par;    
            }
        }
        else if (!t->elem[index]){//Se a posicao nao estiver alocada pode encerrar a busca
            break;
        }
    }while (k < t->n);

    return NULL;
}


TPar * TH_buscar(TTabHash * t, void *chave){ 
    int k = 0;
    
    do{
        //Calcula o indice via a funcao hash
        int index = hash_linear(chave,t->n,t->tam_chave, k++);

        //Se o elemento existir e estiver ativo
        if ((t->elem[index])&&(t->elem[index]->status==ATIVO)){
            TPar * par = t->elem[index];
            //Se for a mesma chave, o par foi encontrado
            if (t->comp(chave,par->chave)==0){
                return par;    
            }
        }
        else if (!t->elem[index]){//Se a posicao nao estiver alocada pode encerrar a busca
            break;
        }
    }while (k < t->n);

    return NULL;
}

TTabHash* TH_liberar(TTabHash *t){
    for (int i=0;i<t->n;i++){
        if (t->elem[i]){
            free(t->elem[i]);
            t->elem[i] = NULL;
        }
        
    }
    free(t->elem);
    return NULL;
}

void TH_imprimir(TTabHash *t){ 
    printf("---------------------------------------------------\n");
    for (int i=0;i<t->n;i++){
        if (!t->elem[i]){
            printf("NULL\n");
        }
        else if (t->elem[i]->status == ATIVO){
            printf("(");
            t->imprimir_chave(t->elem[i]->chave);
            printf(",");
            t->imprimir_valor(t->elem[i]->valor);
            printf(")\n");
        }
        else{
            printf("LIVRE\n");
        }
    }
    printf("---------------------------------------------------\n");
}