#include"TLDE.h"

int main() {
  
  TLDE *ld = inicializa();
  
  for (int i = 9; i>=0; i--){
    ld = ins_ini(ld,i);
  }

  printf("Lista original\n");
  imprime(ld);


  for (int i = 0; i<9; i+=2){
      ld = retira(ld,i);
  }

  printf("Lista sem os pares\n");
  imprime(ld);
  


  for (int i = 0; i<=10; i+=2){
    ld = ins_ord(ld,i);
  }
  
  printf("Lista com pares re-inseridos\n");
  imprime(ld);
  

  
  TLDE *no;
  
  if ( no = busca(ld,10)){
    printf("No %d encontrado\n",no->info);
    TLDE * final = ins_apos(no,criar_no(12));
    ld = ins_antes(ld,criar_no(-1));
    
    printf("Lista após insercao do -1 e 12 \n");
    imprime(ld);
    
    printf("Lista impressa ao inverso após insercao do -1 e 12 \n");
    imprime_rev(final);

    ins_apos(final->ant,criar_no(11));
    printf("Lista apos insercao do 11 \n");
    imprime(ld);

    
  }
  else{
    printf("No nao achado\n");
  }

  TLDE *copia_l = copia(ld);

  imprime(copia_l);
  
  
  libera(ld);
  
  return 0;
}