#ifndef FUNCOES_H
#define FUNCOES_H

#include<stdio.h>
#include<stdlib.h>


typedef struct no{
    int dado;
    struct no * prox;
}no;

int insere_final(no ** lista, int x);

void imprime_lista(no * lista);


#endif