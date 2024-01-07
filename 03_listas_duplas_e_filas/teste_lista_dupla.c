#include<stdio.h>
#include<stdlib.h>

typedef struct lde{int info;
                   struct lde * ant; 
                   struct lde * prox;
                  }TLDE;
                  
          
TLDE *inicializa(void);

TLDE *criar_no(int x);

//Insere no início
TLDE *ins_ini(TLDE *l, int x);

//Insere antes de um no
TLDE *ins_antes(TLDE *no, TLDE *novo);

//Insere após um no
TLDE *ins_apos(TLDE *no, TLDE *novo);

//Imprime a lista
void imprime(TLDE *l);

//Imprime lista ao contrario
void imprime_reverso(TLDE *l);

//Busca primeira vez de x
TLDE* busca(TLDE *l, int x);

//Liberação da lista
void libera(TLDE *l);

//Retira a primeira vez de x
TLDE* retira(TLDE *l, int x);                    

TLDE *inicializa(void){
  return NULL;
}

TLDE *criar_no(int x){
  TLDE * novo = (TLDE*)malloc(sizeof(TLDE));
  novo->info = x;
  novo->ant = NULL;
  novo->prox = NULL;
  return novo;
}

TLDE *ins_ini(TLDE *l, int x){
  TLDE * novo = (TLDE*)malloc(sizeof(TLDE));
  novo->info = x;
  novo->ant = NULL;
  novo->prox = l;
  if (l){
    l->ant = novo;
  }
  
  return novo;
  
}




void imprime(TLDE *l){
  TLDE *p = l;
  printf("\n[");
  while (p){
    printf("%d",p->info);
    p = p->prox;
  }
  printf("]\n");
}

void imprime_reverso(TLDE *l){
  
  TLDE *p = l;
  
  if (!p) return;
  
  //Busca o ultimo no
  while (p->prox){
    p = p->prox;   
  }
  
  printf("\n[");
  while (p){
    printf("%d",p->info);
    p = p->ant;
  }
  printf("]\n");
}

TLDE *busca(TLDE *l, int x){
  TLDE *p = l;
  while ((p!=NULL)&&(p->info!=x)){
    p = p->prox;
  }
  return p;
}


//Liberação da lista
void libera(TLDE *l){
 TLDE *p = l;
 while (p){
  TLDE *temp = p;
  p = p->prox;
  free(temp);
 }
}

//Retira a primeira vez de x
TLDE* retira(TLDE *l, int x){
  TLDE * p = busca(l,x); //busca no no que contem x
  
  if (!p){ // se a busca falhou
    return l; //retonar l;
  }
  else if (p == l){ // se o no encontrado for igual ao primeiro
    l = l->prox;  //atualizar o inicio da lista
  }
  else{
    p->ant->prox = p->prox; // Fazer o antecessor de p apontar para o 
                            // sucessor de p
  }
  
  if (p->prox){ // caso p tenha um sucessor
    p->prox->ant = p->ant; //fazer o sucessor de p ter como antecessor 
                           //o antecessor de p
  }
  
  free(p);
  
  return l;
  
}

//Insere antes de um no
TLDE *ins_antes(TLDE *no, TLDE *novo){
  novo->prox = no; //(1)
  novo->ant = no->ant; //(2)
  if (no->ant){ 
    no->ant->prox = novo; //(3)
  }
  no->ant = novo; //(4)
  
  return novo;
  
}


//Insere após um no
//Insere após um no
TLDE *ins_apos(TLDE *no, TLDE *novo){
  novo->ant = no;
  novo->prox = no->prox;
  if (no->prox){
    no->prox->ant = novo;
  }
  no->prox = novo;
  
  return novo;
}

TLDE *copia(TLDE *l){
  if (!l) return l;
  
  TLDE * nova_l, *ult;
  nova_l = ult = criar_no(l->info); // copiar a cabeca da lista
  
  // copiar os demais nos
  TLDE *p = l->prox;
  while (p){
    ins_apos(ult,criar_no(p->info));
    ult = ult->prox;
    p = p->prox;
  }
  return nova_l;
}

int main() {
  
  TLDE * ld = inicializa();
  
  for (int i=5;i>=0;i--){
    ld = ins_ini(ld,i);
  }
  
  TLDE * p = busca(ld,3);
  
  if (p){
    printf("p:%d",p->info);
    if (p->ant)
      printf("ant(p):%d",p->ant->info);
    if (p->prox)
      printf("suc(p):%d",p->prox->info);
  }
  else{
    printf("No inexistente\n"); 
  }

  ld = retira(ld,3);
  ld = retira(ld,5);
  ld = retira(ld,0);
  
  ld = ins_antes(busca(ld,1),criar_no(0));
  
  imprime(ld);
  imprime_reverso(ld);
  libera(ld);
  
  return 0;
}