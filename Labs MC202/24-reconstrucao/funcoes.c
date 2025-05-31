#include "funcoes.h"
#include<string.h>

ArvNo * novoNo (char c){
    ArvNo *p = malloc(sizeof(ArvNo));

    p->info = c;
    p->esq = NULL;
    p->dir = NULL;

    return p;
}

// acha onde ta o caractere na string em_ordem
int achar_pos(char *em_ordem, int comeco, int final, char c) {
    int i;
    for (i = comeco; i <= final; i++) {
        if (em_ordem[i] == c) 
            return i;
    }
    return -1; // não achou
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
    if (i_em > f_em) {
        return NULL;
    }
    
    char raiz_char = pre[*idx_pre];
    (*idx_pre)++;
    
    ArvNo *raiz = novoNo(raiz_char);
    
    if (i_em == f_em) 
        return raiz;
    
    int pos = achar_pos(em, i_em, f_em, raiz_char);
    
    // monta as subarvores recursivamente
    raiz->esq = construir(pre, em, i_em, pos - 1, idx_pre);
    
    raiz->dir = construir(pre, em, pos + 1, f_em, idx_pre);
    
    return raiz;
}

void imprimir_posordem(ArvNo *no) {
    if (no != NULL) {
        imprimir_posordem(no->esq);
        imprimir_posordem(no->dir);
        printf("%c", no->info);
    }
}

// imprime por nivel usando fila
void imprimir_largura(ArvNo *raiz) {
    if (raiz == NULL) 
        return;
    
    ArvNo *q[500]; // fila
    int frente = 0, tras = 0;
    
    q[tras++] = raiz;
    
    while (frente < tras) {
        ArvNo *atual = q[frente++];
        printf("%c", atual->info);
        
        if (atual->esq != NULL) {
            q[tras++] = atual->esq;
        }
        if (atual->dir != NULL) {
            q[tras++] = atual->dir;
        }
    }
}

void liberarArvore(ArvNo *no) {
    if (no != NULL) {
        liberarArvore(no->esq);
        liberarArvore(no->dir);
        free(no);
    }
}