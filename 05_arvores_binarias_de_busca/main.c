#include <stdio.h>
#include <stdlib.h>
#include"arvbin.h"
#include"arv.h"
#include"abb.h"

/*
#define clrscr() system("cls");

char obter_tecla(){
    char s[50];
    gets(s);
    return s[0];
}

void montar_menu_arvore_binaria(){
    char opcao;
    int chave;
    TArvBin * arv = arvbin_criar_vazia();

    do{
        clrscr();
        arvbin_imprimir(arv);
        printf("Inserir - <i>\n");
        printf("Remover - <d>\n");
        printf("Buscar - (b)\n");
        printf("Sair   - <x>\n");

        opcao = obter_tecla();

        switch(opcao){
            case 'i':
                printf("Digite chave\n");
                scanf("%d",&chave;
                getchar();
                arv = arvbin_inserir_abb(arv,chave);
                arvbin_imprimir(arv);
                printf("Pressione espaco para continuar...\n");
                while (obter_tecla()!=32);
            break;
            case 'd':
                printf("Digite chave\n");
                scanf("%d",&chave);
                getchar();
                arv = arvbin_remover_abb(arv,chave);
                arvbin_imprimir(arv);
                printf("Pressione espaco para continuar...\n");
                while (obter_tecla()!=32);
            break;

            case 'b':
                printf("Digite chave\n");
                scanf("%d",&chave);
                getchar();
                if ((pt=arvbin_buscar(arv,chave)))
                    printf("No no endereco %d com chave = %d\n",pt,pt->chave);
                else
                    printf("No com chave = %d nao encontrado \n",chave);
                printf("Pressione espaco para continuar...\n");
                while (obter_tecla()!=32);
            break;


            default:
            break;
        }
    }while (opcao!='x');

    arv = arvbin_desalocar(arv);
}

*/

void teste_arvore_binaria(){
    int chave;
    TArvBin *arv = NULL, *pt = NULL, *sub_arv = NULL;


    arv = arvbin_criar(9,
                         arvbin_criar(5,
                                       arvbin_criar(3,
                                                     arvbin_criar(2,NULL,NULL),
                                                     arvbin_criar(4,NULL,NULL)
                                                    ),
                                       arvbin_criar(7,
                                                     arvbin_criar(6,NULL,NULL),
                                                     arvbin_criar(8,NULL,NULL)
                                                     )
                                       ),
                         arvbin_criar(20,
                                       arvbin_criar(15,
                                                     arvbin_criar(12,NULL,NULL),
                                                     arvbin_criar(17,NULL,NULL)
                                                    ),
                                       arvbin_criar(25,
                                                     NULL,
                                                     NULL
                                                     )
                                       )
                         );

    arvbin_imprimir(arv);
   
    printf("Teste de busca\n");

    printf("Subarvore com raiz em 5\n");

    arvbin_imprimir(arvbin_buscar(arv,5));

    printf("Subarvore com raiz em 7\n");
 
    arvbin_imprimir(arvbin_buscar(arv,7));

    printf("---------------------------------------------------------------\n");

    printf("Percurso em ordem simetrica\n");
    arvbin_ordem_simetrica(arv);

    printf("\n---------------------------------------------------------------\n");

    printf("Percurso em pre-ordem\n");
    arvbin_pre_ordem(arv);


    printf("\n---------------------------------------------------------------\n");

    printf("Percurso em pos-ordem\n");
    arvbin_pos_ordem(arv);


    printf("\n---------------------------------------------------------------\n");

    printf("Arvore desalocada");

    arv = arvbin_desalocar(arv);


}

