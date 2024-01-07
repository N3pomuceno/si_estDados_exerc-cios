


typedef struct heap{int   n;
                    int tam;
                    int  *p;
                    int tam_info;
                    void *info;}THeap;



void heap_descer(THeap *h, int i, int n);

void heap_subir(THeap *h, int i);

THeap * heap_constroi_heap_maximo(int *p, void *info, int tam_info, int n);

THeap * heap_liberar(THeap *h);

void heap_imprime(THeap *h);

int heap_insere(THeap *h, int novo, void *nova_info);

int heap_exclui(THeap *h, int *elem, void *info);

void heap_sort(int *v, void *info, int tam_info, int n);