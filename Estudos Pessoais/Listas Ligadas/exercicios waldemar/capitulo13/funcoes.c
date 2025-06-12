#include "funcoes.h"

int insere_final(no ** lista, int x){
    no * novo = malloc(sizeof(no));
    if (novo == NULL){
        return 0;
    }

    novo->dado = x;
    novo->prox = NULL;

    if (*lista == NULL){
        *lista = novo;
    }else{
        no * p = *lista;
        while (p->prox != NULL){
            p = p->prox;
        }
        p->prox = novo;
    }

    return 1;
}

void imprime_lista(no * lista){
    while (lista != NULL) {
        printf("%d ",lista->dado);
        lista = lista->prox;
    }
}