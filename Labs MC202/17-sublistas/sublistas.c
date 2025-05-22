#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct no *p_no;

typedef struct no {
    int valor;
    p_no prox;
    } No;

void imprimir_lista(p_no lista) {
    for (p_no atual = lista; atual != NULL; atual = atual->prox) {
        printf("%d ", atual->valor);
    }
    printf("\n");
}
    

void inserir_final(p_no *lista, int valor) {
    p_no novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;

    if (*lista == NULL) {
        *lista = novo;
    } else {
        p_no atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

void extrair_e_inserir(char *entrada, p_no *lista) {
    char *inicio = strchr(entrada, '{');
    char *fim = strchr(entrada, '}');
    if (!inicio || !fim) return;

    inicio++; // pula o '{'

    char numeros[1000];
    strncpy(numeros, inicio, fim - inicio);
    numeros[fim - inicio] = '\0';

    char *token = strtok(numeros, ", ");
    while (token != NULL) {
        inserir_final(lista, atoi(token));
        token = strtok(NULL, ", ");
    }
}

void imprimir_lista_formatada(char *nome, p_no lista) {
    printf("%s = {", nome);
    for (p_no atual = lista; atual != NULL; atual = atual->prox) {
        printf("%d", atual->valor);
        if (atual->prox != NULL) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(){
    char entrada[1000];
    p_no lista;
    lista = NULL;

    fgets(entrada, sizeof(entrada), stdin);

    extrair_e_inserir(entrada, &lista);

    inserir_final(&lista, 3);
    
    imprimir_lista_formatada("A", lista);

    return 0;


}