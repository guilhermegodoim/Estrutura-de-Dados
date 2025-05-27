#include<stdio.h>
#include<string.h>
#include "funcoes.h"

int main() {
    char pre_ordem[100];
    char em_ordem[100];

    while(1){
        scanf("%s %s", pre_ordem, em_ordem);
        printf("%s %s", pre_ordem, em_ordem);

        int n = strlen(pre_ordem);
        int idx_pre = 0;
    
        ArvNo * arvore = construir(pre_ordem, em_ordem);
    
        imprimir_posordem(arvore);
        imprimir_largura(arvore);


    
    
    }

    return 0;
}
