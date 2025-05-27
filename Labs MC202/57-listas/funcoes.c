#include "funcoes.h"

no * criar_lista(){
    return NULL;
}

int inserir(no ** lista, double x, int pos){
    // cria o novo nó
    no* novo = malloc(sizeof(no));
    if (novo == NULL){
        return 0;
    }
    
    novo->dado = x;
    novo->prox = NULL;

    // se a lista está vazia ou inserção na pos 0:
    if (*lista == NULL || pos == 0){
        novo->prox = *lista;
        *lista = novo;
        return 1;
    }
    
    // encontrar a posição de inserção:
    no * atual = *lista;
    int count = 0;

    while(atual->prox != NULL && count < pos - 1){
        atual = atual->prox;
        count++;
    }

    novo->prox = atual->prox;
    atual->prox = novo;

    return 1;
}

int remover(no ** lista, int pos){
    if (*lista == NULL || pos < 0){
        return 0; // lista vazia ou posição inválida
    }
    
    // remover o primeiro elemento (posição 0)
    if (pos == 0){
        no* temp = *lista;
        *lista = (*lista)->prox;
        free(temp);
        return 1;
    }
    
    // encontrar o nó anterior ao que será removido
    no* atual = *lista;
    int count = 0;
    
    while (atual->prox != NULL && count < pos - 1){
        atual = atual->prox;
        count++;
    }
    
    // se não existe nó na posição desejada
    if (atual->prox == NULL){
        return 0;
    }
    
    // remover o nó
    no* temp = atual->prox;
    atual->prox = temp->prox;
    free(temp);
    
    return 1;
}

void imprimir(no * lista){
    no * atual = lista;
    
    while(atual != NULL){
        printf("%.2f ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

// Função auxiliar para contar o tamanho da lista
int tamanho_lista(no* lista){
    int count = 0;
    no* atual = lista;
    while(atual != NULL){
        count++;
        atual = atual->prox;
    }
    return count;
}

void reverter(no ** lista, int inicio, int fim){
    if (*lista == NULL) return;
    
    int n = tamanho_lista(*lista);
    
    // verificar se os índices são válidos
    if (inicio < 0 || fim < 0 || inicio > fim || fim >= n) return;
    
    // se reverter apenas um elemento, não há nada a fazer
    if (inicio == fim) return;
    
    // criar um array temporário para armazenar os valores
    double* temp = malloc((fim - inicio + 1) * sizeof(double));
    if (temp == NULL) return;
    
    // percorrer até o início do trecho
    no* atual = *lista;
    for (int i = 0; i < inicio; i++){
        atual = atual->prox;
    }
    
    // copiar os valores para o array temporário
    for (int i = 0; i <= fim - inicio; i++){
        temp[i] = atual->dado;
        atual = atual->prox;
    }
    
    // voltar ao início do trecho
    atual = *lista;
    for (int i = 0; i < inicio; i++){
        atual = atual->prox;
    }
    
    // copiar os valores de volta em ordem reversa
    for (int i = fim - inicio; i >= 0; i--){
        atual->dado = temp[i];
        atual = atual->prox;
    }
    
    free(temp);
}

void mover(no ** lista, int inicio, int fim, int pos){
    if (*lista == NULL) return;
    
    int n = tamanho_lista(*lista);
    
    // verificar se os índices são válidos
    if (inicio < 0 || fim < 0 || inicio > fim || fim >= n || pos < 0) return;
    
    // se não há nada para mover
    if (inicio == fim && inicio == pos) return;
    
    // criar arrays temporários
    int tamanho_trecho = fim - inicio + 1;
    double* trecho = malloc(tamanho_trecho * sizeof(double));
    double* resto = malloc((n - tamanho_trecho) * sizeof(double));
    
    if (trecho == NULL || resto == NULL){
        free(trecho);
        free(resto);
        return;
    }
    
    // extrair o trecho a ser movido
    no* atual = *lista;
    int idx = 0;
    int idx_trecho = 0;
    int idx_resto = 0;
    
    while (atual != NULL){
        if (idx >= inicio && idx <= fim){
            trecho[idx_trecho++] = atual->dado;
        } else {
            resto[idx_resto++] = atual->dado;
        }
        atual = atual->prox;
        idx++;
    }
    
    // recriar a lista na nova ordem
    atual = *lista;
    idx = 0;
    int pos_ajustada = pos;
    
    // ajustar posição se ela for após o trecho removido
    if (pos > fim){
        pos_ajustada = pos - tamanho_trecho;
    }
    
    idx_resto = 0;
    idx_trecho = 0;
    
    while (atual != NULL){
        if (idx == pos_ajustada){
            // inserir o trecho aqui
            for (int i = 0; i < tamanho_trecho; i++){
                atual->dado = trecho[idx_trecho++];
                if (atual->prox != NULL) atual = atual->prox;
                else break;
                idx++;
            }
        }
        if (idx_resto < (n - tamanho_trecho)){
            atual->dado = resto[idx_resto++];
        }
        atual = atual->prox;
        idx++;
    }
    
    free(trecho);
    free(resto);
}

void terminar(){
    return;
}