#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pilha.c"

#define TAM_ELEM 10*sizeof(char)

void imprimir_char(TElem e){
    char *c = (char*)e;
    printf("%c",*c);
}

void imprimir_str(TElem e){
    char * s = (char*)e;
    printf("%s",s);
}

void imprimir_int(TElem e){
    int * i = (int*)e;
    printf("%d ",*i);
}

int eh_operador(char c){
    return ((c=='+')||(c=='-')||(c=='*')||(c=='/'));
}


char * converte_notacao_polonesa_reversa(char * expr){
    TPilha * p = pilha_criar(50,sizeof(char));
    char * polonesa_rev = (char*)malloc(50*sizeof(char));
    
    int i=0, j=0;
    while (expr[i]!='\0'){
        /* Caracteres que nao sao '(', ')', '+', '-', '*', '/'
           if ((!eh_operador(expr[i]))&&(expr[i]!='(')&&(expr[i]!=')')){ */

        // Tratar numeros
        if (isdigit(expr[i])){
            do{
                polonesa_rev[j++] = expr[i];
                i++;
            }while(isdigit(expr[i]));
            i--;  //recuar um elemento
            polonesa_rev[j++] = ' '; 
        }
        else if (eh_operador(expr[i])){
            pilha_empilhar(p,&expr[i],sizeof(char));
            pilha_dump(p,1,imprimir_char);
        }
        else if (expr[i]==')'){
            if (!pilha_verificar_vazia(p)){
                char op;
                pilha_desempilhar(p,&op,sizeof(char));
                pilha_dump(p,1,imprimir_char);
                polonesa_rev[j++] = op;
                polonesa_rev[j++] = ' ';
            }
            else{
                printf("Nao eh possível converter.Expressao incorreta\n");
                free(polonesa_rev);
                polonesa_rev = NULL;
                break;
            }
        }
        i++;
    }
    
    if (polonesa_rev){
        polonesa_rev[j]='\0';
    }

    pilha_liberar(p);

    return polonesa_rev;    
}


int avalia_expr_polonesa_reversa(char * expr){
    // Pilha de inteiros
    TPilha * p = pilha_criar(50,sizeof(int));
    //resultado final
    int total = 0;
    //string que representa uma sequencia de digitos que forma um inteiro
    char * numero = (char*)malloc(10*sizeof(char));
    
    int i=0;
    while (expr[i]!='\0'){

        if (isdigit(expr[i])){
            int j = 0;
            do{
                numero[j++] = expr[i];
                i++;
            }while(isdigit(expr[i]));
            i--;
            numero[j++] = '\0'; 
            int operando = atoi(numero);
            pilha_empilhar(p,&operando,sizeof(int));
            pilha_dump(p,sizeof(int),imprimir_int);
        }
        else if (eh_operador(expr[i])){
            int operando1,operando2,resultado;

            pilha_desempilhar(p,&operando2,sizeof(int));
            pilha_desempilhar(p,&operando1,sizeof(int));
            switch(expr[i]){
                case '+':  resultado = operando1+operando2;break;
                case '-':  resultado = operando1-operando2;break;
                case '*':  resultado = operando1*operando2;break;
                case '/':  resultado = operando1/operando2;break;
                default: printf("Erro de avaliacao\n");
                break;
            }
            pilha_empilhar(p,&resultado,sizeof(int));
            pilha_dump(p,sizeof(int),imprimir_int);
        }
        i++;
    }
    
    pilha_desempilhar(p,&total,sizeof(int));

    pilha_liberar(p);

    free(numero);

    return total;    
}

int verifica_expressao_parentizada(char * expr){
    TPilha * p = pilha_criar(20,sizeof(char));

    int i=0;
    int resultado;

    while (expr[i]!='\0'){
        printf("i = %d - \' %c \'  ",i,expr[i]);
        if (expr[i]=='('){
            pilha_empilhar(p,&expr[i],sizeof(char));
            
            pilha_dump(p,sizeof(char),imprimir_char);
        }
        else if (expr[i]==')'){
            if (pilha_verificar_vazia(p)){
                printf("Erro na posicao:%d\n",i);
                return 0;
            }
            char c;
            pilha_desempilhar(p,&c,sizeof(char));
            pilha_dump(p,sizeof(char),imprimir_char);
        }

        i++;
        printf("\n");
    }

    if (!pilha_verificar_vazia(p)){
        resultado = 0;
    }
    else{
        resultado = 1;
    }

    pilha_liberar(p);

    return resultado;
}

int main()
{

    char expressao[20];
    
    printf("Digite a expressao\n");
    scanf("%s",expressao);

    printf("Expressao lida:%s\n",expressao);

    if (verifica_expressao_parentizada(expressao)){
        printf("Expressao correta!\n");
    }
    else{
        printf("Erro de parentizacao!\n");
    }



    char * polonesa_rev = converte_notacao_polonesa_reversa(expressao);

    if (polonesa_rev){
        printf("%s\n",polonesa_rev);
    }

    printf("Resultado %d\n",avalia_expr_polonesa_reversa(polonesa_rev));


    return 0;
}

