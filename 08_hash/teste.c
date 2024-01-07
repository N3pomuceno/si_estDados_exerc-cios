#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#include"THaux.h"
#include"TH.h"


typedef struct ponto{int x;
                     int y;}TPonto;

typedef struct pontof{float x;
                      float y;}TPontof;



int comparar_TPonto(void *a, void *b){
    TPonto *_a = (TPonto*)a;
    TPonto *_b = (TPonto*)b;
    
    if ((_a->x <_b->x)||((_a->x ==_a->x)&&(_a->y < _b->y))){
        return -1;
    }
    else if ((_a->x > _b->x)||((_a->x ==_a->x)&&(_a->y > _b->y))){
        return 1;
    }
    else{
        return 0;
    }
}


void imprimir_TPonto(void *a){
    TPonto *_a = (TPonto*)a;
    printf("(%d,%d)",_a->x,_a->y);
}


int comparar_TPontof(void *a, void *b){
    TPontof *_a = (TPontof*)a;
    TPontof *_b = (TPontof*)b;
    
    if ((abs(_a->x-_b->x)<EPS)&&(abs(_a->y-_b->y)<EPS)){
        return 0;
    }
    else if (((abs(_a->x-_b->x)<EPS)&&(_a->y < _b->y)) ||(_a->x <_b->x)){
        return -1;
    }
    else{
        return 1;
    }
}




void imprimir_TPontof(void *a){
    TPontof *_a = (TPontof*)a;
    printf("(%f,%f)",_a->x,_a->y);
}




void achar_pares_simetricos(TTabHash *t, TPonto *v, int n){
    TPonto p;
    TPonto p_simetrico;
    TPar *par;
    int contador = 1;
    int *valor;
    
    for (int i=0;i<n;i++){
        p = v[i];
        p_simetrico.x = v[i].y;
        p_simetrico.y = v[i].x;


        par = TH_buscar(t,&p);
        if (!par){
            par = TH_inserir(t,&p,&contador);
        }
        else{
            valor = (int*)(par->valor);
            (*valor)++;
        }

        par = TH_buscar(t,&p_simetrico);
        if (!par){
            par = TH_inserir(t,&p_simetrico,&contador);
        }
        else{
            int *valor = (int*)par->valor;
            printf("%d",*valor);
            (*valor)++;
        }
    }
}

//Detecta todos os pares (i,j) tais que (j,i) tambem ocorrem em uma lista
void exemplo_pares_de_pontos_simetricos(){
   TTabHash *t;
   TPonto v[8] = {{1,2},{4,5},{12,9},{2,1},{5,4},{8,7},{3,4},{34,23}};

    t = TH_criar(20,sizeof(TPonto),sizeof(int));
    TH_set_callback_comparar(t,comparar_TPonto);
    TH_set_callback_imprimir_chave(t,imprimir_TPonto);
    TH_set_callback_imprimir_valor(t,TH_imprimir_int);


    achar_pares_simetricos(t,v,8);
    
    TH_imprimir(t);

    printf("Pares simetricos:\n\n");
    for (int i=0;i<20;i++){
        TPar * par = t->elem[i];
        if (par){
            int *valor = (int*)par->valor;
            if ((*valor)==2){
                printf("(");
                imprimir_TPonto(par->chave);
                printf(",");
                TH_imprimir_int(par->valor);
                printf(")\n");
            }
        }
    }

    t = TH_liberar(t);
}

//Dada um array de hobbies de pessoas, retornar todos os pares (pessoa,hobby)
//que tem hobbies em comum

