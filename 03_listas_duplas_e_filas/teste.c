#include <limits.h>
#include "TF.h"

int menor(TF *f);

void ordena(TF *f){
  if(TF_vazia(f)) return;
  TF *aux = TF_inicializa();
  while(!TF_vazia(f))
    TF_insere(aux, TF_retira(f));
  while(!TF_vazia(aux)){
    int x = menor(aux);
    TF_insere(f, x);
  }
  TF_libera(aux);
}

int menor(TF *f){
  if(TF_vazia(f)) return INT_MAX;
  int resp = TF_retira(f), prox;
  TF *aux = TF_inicializa();
  while(!TF_vazia(f)){
    prox = TF_retira(f);
    if(resp > prox){
      TF_insere(aux, resp);
      resp = prox;
    }
    else TF_insere(aux, prox); 
  }
  while(!TF_vazia(aux))
    TF_insere(f, TF_retira(aux));
  TF_libera(aux);
  return resp;
}

int main(void){
  TF *f = TF_inicializa();
  printf("f:\n");
  int n;
  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    TF_insere(f, n);
  }
  TF_retira(f);
  TF_retira(f);  
  TF_insere(f, 300);
  TF_insere(f, 200);
  TF_insere(f, 100);
  TF_insere(f, 700);
  TF_insere(f, 900);
  TF_insere(f, 800);
  TF_insere(f, 500);
  TF_insere(f, 400);
  TF_imprime(f);
  printf("\n");
  ordena(f);
  TF_imprime(f);
  printf("\n");    
  TF_libera(f);
  return 0;
}
