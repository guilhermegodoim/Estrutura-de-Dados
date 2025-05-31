#include<stdio.h>
#include<string.h>
#include "funcoes.h"

int main() {
    char pre_ordem[100];
    char em_ordem[100];

    while(scanf("%s %s", pre_ordem, em_ordem) == 2){
        int tamanho = strlen(pre_ordem);
        int idx = 0;
    
        ArvNo * arvore = construir(pre_ordem, em_ordem, 0, tamanho-1, &idx);
    
        imprimir_posordem(arvore);
        printf(" ");
        imprimir_largura(arvore);
        printf("\n");
        
        liberarArvore(arvore);
    }

    return 0;
}