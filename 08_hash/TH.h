#ifndef TH
#define TH



typedef struct par{
                   void *chave;
                   void *valor;
                   int status;}TPar;

typedef struct tab_hash{
    int tam_chave;
    int tam_valor;
    int n;
    int ocupacao;
    TPar **elem;
    int (*comp)(void*a,void*b);
    void (*imprimir_chave)(void*a);
    void (*imprimir_valor)(void*a);
}TTabHash;



//Criar uma tabela hash que armazena pares (chave,valor)
//Para criacao e necessario passar o tamanho do tipo da chave e o tamanho do tipo do valor
TTabHash * TH_criar(int n, int tam_chave, int tam_valor);

//Permite cadastrar uma funcao na tabela hash para comparacao entre duas chaves a e b de tipos 
//arbitrarios
void TH_set_callback_comparar(TTabHash *t,int (*comp)(void*a,void*b));

//Permite cadastrar uma funcao para imprimir chaves de qualquer tipo
void TH_set_callback_imprimir_chave(TTabHash *t,void (*imprimir)(void*a));

//Permite cadastrar uma funcao para imprimir valores de qualquer tipo
void TH_set_callback_imprimir_valor(TTabHash *t,void (*imprimir)(void*a));

//Insere para chave e valor. Deve ser usado o endereco da variavel que contem a chave
//e o endereco da variavel que contem o valor
TPar * TH_inserir(TTabHash * t, void *chave, void *valor);

//Busca um par (chave,valor) dada a chave
TPar * TH_buscar(TTabHash *t, void *chave);

//Remove e retorna um elemento da tabela hash
TPar * TH_remover(TTabHash *t, void *chave); 

//Libera a tabela hash criada
TTabHash * TH_liberar(TTabHash *t);

//Imprime a tabela hash
void TH_imprimir(TTabHash *t);


//TPar * TH_inserir(TTabHash * t, void *chave, void *valor, int (*comp)(void *a, void*b));
//TPar * TH_buscar(TTabHash *t, void *chave,  int (*comp)(void *a, void *b));
//void TH_imprimir(TTabHash *t,void (*imprimir_chave)(void*chave),void (*imprimir_valor)(void*valor));

#endif