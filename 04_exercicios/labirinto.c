#include <stdio.h>
#include <stdlib.h>

typedef struct coord{int i;
                     int j;}Coord;

typedef struct caminho{int n;
                       Coord *vert;}Caminho;

typedef struct mat_char{int n_lin;
                        int n_col;
                        char **elems;}Mat_char;

void marca_mapa(Mat_char *mapa, Caminho * caminho);

Caminho * alocar_caminho(int n){
    Caminho * caminho = (Caminho*)malloc(sizeof(Caminho));
    caminho->n = 0;
    caminho->vert = (Coord*)malloc(n*sizeof(Coord));
}

Caminho * desalocar_caminho(Caminho *caminho){
    free(caminho->vert);
    free(caminho);
    return NULL;
}

void imprimir_caminho(Caminho *cam){
    for (int i=0;i<cam->n;i++){
            printf("(%d,%d) ",cam->vert[i].i,cam->vert[i].j);

    }
    printf("\n");
}

Mat_char * alocar_matriz_char(int n_lin, int n_col){
    Mat_char * m = (Mat_char*)malloc(sizeof(Mat_char));

    m->n_lin = n_lin;
    m->n_col = n_col;

    m->elems = (char**)malloc(n_lin*sizeof(char*));

    for (int i=0;i<n_lin;i++){
        m->elems[i] = (char*)malloc(n_col*sizeof(char));
    }

    return m;
}

Mat_char * desalocar_matriz_char(Mat_char *m){

    for (int i=0;i<m->n_lin;i++){
        free(m->elems[i]);
    }

    free(m->elems);

    free(m);

    return NULL;
}

Mat_char *le_labirinto(char *nome_arq){
    int n_lin,n_col;
    FILE * f = fopen(nome_arq,"r");

    fscanf(f,"%d %d",&n_lin,&n_col);
    fgetc(f);

    Mat_char *mapa = alocar_matriz_char(n_lin,n_col);
    char c;

    for (int i=0;i<n_lin;i++){
        for (int j=0;j<n_col;j++){
            fscanf(f,"%c",&(mapa->elems[i][j]));
        }
        fgetc(f);    
    }
    
    fclose(f);

    return mapa;

}

void imprimir_matriz(Mat_char *mapa){
    
    for (int i=0;i<mapa->n_lin;i++){
        for (int j=0;j<mapa->n_col;j++){
            printf("%c ",mapa->elems[i][j]);
        }
        printf("\n");
    }
}

void imprimir_mapa(Mat_char *mapa){
    unsigned char bloco = 178;
    unsigned char ponto = 254;
    for (int i=0;i<mapa->n_lin;i++){
        for (int j=0;j<mapa->n_col;j++){
            if (mapa->elems[i][j]=='1'){
                printf("%c",bloco);
                printf("%c",bloco);
                printf("%c",bloco);
            }
            else if (mapa->elems[i][j]=='X'){
                printf(" %c ",ponto);
            }
            else if (mapa->elems[i][j]=='0'){
                printf("   ");
            }
            else{
                printf(" %c ",mapa->elems[i][j]);
            }
        }
        printf("\n");
    }
}


void inicializa_visitados(Mat_char *visitados){
    for (int i=0;i<visitados->n_lin;i++){
        for (int j=0;j<visitados->n_col;j++){
           visitados->elems[i][j] ='F';
        }
    }
}

int saida(Mat_char *mapa,Coord posicao){
    if (mapa->elems[posicao.i][posicao.j]=='S'){
        return 1;
    }
    else{
        return 0;
    }
}


int valida(Mat_char *mapa, Mat_char *visitados, Coord posicao){
    if (posicao.i<0 || posicao.i>=visitados->n_lin || posicao.j<0 || posicao.j>=visitados->n_col){
        return 0;
    }
    if (visitados->elems[posicao.i][posicao.j]=='T'){
        return 0;
    }
    if (mapa->elems[posicao.i][posicao.j]=='1'){
        return 0;
    }
    return 1;
}

int encontra_caminho(Mat_char *mapa, Mat_char *visitados, Coord posicao, 
                      Caminho *caminho){
            
    if (!valida(mapa,visitados, posicao)){
        return 0;
    }
    else{
        if (saida(mapa,posicao)){
            return 1;
        }
        else{
            caminho->vert[caminho->n++] = posicao;
            visitados->elems[posicao.i][posicao.j]='T';
            mapa->elems[posicao.i][posicao.j] = 'X';

            getc(stdin);
            system("cls");
            imprimir_mapa(mapa);
            
            for (int i=-1;i<=1;i++){
                for (int j=-1;j<=1;j++){
                    if ((i!=0 && j==0) || (i==0 && j!=0)){
                        
                        Coord nova_posicao;
                        nova_posicao.i = posicao.i+i;
                        nova_posicao.j = posicao.j+j;

                        if (encontra_caminho(mapa,visitados,nova_posicao,caminho)){
                            return 1;
                        }
                    }
                }
            }
            mapa->elems[posicao.i][posicao.j] = '.';
            caminho->n--;

            getc(stdin);
            system("cls");
            imprimir_mapa(mapa);

            return 0;
        }

    }        
}

void marca_mapa(Mat_char *mapa, Caminho * caminho){
    
    for (int i=0;i<caminho->n;i++){
        int pos_i = caminho->vert[i].i;
        int pos_j = caminho->vert[i].j;

        if (mapa->elems[pos_i][pos_j] != 'S' && mapa->elems[pos_i][pos_j]!='E'){
            mapa->elems[pos_i][pos_j] = 'X';
        }
    }
}

int main()
{
    char nome_mapa[40];

    printf("Digite o nome do mapa\n");
    scanf("%s",nome_mapa); 
    Mat_char * mapa = le_labirinto(nome_mapa);
    Mat_char * visitados = alocar_matriz_char(mapa->n_lin,mapa->n_col);
    Caminho * caminho = alocar_caminho(100);
    Coord posicao;
    
    posicao.i = 1;
    posicao.j = 1;
    mapa->elems[posicao.i][posicao.j] = 'E';

    inicializa_visitados(visitados);
    printf("----------------------------------------------------------------------\n");
    encontra_caminho(mapa,visitados,posicao,caminho);   

    imprimir_mapa(mapa);
    imprimir_caminho(caminho);
    desalocar_matriz_char(mapa);
    desalocar_matriz_char(visitados);
    desalocar_caminho(caminho);
}
