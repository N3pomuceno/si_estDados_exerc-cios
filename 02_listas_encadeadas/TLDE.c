#include"TLDE.h"

TLDE* inicializa(void){
  return NULL; 
}

TLDE *criar_no(int x){
  TLDE * novo = (TLDE*)malloc(sizeof(TLDE));
  novo->info = x;
  novo->prox = NULL;
  novo->ant = NULL;

  return novo;
}

//Insere no início
TLDE *ins_ini(TLDE *l, int x){
  TLDE * novo = (TLDE*)malloc(sizeof(TLDE));
  novo->info = x;
  novo->prox = l;
  novo->ant = NULL;
  if (l){
    l->ant = novo;  
  }
  return novo;
}

TLDE *ins_ord(TLDE *l, int x){
  TLDE * novo = (TLDE*)malloc(sizeof(TLDE));//criar o novo no
  novo->info = x;

  if (!l){//Insercao em lista vazia
      novo->prox = NULL;
      novo->ant = NULL;
      l = novo;
  }
  else if (l->info>x){//Insercao no inicio
      novo->prox = l;
      novo->ant = NULL;
      l->ant = novo;
      l = novo;
  }
  else{
      TLDE * ant = l; //Busca o ponto de insercao a partir do segundo no
      while ((ant->prox)&&(ant->prox->info<=x)){
          ant = ant->prox;
      }
 

      ins_apos(ant,novo);
      /*
      //ant->prox é o nó após novo (>x) ou é NULL
      novo->prox = ant->prox; 
      novo->ant = ant;

     
      if (ant->prox){//Insercao no meio. Existe um nó após novo
          ant->prox->ant = novo;
      }
      
      ant->prox = novo; // ant sempre existe
    */      

  }

  return l;

}

//Insere antes de um no
TLDE *ins_antes(TLDE *no, TLDE *novo){
    novo->prox = no;
    novo->ant = no->ant;
    if (no->ant){
        no->ant->prox = novo;
    }
    no->ant = novo;

    return novo;
    
}

//Insere após um no
TLDE *ins_apos(TLDE *no, TLDE *novo){
    novo->prox = no->prox;
    novo->ant = no;
    if (no->prox){
        no->prox->ant = novo;
    }
    no->prox = novo;

    return novo;
}

TLDE *copia(TLDE *l){
    if (!l) return NULL;

    // Criar a cabeça da lista e guarda no ultimo inserido (ult)
    TLDE *ult, *nova_l = ult = criar_no(l->info);

    // Percorre a lista original a partir do proximo elemento
    TLDE *p = l->prox;
    while (p){
        ins_apos(ult,criar_no(p->info));
        ult  = ult->prox;
        p = p->prox;
    }

    return nova_l;
}

///Imprime a lista
void imprime(TLDE *l){
  printf("[ ");
  TLDE *p = l;
  
  while(p){
    printf("%d ",p->info);
    p = p->prox;
  }
  
  printf("]\n");
}


///Imprime a lista
void imprime_rev(TLDE *l){
  printf("[ ");
  TLDE *p = l;
  
  while(p){
    printf("%d ",p->info);
    p = p->ant;
  }
  
  printf("]\n");
}


void libera(TLDE *l){
  TLDE * p = l;
  
  while (p){
    TLDE *temp = p;
    p = p->prox;
    free(temp);
  }
}


TLDE* busca(TLDE *l, int x){
  TLDE *resp = l;
  while ((resp)&&(resp->info != x)){
    resp = resp->prox; 
  }
  
  return resp;
  
}


TLDE *retira(TLDE *l, int x){

    TLDE * p = busca(l,x);

    if(!p) return l;
    if(p == l){ // remoçao do 1o
        l = l->prox;
    }
    else{ //remoção de um nó geral
        p->ant->prox = p->prox;
    }

    if(p->prox){
        p->prox->ant = p->ant;
    }

    free(p);
    return l;
}

