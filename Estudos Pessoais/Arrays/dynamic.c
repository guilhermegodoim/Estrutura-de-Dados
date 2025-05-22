#include<stdio.h>
#include<stdlib.h>

/* vetor de inteiros */
typedef struct vetor{
    int * dados;
    int cap;
    int size;
}vetor;


vetor * criar_vetor(int capacidade){
    vetor * V;
    V = malloc(sizeof(struct vetor));
    V->dados = malloc(capacidade * sizeof(int));
    V->cap = capacidade;
    V->size = 0;

    return V;
}

/* insere x no final do vetor. se o vetor estiver cheio, dobra o tamanho do vetor.
se a inserção ocorrer com sucesso retorna 1. */

int inserir_final(vetor *vetor, int x) {
    // 1. Checa se o vetor está cheio
    if (vetor->size == vetor->cap) {
        int nova_cap = 2 * vetor->cap;
        int *novo_dados = realloc(vetor->dados, nova_cap * sizeof(int));

        if (novo_dados == NULL) {
            // Falha na realocação
            return 0;
        }

        vetor->dados = novo_dados;
        vetor->cap = nova_cap;
    }

    // 2. Insere o valor x no final do vetor
    vetor->dados[vetor->size] = x;

    // 3. Atualiza o tamanho
    vetor->size++;

    return 1; // sucesso
}

int remover(vetor * vetor,int x){
    vetor->size--;
    if ((vetor->size) > (vetor->cap)/4) {
        int nova_cap = (vetor->cap)/2;
        int * novos_dados = realloc(vetor->dados, nova_cap * sizeof(int));
    }



}






int main() {
    vetor *V = criar_vetor(2); // Começa com capacidade 2

    for (int i = 0; i < 10; i++) {
        inserir_final(V, i * 10); // Insere 0, 10, 20, ..., 90
    }

    for (int i = 0; i < V->size; i++) {
        printf("%d ", V->dados[i]);
    }
    printf("\n");

    free(V->dados);
    free(V);
    return 0;
}