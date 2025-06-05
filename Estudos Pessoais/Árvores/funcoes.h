#ifndef FUNCOES_H
#define FUNCOES_H

#include<stdlib.h>
#include<stdio.h>

typedef struct arvno{
    int dado;
    struct arvno * left;
    struct arvno * right;
}ArvNo;

typedef struct tree{
    ArvNo * raiz;
}tree;



void imprimirArvore(ArvNo* raiz, int espaco);
tree * criar_arvore();
ArvNo * criar_no(int x);
int inserir(tree * T, int x);
void percursoPostOrder(ArvNo* raiz);
void percursoPreOrder(ArvNo* raiz);
void percursoInOrder(ArvNo* raiz);

#endif