void teste_abb(){

    TABB * abb = abb_criar_vazia();
    TABB * abb_sub_arv = NULL;

    abb = abb_inserir(abb,5);
    abb = abb_inserir(abb,3);
    abb = abb_inserir(abb,7);
    abb = abb_inserir(abb,1);
    abb = abb_inserir(abb,2);
    abb = abb_inserir(abb,4);
    abb = abb_inserir(abb,6);
    abb = abb_inserir(abb,8);
    abb = abb_inserir(abb,15);
    abb = abb_inserir(abb,10);
    abb = abb_inserir(abb,13);

    abb_imprimir(abb);


    printf("Subarvore do no %d\n",3);
    abb_sub_arv = abb_buscar(abb,3);
    abb_imprimir(abb_sub_arv);


    printf("---------------------------------------------------------------\n");
    printf("Delete node 5\n");

    abb = abb_remover(abb,5);
    abb_imprimir(abb);


    printf("Delete node 4\n");
    abb = abb_remover(abb,4);
    abb_imprimir(abb);
    
    abb = abb_desalocar(abb);

    printf("Criacao de arvore balanceada a partir de vetor ordenado\n");

    int v[15] = {2,3,4,6,9,10,15,17,19,20,22,25,30,32,35};
    abb = abb_criar_chaves(v,0,14);

    abb_imprimir(abb);

    for (int i=0;i<15;i++){
        TABB * suc = abb_sucessor(abb,v[i]);
        if (suc){
            printf("sucessor %d = %d\n",v[i],suc->chave);
        }
        else{
            printf("sucessor %d = vazio\n",v[i]);
        }
    }
    

    abb = abb_desalocar(abb);
}

void teste_arvore_filho_esq_irmao_dir(){

    printf("---------------------------------------------------------------\n");

   /* TNoArv * arv_gen = arv_criar(0,4,
                                 arv_criar(6,3,
                                           arv_criar(1,0),
                                           arv_criar(9,0),
                                           arv_criar(17,1,
                                                     arv_criar(23,0)
                                                    )
                                           ),
                                 arv_criar(7,0),
                                 arv_criar(8,4,
                                           arv_criar(4,0),
                                           arv_criar(10,0),
                                           arv_criar(12,0),
                                           arv_criar(0,0)
                                           ),
                                 arv_criar(7,2,
                                           arv_criar(12,0),
                                           arv_criar(3,0)
                                           )
                                );


    arv_imprimir2(arv_gen);


    TArvFEID * arv_feid = arv_converter_gen_feid(arv_gen);

    printf("\n");

    arv_feid_imprimir(arv_feid);
*/
    
    int pos = 0;
    TArvFEID * arv_feid = arv_criar_feid("(14((6((13)(5)))(18((71)(9)))))",&pos);
    printf("\n");

    arv_feid_imprimir(arv_feid);
    char s[60];
    arv_converter_rep_parentizada(arv_feid,s);
    printf("%s",s);


}

void teste_converte_arvbin_feid(){
    TArvBin * arv = arvbin_criar(5,arvbin_criar(6,
                                                arvbin_criar(2,NULL,NULL),
                                                arvbin_criar(3,NULL,NULL)
                                                ),
                                   arvbin_criar(7,NULL,NULL)
                                );
    arvbin_imprimir(arv);
    TArvFEID *arv_feid = arv_converter_arvbin_feid(arv);
    arv_feid_imprimir(arv_feid);

}

void teste_converte_abb_feid(){
    TABB * abb = abb_criar_vazia();
    int chave;
    do{
        scanf("%d",&chave);
        if (chave!=-1){
            abb = abb_inserir(abb,chave);
        }

    }while(chave!=-1);



    abb_imprimir(abb);
    TArvFEID *arv_feid = arv_converter_abb_feid(abb);
    arv_feid_imprimir(arv_feid);
    char s[50];
    arv_converter_rep_parentizada(arv_feid, s);
    printf("%s\n",s);

    printf("%d",arv_checar_arv_feid_arvbin(arv_feid));

}

int main()
{
    //teste_arvore_binaria();
    teste_abb();
    //teste_arvore_filho_esq_irmao_dir();
    //teste_converte_abb_feid();
}
