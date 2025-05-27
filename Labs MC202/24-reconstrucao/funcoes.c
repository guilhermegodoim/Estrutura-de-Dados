#include "funcoes.h"

ArvNo * novoNo (char c){
    ArvNo *p = malloc(sizeof(ArvNo));

    p->info = c;
    p->esq = NULL;
    p->dir = NULL;

    return p;
}

/* 
o algoritmo p/ construir a árvore funciona da seguinte forma:
1) o primeiro caractere da string pre_ordem é a raíz da arvore
2) identificar esse caractere na string em_ordem
3) tudo a esquerda dele na string é a SAE e tudo a direita é a SAD
4) repetir recursivamente para as subarvores 

os índices servem para determinar qual subárvore estamos trabalhando (da string em_ordem)

a função recebe também um ponteiro para o índice atual no vetor da pré ordem
*/
ArvNo * construir(char * pre, char * em, int i_em, int f_em, int * idx_pre){
    
}


