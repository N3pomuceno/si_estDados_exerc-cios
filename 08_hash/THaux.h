#ifndef THAUX
#define THAUX

#define EPS 1e-6

// Callbacks padrao para comparacao e impressao de tipos basicos
int TH_comparar_char(void *a, void *b);
void TH_imprimir_char(void *a);
int TH_comparar_int(void *a, void *b);
void TH_imprimir_int(void *a);
int TH_comparar_float(void *a, void *b);
void TH_imprimir_float(float *a);

//Obs.: TH_comparar_string e  TH_imprimir_string requerem que as cadeias terminem com '\0' 
int TH_comparar_string(void *a, void *b);
void TH_imprimir_string(void *a);
#endif