#include<stdio.h>

struct aluno{
  char nome[10];
  int mat;
  float notas[3];
  //float *notas;
  float cr;
};

void imprimir_aluno(struct aluno aln){
  
  printf("nome = %s\n",aln.nome);
  printf("mat = %d\n",aln.mat);
  printf("nota_0 = %f\n",aln.notas[0]);
  printf("nota_1 = %f\n",aln.notas[1]);
  printf("nota_2 = %f\n",aln.notas[2]);
  printf("cr = %f\n",aln.cr);
  

}

struct aluno criar_aluno(char *nome, int mat, 
                         float n0, float n1, float n2,
                         float cr){
                            
    struct aluno aluno;
    strcpy(aluno.nome,nome);
    aluno.mat = mat;
    //aluno.notas = (float*)malloc(3*sizeof(float));
    aluno.notas[0] = n0;
    aluno.notas[1] = n1;
    aluno.notas[2] = n2;
    aluno.cr = cr;
    
    return aluno;
}

struct aluno *criar_aluno_din(char *nome, int mat, 
                              float n0, float n1, float n2,
                              float cr){
                            
    struct aluno *aluno = (struct aluno*)malloc(sizeof(struct aluno));
    
    strcpy(aluno->nome,nome);
    aluno->mat = mat;
    //aluno->notas = (struct aluno*)malloc(sizefo(struct aluno));
    aluno->notas[0] = n0;
    aluno->notas[1] = n1;
    aluno->notas[2] = n2;
    aluno->cr = cr;
    
    return aluno;
}

void deslocar_aluno_din(struct aluno *aln){
    free(aln->notas);
    free(aln);
}
    

int main() {
  struct aluno aluno_prog_est , aluno_prog_est_copia;
  struct aluno * p_aluno_prog_est;
  
  
  /*aluno_prog_est.mat = 111111;
  
  aluno_prog_est.notas = (float*)malloc(3*sizeof(float));
  
  aluno_prog_est.notas[0] = 7.0f;
  aluno_prog_est.notas[1] = 8.0f;
  aluno_prog_est.notas[2] = 6.0f;
  
  aluno_prog_est.cr = 7.2f;
  strcpy(aluno_prog_est.nome,"carlos");
  */
  
  aluno_prog_est = criar_aluno("carlos", 111111, 7.0, 8.0, 6.0, 7.2);
  aluno_prog_est_copia = aluno_prog_est;
  
  p_aluno_prog_est = criar_aluno_din("carlos", 111111, 7.0, 8.0, 6.0, 7.2);
  
  imprimir_aluno(aluno_prog_est);
  imprimir_aluno(aluno_prog_est_copia);
  imprimir_aluno(*p_aluno_prog_est);
  
  //não esquecer de deslocar a área alocada dinamicamente
  free(p_aluno_prog_est);
  
  
  //free(aluno_prog_est.notas);
  
  
  return 0;
}