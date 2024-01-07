#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>



enum tipo_forma{CIRCULO,RETANGULO,TRIANGULO};

typedef struct vetor2d{float x;
                       float y;}Vetor2d;

typedef struct retangulo{float altura;
                         float largura;
                         Vetor2d pos;}Retangulo, *PRetangulo;

typedef struct circulo{float raio;
                       Vetor2d centro;}Circulo, *PCirculo;

typedef struct forma{enum tipo_forma tipo;  
                     void *fig;}Forma, *PForma;

typedef struct{int tam_max;
               int n;
               PForma *elems;} ListaFormas, *PListaFormas;

PCirculo criar_circulo(float raio, Vetor2d centro){
    PCirculo pcirculo = (PCirculo)malloc(sizeof(Circulo));
    pcirculo->raio = raio;
    pcirculo->centro = centro;
    return pcirculo;
}

PRetangulo criar_retangulo(float altura, float largura, Vetor2d posicao){
    PRetangulo pretangulo = (PRetangulo)malloc(sizeof(Retangulo));
    pretangulo->altura = altura;
    pretangulo->largura = largura;
    pretangulo->pos = posicao;
    return pretangulo;
    
}

PForma criar_forma(enum tipo_forma tipo, void *fig){
    PForma pforma = (PForma)(malloc(sizeof(Forma)));
    pforma->tipo = tipo;
    pforma->fig = fig;
    return pforma;
}



PListaFormas criar_lista_formas(int tam_max){
    PListaFormas pformas = (PListaFormas)malloc(sizeof(ListaFormas));
    pformas->tam_max = tam_max;
    pformas->n = 0;
    pformas->elems = (PForma*)malloc(tam_max*sizeof(Forma));
    return pformas;
}

PListaFormas desalocar_lista_formas(PListaFormas plistaformas){
    for (int i=0;i<plistaformas->n;i++){
        PForma pforma = plistaformas->elems[i];

        free(pforma->fig); //deslocar a figura geometrica
        free(pforma);      //desalocar a forma abstrata (que contém um ponteiro para uma figura geometrica)
    }
    free(plistaformas->elems); //deslocar o array elems
    free(plistaformas); //deslocar a estrutura que guarda a lista de formas
}

void imprimir_lista_formas(PListaFormas lista_formas){
    printf("-------------------------------------------------------------\n");
    printf("Total de figuras:%d\n",lista_formas->n);
    for (int i=0;i<lista_formas->n;i++){
        PForma pforma = lista_formas->elems[i];
        switch(pforma->tipo){
            case CIRCULO:{
                PCirculo pcirculo = (PCirculo)(pforma->fig);
                printf("Circulo (%f %f %f)\n",pcirculo->raio, pcirculo->centro.x,pcirculo->centro.y);
            }
            break;
            case RETANGULO:{
                PRetangulo pretangulo = (PRetangulo)(pforma->fig);
                printf("Retangulo (%f %f %f %f)\n",pretangulo->pos.x, pretangulo->pos.y,
                                                   pretangulo->altura, pretangulo->largura);
            }
        }
    }
    printf("-------------------------------------------------------------\n");
}

void adicionar_lista_formas(PListaFormas lista_formas, PForma forma){
    lista_formas->elems[lista_formas->n++] = forma;
}

int main(){
    PListaFormas plista_formas;
    char c;
    PForma pforma;
    plista_formas = criar_lista_formas(100);

    while(1){
        printf("Digite o tipo da forma\n");
        printf("C - Circulo\n");
        printf("R - Retangulo\n");
        printf("X - Sair\n");

        c = getchar();
        c = toupper(c);
        getchar();

        if (c == 'X'){
            break;
        }

        switch(c){
            case 'C':{
                float raio;
                Vetor2d centro;
                printf("Digite o raio, cx e cy\n");
                scanf("%f %f %f",&raio,&centro.x,&centro.y);              
                PCirculo pcirculo = criar_circulo(raio, centro);
                pforma = criar_forma(CIRCULO,pcirculo);
            }    
            break;
            case 'R':{
                float altura,largura;
                Vetor2d pos;
                printf("Digite a posicao (p.x, p.y), altura e largura\n");
                scanf("%f %f %f %f",&pos.x,&pos.y,&altura,&largura);              
                PRetangulo pretangulo = criar_retangulo(altura, largura, pos);
                pforma = criar_forma(RETANGULO,pretangulo);
            }    
            break;

            default:
            break;
        }
        
        getchar();

        adicionar_lista_formas(plista_formas,pforma);

    }

    imprimir_lista_formas(plista_formas);
    desalocar_lista_formas(plista_formas);

}



