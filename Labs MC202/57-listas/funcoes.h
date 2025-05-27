#ifndef FUNCOES_H
#define FUNCOES_H

#include<stdlib.h>
#include<stdio.h>

typedef struct no{
    double dado;
    struct no * prox;
}no;

no * criar_lista();

int inserir(no ** lista, double x, int pos);

int remover(no ** lista,int pos);

void imprimir(no * lista);

void reverter(no ** lista, int inicio, int fim);

void mover(no ** lista, int inicio, int fim, int pos);

void terminar();

#endif
