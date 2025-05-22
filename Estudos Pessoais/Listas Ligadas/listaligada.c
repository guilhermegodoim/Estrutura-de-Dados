#include<stdio.h>
#include<stdlib.h>
#include<string.h>



// struct para representar o nó de uma lista ligada

typedef struct no{
    int dado;
    struct no * prox;
}no;

int lenght(no * top){
    no * atual = top;
    int n = 0;
    while(atual != NULL){
        n++;
        atual = atual ->prox;
    }
    return n;
}

int search(no * top, int x){
    no * atual = top;
    if (top == NULL){
        printf("A lista está vazia");
    }

    while (atual != NULL){
        if (atual->dado == x){
            return 1;
        }

        atual = atual -> prox;
    }

    return 0;
}

int insert_tail(no ** top, int x){
    
    no * novo = malloc(sizeof(no));
    if (novo == NULL){
        return 0;
    }

    novo -> dado = x;
    novo -> prox = NULL;

    if (*top == NULL){
        *top = novo;
    }else{
        no * p = *top;
        while (p->prox != NULL){
            p = p->prox;
        }
        p->prox = novo;
    }

    return 1;

}

int insert_head(no ** top, int x){
    no * novo = malloc(sizeof(no));
    if (novo == NULL){
        return 0;
    }

    novo->dado = x;
    novo->prox = *top;
    
    *top = novo;

    return 1;

}



void imprimir(no* top) {
    if (top != NULL){
        printf("%d ", top->dado);
        imprimir(top->prox);
    }

}

int remove_x(no ** top, int x){
    no * pp = NULL;
    no * p = *top;

    if (p==NULL){
        return 0;
    }

    while(p->dado != x){
        pp = p;
        p = p->prox;
    }

    if (pp == NULL){
        *top = p->prox;
        free(p);
    }else{
        pp->prox = p->prox;
        free(p);
    }
    return 1;
}

int main(){
    no * top = NULL;

    insert_tail(&top, 1);
    insert_tail(&top, 45);
    insert_tail(&top, 12);
    insert_head(&top, 77);
    insert_head(&top, 141);
    insert_tail(&top, 45);

    printf("%d\n", search(top, 34));
    printf("%d\n", search(top, 45));

    remove_x(&top, 45);
    printf("%d\n", search(top, 45));

    
    printf("A lista tem tamanho %d\n", lenght(top));

    printf("Lista: ");
    imprimir(top);
    printf("\n");


    return 0; 
}