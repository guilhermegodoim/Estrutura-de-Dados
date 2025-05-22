#include<stdio.h>
#include<stdlib.h>


struct no{
    int dado;
    struct no* prox;
};

typedef struct no no;


int inserir_cabeca(no **lista, int x){
    no* novo = malloc(sizeof(no));
    novo->dado = x;
    novo->prox = *lista;
    *lista = novo;

    return 1;
}

int inserir_final(no **lista, int x){ // REVISAR
    no* novo = malloc(sizeof(no));
    novo->dado = x;
    novo->prox = NULL;

    if (*lista = NULL){
        *lista = novo;
    } else{
        no* p = *lista;
        while(p->prox != NULL){
            p = p->prox;
        }

        p->prox = novo;

    }

}

void imprimir(no* lista) {
    if (lista != NULL){
        printf("%d ", lista->dado);
        imprimir(lista->prox);
    }

}

int main(){
    no* lista = NULL;
    
    inserir_cabeca(&lista, 5);
    inserir_cabeca(&lista, 2);
    inserir_cabeca(&lista, 67);
    inserir_cabeca(&lista, 12);        // teoricamente a lista está assim: 5, 2, 67, 12

    inserir_final(&lista, 37);
    inserir_final(&lista, 72); 
    
    imprimir(lista);


}