void hashing_string(){
    TTabHash *t_contador;
    char hobbies[10][2][10] =  {{"pedro    \0","jogos    \0"},
                                {"mario    \0","viagem   \0"},
                                {"jose     \0","jogos    \0"},
                                {"carla    \0","pintura  \0"},
                                {"juca     \0","futebol  \0"},
                                {"ana      \0","surf     \0"},
                                {"beatriz  \0","cinema   \0"},
                                {"berta    \0","cinema   \0"},
                                {"bianca   \0","piano    \0"},
                                {"nando    \0","jogos    \0"}};


    t_contador = TH_criar(31,10*sizeof(char),sizeof(int));
    TH_set_callback_comparar(t_contador,TH_comparar_string);
    TH_set_callback_imprimir_chave(t_contador,TH_imprimir_string);
    TH_set_callback_imprimir_valor(t_contador,TH_imprimir_int);

    int contador = 1;
    TPar * par;
    for (int i=0;i<10;i++){
        par = TH_buscar(t_contador,&hobbies[i][1]);
        if (!par){
            TH_inserir(t_contador,&hobbies[i][1],&contador);
        }
        else{
            int* num_repeticoes = (int*)par->valor;
            (*num_repeticoes)++;
        }
    }
    TH_imprimir(t_contador);

    for (int i=0;i<10;i++){
        TPar * par = TH_buscar(t_contador,&hobbies[i][1]);
        int *num_repeticoes = (int*)par->valor;
        if (*num_repeticoes>1){
            printf("(%s,%s)\n",hobbies[i][0],hobbies[i][1]);
        }
    }


    TH_imprimir(t_contador);
    TH_liberar(t_contador);

}

void teste_triangulacao(){
    TTabHash * t;

    t = TH_criar(31,sizeof(TPontof),sizeof(int));
    TH_set_callback_comparar(t,comparar_TPontof);
    TH_set_callback_imprimir_chave(t,imprimir_TPontof);
    TH_set_callback_imprimir_valor(t,TH_imprimir_int);

    FILE * f = fopen("triangulacao.dat","r");
    int num_triangulos;
    fscanf(f,"%d",&num_triangulos);
    
    TPontof *p = (TPontof*)malloc(num_triangulos*sizeof(TPontof));
    TPar *par;

    int indice_vertice = 0;
    for (int i=0;i<num_triangulos;i++){
        for (int j=0;j<3;j++){
            fscanf(f,"%f %f",&p[i].x,&p[i].y);
            
            par = TH_buscar(t,&p[i]);
            if (!par){
                TH_inserir(t,&p[i],&indice_vertice);
                indice_vertice++;
            }
            TH_imprimir(t);
        }
    }
    TH_imprimir(t);
    fclose(f);
}

void teste_char(){

    TTabHash * tc = TH_criar(31,sizeof(char),sizeof(char));

    TH_set_callback_comparar(tc,TH_comparar_char);
    TH_set_callback_imprimir_chave(tc,TH_imprimir_char);
    TH_set_callback_imprimir_valor(tc,TH_imprimir_char);

    char c =  'a';
    char cm = 'A';
    
    for (int i=0;i<26;i++){
        TH_inserir(tc,&c,&cm);
        c +=1;
        cm +=1;
    }

    TH_imprimir(tc);
    TH_liberar(tc);

}

void teste(){

    TTabHash * t = TH_criar(9,sizeof(int),sizeof(int));
    int v[8][2] = {{5,1},{28,2},{19,3},{15,4},{20,5},{33,6},{12,7},{17,8}};

    TH_set_callback_comparar(t,TH_comparar_int);
    TH_set_callback_imprimir_chave(t,TH_imprimir_int);
    TH_set_callback_imprimir_valor(t,TH_imprimir_int);


    for (int i=0;i<8;i++){
        TH_inserir(t,&v[i][0],&v[i][1]);
    }

    TH_imprimir(t);


    TH_remover(t,&v[2][0]);
    TH_remover(t,&v[6][0]);

    TH_imprimir(t);

    TPar * p = TH_buscar(t,&v[4][0]);

    if (p){
        printf("(");
        TH_imprimir_int(p->chave);printf(",");
        TH_imprimir_int(p->valor);
        printf(")\n");

    }
    else{
        printf("(%d,%d) nao encontrado\n",v[4][0],v[4][1]);
    }

    p = TH_buscar(t,&v[7][0]);

    if (p){
        printf("(");
        TH_imprimir_int(p->chave);printf(",");
        TH_imprimir_int(p->valor);
        printf(")\n");    }
    else{
        printf("(%d,%d) nao encontrado\n",v[4][0],v[4][1]);
    }

    TH_liberar(t);


}

int main(void){
 
    teste_char();
    
    //  teste();
    
    //  hashing_string();
    
    // teste_triangulacao();

    // exemplo_pares_de_pontos_simetricos();


}