#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"THaux.h"



int TH_comparar_char(void *a, void *b){
    char *_a = (char*)a;
    char *_b = (char*)b;
    
    if (*_a==*_b){
        return 0;
    }
    else if(*_a<*_b){
        return -1;
    }
    else{
        return 1;
    }
}

void TH_imprimir_char(void *a){
    char *_a = (char*)a;
    printf("%c",*_a);
}

int TH_comparar_int(void *a, void *b){
    int *_a = (int*)a;
    int *_b = (int*)b;
    
    if (*_a==*_b){
        return 0;
    }
    else if(*_a<*_b){
        return -1;
    }
    else{
        return 1;
    }
}

void TH_imprimir_int(void *a){
    int *_a = (int*)a;
    printf("%d",*_a);
}




int TH_comparar_float(void *a, void *b){
    float *_a = (float*)a;
    float *_b = (float*)b;
    if (abs(*_a-*_b)<EPS){
        return 0;
    }
    else if (_a<_b){
        return -1;
    }
    else{
        return 1;
    };
}

void TH_imprimir_float(float *a){
    float *_a = (float*)a;
    printf("%f",*_a);
}


int TH_comparar_string(void *a, void *b){
    char *_a = (char*)a;
    char *_b = (char*)b;
    int ret = strcmp(_a,_b); 
    return ret;
}

void TH_imprimir_string(void *a){
    char *_a = (char*)a;
    int len = strlen(a);
    printf("%s",_a);
}
