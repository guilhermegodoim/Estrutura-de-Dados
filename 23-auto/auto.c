#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int num;
    struct no * prox;
}no;

/*Insere o elemento no final da lista. retorna 1 se bem sucedido
e 0 se não houver memória*/

int inserir(no ** lista, int x){
    no* novo = malloc(sizeof(no));

    if (novo == NULL){
        return 0;
    }

    novo->num = x;
    novo->prox = NULL;

    if (*lista == NULL){
        *lista = novo;
    }

    else{
        no * p = *lista;
        while (p->prox != NULL){
            p = p->prox;
        }

    p->prox = novo;
    }

    return 1;
}

/* Insere o elemento no começo da lista. retorna 1 se bem sucedido
e 0 se não houver memória */
int inserir_começo(no ** lista, int x){
    no * novo = malloc(sizeof(no));
    if (novo = NULL){
        return 0;
    }

    novo->num = x;
    novo->prox = *lista;
    *lista = novo;

    return 1;

}
/* recebe o ponteiro para a lista ligada e um inteiro n.
monta a lista na forma (1,2,...,n) */

void montar_lista(no **lista, int n) {
    for (int i = 1; i <= n; i++) {
        inserir(lista, i);
    }
}

void imprimir(no *lista) {
    while (lista != NULL) {
        printf("%d ", lista->num);
        lista = lista->prox;
    }
    printf("\n");
}

// corrigir!!!!
void busca_mtf(no **lista, int chave, int *achou, int *n_comp_total) {
    int n_comp = 0;
    no *anterior = NULL;
    no *atual = *lista;

    while (atual != NULL) {
        n_comp++;
        if (atual->num == chave) {
            *achou = 1;
            *n_comp_total += n_comp;

            // Se já está no início, nada a fazer
            if (anterior != NULL) {
                // Remove da posição atual
                anterior->prox = atual->prox;

                // Move pro início
                atual->prox = *lista;
                *lista = atual;
            }

            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Não encontrou
    *achou = 0;
    *n_comp_total += n_comp;

    // Insere no começo
    inserir_começo(lista, chave);
}

void busca_sequencial(no *lista, int chave, int *achou, int *n_comp_total) {
    int n_comp = 0;
    no *atual = lista;

    while (atual != NULL) {
        n_comp++;
        if (atual->num == chave) {
            *achou = 1;
            *n_comp_total += n_comp;
            return;
        }
        atual = atual->prox;
    }

    // não encontrou
    *achou = 0;
    *n_comp_total += n_comp;
}






int main() {
    no *lista = NULL;
    int n;
    scanf("%d", &n);

    montar_lista(&lista, n);

    int k;
    scanf("%d", &k);

    int seq_busca[1000];
    for (int i = 0; i < k; i++) {
        scanf("%d", &seq_busca[i]);
    }

    int total_comp = 0;

    for (int i = 0; i < k; i++) {
        int achou;
        busca_sequencial(lista, seq_busca[i], &achou, &total_comp);
        if (!achou) {
            inserir(&lista, seq_busca[i]);
        }
    }

    printf("Sequencial: %d\n", total_comp);

    int total_comp_mtf = 0;
    for (int i = 0; i < k; i++) {
        int achou;
        busca_mtf(&lista, seq_busca[i], &achou, &total_comp_mtf);
    }
    printf("MTF: %d\n", total_comp_mtf);



    return 0;
}


