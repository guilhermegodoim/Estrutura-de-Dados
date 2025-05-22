#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bloco {
    int livre;   // 1 se livre, 0 se ocupado
    int tamanho; // tamanho em Kb
    char nome[11]; // nome do arquivo (se ocupado)
    struct bloco* prox;
} Bloco;

/*a ideia aqui é converter todos os tamanhos dos arquivos e do disco para a menor unidade usada
(nesse caso, o Kb) antes de efetuar as operações, já que um disco por exemplo com tamanho 5gb pode receber
um arquivo em Mb ou Kb*/


int converter_para_kb(char* str) {
    int valor;
    char unidade[3];
    sscanf(str, "%d%2s", &valor, unidade);

    if (strcmp(unidade, "Kb") == 0) return valor;
    if (strcmp(unidade, "Mb") == 0) return valor * 1024;
    if (strcmp(unidade, "Gb") == 0) return valor * 1024 * 1024;
    return 0;
}



int inserir(Bloco** disco, char* nome, int tamanho) {
    Bloco* atual = *disco;
    Bloco* melhor = NULL;

    while (atual) {
        if (atual->livre && atual->tamanho >= tamanho) {
            if (!melhor || atual->tamanho < melhor->tamanho)
                melhor = atual;
        }
        atual = atual->prox;
    }

    if (!melhor) return 0; // precisa otimizar

    if (melhor->tamanho == tamanho) {
        melhor->livre = 0;
        strcpy(melhor->nome, nome);
    } else {
        Bloco* novo = malloc(sizeof(Bloco));
        novo->livre = 1;
        novo->tamanho = melhor->tamanho - tamanho;
        novo->prox = melhor->prox;

        melhor->livre = 0;
        melhor->tamanho = tamanho;
        strcpy(melhor->nome, nome);
        melhor->prox = novo;
    }

    return 1;
}

void remover(Bloco* disco, char* nome) {
    Bloco* atual = disco;
    while (atual) {
        if (!atual->livre && strcmp(atual->nome, nome) == 0) {
            atual->livre = 1;
            atual->nome[0] = '\0';
            break;
        }
        atual = atual->prox;
    }
}

void otimizar(Bloco** disco) {
    Bloco* novo = NULL;
    Bloco** ult = &novo;
    Bloco* atual = *disco;
    int total_livre = 0;

    while (atual) {
        if (!atual->livre) {
            Bloco* ocupado = malloc(sizeof(Bloco));
            *ocupado = *atual;
            ocupado->prox = NULL;
            *ult = ocupado;
            ult = &ocupado->prox;
        } else {
            total_livre += atual->tamanho;
        }
        atual = atual->prox;
    }

    if (total_livre > 0) {
        Bloco* livre = malloc(sizeof(Bloco));
        livre->livre = 1;
        livre->tamanho = total_livre;
        livre->nome[0] = '\0';
        livre->prox = NULL;
        *ult = livre;
    }

    atual = *disco;
    while (atual) {
        Bloco* temp = atual;
        atual = atual->prox;
        free(temp);
    }

    *disco = novo;
}

void imprimir(Bloco* disco, int capacidade) {
    int parte = capacidade / 8;
    int ocupados[8] = {0};

    int pos = 0;
    while (disco) {
        if (!disco->livre) {
            int inicio = pos / parte;
            int fim = (pos + disco->tamanho - 1) / parte;
            for (int i = inicio; i <= fim && i < 8; i++) {
                int parte_ini = i * parte;
                int parte_fim = parte_ini + parte;
                int inter_ini = pos > parte_ini ? pos : parte_ini;
                int inter_fim = (pos + disco->tamanho) < parte_fim ? (pos + disco->tamanho) : parte_fim;
                ocupados[i] += inter_fim - inter_ini;
            }
        }
        pos += disco->tamanho;
        disco = disco->prox;
    }

    for (int i = 0; i < 8; i++) {
        float perc = (100.0 * ocupados[i]) / parte;
        if (perc <= 25) printf("[ ]");
        else if (perc <= 75) printf("[-]");
        else printf("[#]");
    }
    printf("\n");
}


int main() {
    int N;
    while (scanf("%d", &N) && N != 0) {
        char str_tam[10];
        scanf("%s", str_tam);
        int capacidade = converter_para_kb(str_tam);

        Bloco* disco = malloc(sizeof(Bloco));
        disco->livre = 1;
        disco->tamanho = capacidade;
        disco->prox = NULL;

        int erro = 0;

        for (int i = 0; i < N; i++) {
            char op[10], nome[11], tam_str[10];
            scanf("%s", op);
            if (strcmp(op, "inserir") == 0) {
                scanf("%s %s", nome, tam_str);
                int tam = converter_para_kb(tam_str);
                if (!inserir(&disco, nome, tam)) {
                    otimizar(&disco);
                    if (!inserir(&disco, nome, tam)) {
                        printf("ERRO: disco cheio\n");
                        erro = 1;
                        char linha[100];
                        fgets(linha, 100, stdin);
                        for (int j = i + 1; j < N; j++) fgets(linha, 100, stdin);
                        break;
                    }
                }
            } else if (strcmp(op, "remover") == 0) {
                scanf("%s", nome);
                remover(disco, nome);
            } else if (strcmp(op, "otimizar") == 0) {
                otimizar(&disco);
            }
        }

        if (!erro) {
            imprimir(disco, capacidade);
        }

        Bloco* atual = disco;
        while (atual) {
            Bloco* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    return 0;
}

    
