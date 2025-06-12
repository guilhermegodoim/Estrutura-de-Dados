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
ArvNo* inserir(ArvNo *raiz, int x);
void percursoPostOrder(ArvNo* raiz);
void percursoPreOrder(ArvNo* raiz);
void percursoInOrder(ArvNo* raiz);
int altura(ArvNo* raiz);
ArvNo* remover_no(ArvNo* raiz, int x);
int eh_abb(ArvNo * raiz, int max, int min);
int sao_iguais(ArvNo * r1, ArvNo * r2);



#endif
