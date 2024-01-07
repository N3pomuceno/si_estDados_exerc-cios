#include<stdio.h>
#include<stdlib.h>


typedef struct lde{
  int info;
  struct lde *ant, *prox;
} TLDE;


//Cria lista vazia
TLDE *inicializa(void);
//Criar no
TLDE *criar_no(int x);
//Insere no início
TLDE *ins_ini(TLDE *l, int x);
//Insere em ordem
TLDE *ins_ord(TLDE *l, int x);
//Insere antes de um no
TLDE *ins_antes(TLDE *no, TLDE *novo);
//Insere após um no
TLDE *ins_apos(TLDE *no, TLDE *novo);
//Copiar a lista
TLDE *copia(TLDE *l);
//Imprime a lista
void imprime(TLDE *l);
//Imprime a lista em ordem inversa
void imprime_rev(TLDE *l);
//Busca primeira vez de x
TLDE *busca(TLDE *l, int x);
//Liberação da lista
void libera(TLDE *l);
//Retira a primeira vez de x
TLDE *retira(TLDE *l, int x);





