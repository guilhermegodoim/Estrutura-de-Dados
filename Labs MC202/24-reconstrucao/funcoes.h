#ifndef FUNCOES_H
#define FUNCOES_H

#include<stdlib.h>
#include<stdio.h>

typedef struct arvno{
    char info;
    struct arvno *esq;
    struct arvno *dir;
}ArvNo;

ArvNo * novoNo(char c);
ArvNo * construir(char * pre, char * em, int i_em, int f_em, int * idx_pre);
void imprimir_posordem(ArvNo *no);
void imprimir_largura(ArvNo *raiz);
void liberarArvore(ArvNo *no);
int achar_pos(char *em_ordem, int comeco, int final, char c);

#endif