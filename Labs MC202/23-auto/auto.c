#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int num;
    int contador;  
    struct no *prox;
} no;

no* criar_no(int valor) {
    no *novo = malloc(sizeof(no));
    if (novo == NULL) return NULL;
    novo->num = valor;
    novo->contador = 0;
    novo->prox = NULL;
    return novo;
}

int inserir_fim(no **lista, int x) {
    no *novo = criar_no(x);
    if (novo == NULL) {
        return 0;
    }
    
    if (*lista == NULL) {
        *lista = novo;
    } else {
        no *p = *lista;
        while (p->prox != NULL) {
            p = p->prox;
        }
        p->prox = novo;
    }
    return 1;
}

int inserir_inicio(no **lista, int x) {
    no *novo = criar_no(x);
    if (novo == NULL) {
        return 0;
    }
    
    novo->prox = *lista;
    *lista = novo;
    return 1;
}

// monta lista no formato (1, 2, ..., n)
void montar_lista(no **lista, int n) {
    // limpa a lista para evitar que, caso haja alteração nela ao usar uma função de busca, a próxima não itere sobre a lista alterada
    while (*lista != NULL) {
        no *temp = *lista;
        *lista = (*lista)->prox;
        free(temp);
    }
    
    for (int i = 1; i <= n; i++) {
        inserir_fim(lista, i);
    }
}

int busca_sequencial(no **lista, int chave) {
    int comparacoes = 0;
    no *atual = *lista;
    
    while (atual != NULL) {
        comparacoes++;
        if (atual->num == chave) {
            return comparacoes;
        }
        atual = atual->prox;
    }
    
    inserir_fim(lista, chave);
    return comparacoes;
}

// quando o elemento é encontrado ele é movido para o início da lista
int busca_mtf(no **lista, int chave) {
    int comparacoes = 0;
    no *anterior = NULL;
    no *atual = *lista;
    
    while (atual != NULL) {
        comparacoes++;
        if (atual->num == chave) {
            if (anterior != NULL) {
                anterior->prox = atual->prox;
                atual->prox = *lista;
                *lista = atual;
            }
            return comparacoes;
        }
        anterior = atual;
        atual = atual->prox;
    }
    
    inserir_inicio(lista, chave);
    return comparacoes;
}

// quando o elementp é encontrado, ele troca de lugar com o seu antecessor
int busca_transpose(no **lista, int chave) {
    int comparacoes = 0;
    no *anterior_anterior = NULL;
    no *anterior = NULL;
    no *atual = *lista;
    
    while (atual != NULL) {
        comparacoes++;
        if (atual->num == chave) {
            if (anterior != NULL) {
                if (anterior_anterior != NULL) {
                    anterior_anterior->prox = atual;
                } else {
                    *lista = atual;
                }
                anterior->prox = atual->prox;
                atual->prox = anterior;
            }
            return comparacoes;
        }
        anterior_anterior = anterior;
        anterior = atual;
        atual = atual->prox;
    }
    
    inserir_inicio(lista, chave);
    return comparacoes;
}

// mantém um contador de acesso para cada elemento
int busca_count(no **lista, int chave) {
    int comparacoes = 0;
    no *anterior = NULL;
    no *atual = *lista;
    
    while (atual != NULL) {
        comparacoes++;
        if (atual->num == chave) {
            atual->contador++;
            
            if (anterior != NULL) {
                anterior->prox = atual->prox;
            } else {
                *lista = atual->prox;
            }
            
            no *pos_anterior = NULL;
            no *pos_atual = *lista;
            
            while (pos_atual != NULL && pos_atual->contador > atual->contador) {
                pos_anterior = pos_atual;
                pos_atual = pos_atual->prox;
            }
            
            if (pos_anterior == NULL) {
                atual->prox = *lista;
                *lista = atual;
            } else {
                atual->prox = pos_anterior->prox;
                pos_anterior->prox = atual;
            }
            
            return comparacoes;
        }
        anterior = atual;
        atual = atual->prox;
    }
    
    no *novo = criar_no(chave);
    if (novo == NULL) return comparacoes;
    
    novo->contador = 1;
    
    no *pos_anterior = NULL;
    no *pos_atual = *lista;
    
    while (pos_atual != NULL && pos_atual->contador >= 1) {
        pos_anterior = pos_atual;
        pos_atual = pos_atual->prox;
    }
    
    if (pos_anterior == NULL) {
        novo->prox = *lista;
        *lista = novo;
    } else {
        novo->prox = pos_anterior->prox;
        pos_anterior->prox = novo;
    }
    
    return comparacoes;
}

int main() {
    int n, r;
    scanf("%d", &n);
    scanf("%d", &r);
    
    // alocar dinamicamente (tava dando problema usar arrays fixas)
    int *buscas = malloc(r * sizeof(int));
    for (int i = 0; i < r; i++) {
        scanf("%d", &buscas[i]);
    }
    
    // busca sequencial 
    no *lista = NULL;
    montar_lista(&lista, n);
    int total_seq = 0;
    for (int i = 0; i < r; i++) {
        total_seq += busca_sequencial(&lista, buscas[i]);
    }
    printf("Sequencial: %d\n", total_seq);
    
    // mtf
    montar_lista(&lista, n);
    int total_mtf = 0;
    for (int i = 0; i < r; i++) {
        total_mtf += busca_mtf(&lista, buscas[i]);
    }
    printf("MTF: %d\n", total_mtf);
    
    // transpose
    montar_lista(&lista, n);
    int total_transpose = 0;
    for (int i = 0; i < r; i++) {
        total_transpose += busca_transpose(&lista, buscas[i]);
    }
    printf("Transpose: %d\n", total_transpose);
    
    // count
    montar_lista(&lista, n);
    int total_count = 0;
    for (int i = 0; i < r; i++) {
        total_count += busca_count(&lista, buscas[i]);
    }
    printf("Count: %d\n", total_count);
    
    while (lista != NULL) {
        no *temp = lista;
        lista = lista->prox;
        free(temp);
    }
    free(buscas);
    
    return 0;
}