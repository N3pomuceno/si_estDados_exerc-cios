#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

struct aluno{char nome[30];
             int matricula;
             };

typedef struct aluno TAluno;

struct lista_alunos{
    int tam;
    int n;
    TAluno *vet;
};

typedef struct lista_alunos TListaAlunos;

TListaAlunos * criar_alunos(int tam){
    TListaAlunos * la = (TListaAlunos*)malloc(sizeof(TListaAlunos));

    la->tam = tam;
    la->n = 0;
    la->vet = (TAluno*)malloc(tam*sizeof(TAluno));
    return la;
}

TListaAlunos * desalocar_alunos(TListaAlunos * la){
    free(la->vet);
    free(la);
    return NULL;
}

void inserir_aluno(TListaAlunos *la,char *nome, int mat){
    strcpy(la->vet[la->n].nome,nome);
    la->vet[la->n].matricula = mat;
    (la->n)++;

}

void imprimir_alunos(TListaAlunos *la){
    printf("\n______________________________________________________________\n\n");
    printf("                            Alunos                                \n");
    printf("______________________________________________________________\n\n");
    printf("Total: %d\n",la->n);
    for (int i=0;i<la->n;i++){
        printf("-------------------------------------------------------------\n");
        printf("Aluno %d\n",i);
        printf("Nome: %s\n",la->vet[i].nome);
        printf("Matricula: %d\n",la->vet[i].matricula);
        printf("-------------------------------------------------------------\n");
    }
    printf("\n______________________________________________________________\n\n");
}

void inicializar_alunos(TListaAlunos *la){
    inserir_aluno(la,"joao",111111);
    inserir_aluno(la,"maria",111112);
    inserir_aluno(la,"carlos",111113);
    inserir_aluno(la,"pedro",111114);
    inserir_aluno(la,"afonso",111115);
    inserir_aluno(la,"marcos",111116);
    inserir_aluno(la,"anselmo",111117);
    inserir_aluno(la,"claudia",111118);
    
}

//size_t é um tipo predefinido que depende da implementação 
//da linguagem. Por exemplo, pode ser unsigned int

void trocar(void *a, void *b, size_t tamanho_bytes){
    unsigned char temp[tamanho_bytes];

    memcpy(temp,a,tamanho_bytes);
    memcpy(a,b,tamanho_bytes);
    memcpy(b,temp,tamanho_bytes);

}


int cmp_aluno(const void *al0, const void *al1){

    TAluno *aluno_0 = (TAluno*)al0;
    TAluno *aluno_1 = (TAluno*)al1;

    int result = strcmp(aluno_0->nome,aluno_1->nome);

    if (result){
        return result;
    }
    else{
        if (aluno_0->matricula<aluno_1->matricula){
            return -1;
        }
        else if (aluno_0->matricula>aluno_1->matricula){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void my_qsort(void *vet, int n, int tamanho_bytes, int (*cmp)(const void*a, const void *b)){
    
    if (n<=1) {return;};

    int offset = tamanho_bytes;
    unsigned char *v = (unsigned char *)vet;
    unsigned char *pivo = &v[0];
    int a = 1;
    int b = (n-1);

    do{
        while (a<n && cmp(&v[a*offset],pivo)<=0) {a++;};
        while (cmp(&(v[b*offset]),pivo)>0) {b--;};
        
        if (a<b){
            trocar(&v[a*offset],&v[b*offset],tamanho_bytes);    
        }

    }while(a<=b);

    trocar(&v[0],&v[b*offset],tamanho_bytes);

    my_qsort(v,b,tamanho_bytes,cmp);
    my_qsort(&v[(b+1)*offset],n-b-1,tamanho_bytes,cmp);

}

void imprimir_vetor(char *s,int *v,int n){
    printf("%s = [ ",s);
    for (int i=0;i<n;i++){
        printf("%d ",v[i]);
    }
    printf(" ]\n");
}

int cmp_int(const void *a, const void *b){

    int *ai = (int*)a;
    int *bi = (int*)b;

    if (*ai<*bi){
        return -1;
    }
    else if (*ai>*bi){
        return 1;
    }
    else{
        return 0;
    }
}



int main(){

   TListaAlunos * la = criar_alunos(10);
   inicializar_alunos(la);
   // imprimir_alunos(la);

    printf("Tamanho do tipo aluno\n");
    printf("%d\n",sizeof(TAluno));

    TAluno * vetor_aluno = la->vet;

   // printf("%s %d\n",vetor_aluno[2].nome, vetor_aluno[2].matricula);

   // char *v = (char*)la->vet;
    
    printf("%s",&v[36]);

    /*
    trocar(&(la->vet[0]),&(la->vet[3]),sizeof(TAluno));
    imprimir_alunos(la);
    


    int resultado = cmp_aluno(&(la->vet[0]),&(la->vet[3]));

    if (resultado<0){
        printf("%s vem antes de %s\n",&(la->vet[0]),&(la->vet[3]));
    }
    else if (resultado>0){
        printf("%s vem depois de %s\n",&(la->vet[0]),&(la->vet[2]));
    }
    else{
        printf("Os dois são iguais\n");
    }

    my_qsort(la->vet,la->n,sizeof(TAluno),cmp_aluno);

    imprimir_alunos(la);

    la = desalocar_alunos(la);

    int vet[10] = {9,3,5,2,4,6,1,8,7,10};

    imprimir_vetor("vet",vet,10);

    my_qsort(vet,10,sizeof(int),cmp_int);

    imprimir_vetor("vet",vet,10);

    */


    return 0;
}