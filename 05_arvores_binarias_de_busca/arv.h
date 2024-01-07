#ifndef ARV_H
    #define ARV_H
    #include"arvbin.h" 
    #include"abb.h"

    typedef struct NoArv{
        int chave;
        int n_filhos;
        struct NoArv **filhos; // struct NoArv * filhos[N];
    }TArv;

    typedef struct{
        int n_arvores;
        TArv* arvores;
    }TFloresta;

    typedef struct noArvFEID{
        int chave;
        struct noArvFEID * fe;
        struct noArvFEID * id;
    }TArvFEID;

    TArv * arv_criar(int chave, int n, ...);
    void arv_imprimir(TArv* arv);
    void arv_imprimir2(TArv* arv);

    TArvFEID * arv_converter_gen_feid(TArv *arv); // converte um árvore generica em filho-esq-irmao-dir
    TArvFEID * arv_converter_arvbin_feid(TArvBin * arv);
    TArvFEID * arv_converter_abb_feid(TABB * arv);
    TArvFEID * arv_criar_feid(char * rep_paren, int *pos);
    void arv_feid_imprimir(TArvFEID *raiz);
    void arv_converter_rep_parentizada(TArvFEID *raiz, char *s);
    int arv_checar_arv_feid_arvbin(TArvFEID *raiz);

#endif