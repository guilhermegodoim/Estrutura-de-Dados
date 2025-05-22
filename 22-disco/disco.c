#include<stdio.h>
#include<stdlib.h>
#include <errno.h>
#include<string.h>
#define MAX_NOMES 10

typedef struct {
    int valor;
    char prefixo;
} tamanho;

typedef struct {
    char nome[MAX_NOMES];
    tamanho size;
} arquivo;

typedef struct bloco {
    arquivo arq;
    int capacidade; // em bytes
    int p; // porcentagem ocupada
    struct bloco* prox;
} bloco;


/* A função a seguir calcula quanto cada bloco do nosso disco tem de memória
Ela converte o tamanho lido do disco para Kb (que é a menor divisão de memória 
utilizada no lab.)*/

long calcula_cap_bloco(tamanho *disco) {
    long cap_bloco = 0;

    if (disco->prefixo == 'M') {
        cap_bloco = (disco->valor * 1024L) / 8;
    } else if (disco->prefixo == 'G') {
        cap_bloco = (disco->valor * 1024L * 1024L) / 8;
    } else if (disco->prefixo == 'K') {
        cap_bloco = disco->valor / 8;
    }

    return cap_bloco;
}

/*Nosso disco é uma lista ligada em que cada nó é um bloco com a capacidade (em Kb) 
igual ao tamanho do disco dividido por 8 (são 8 blocos totais)*/

bloco* inicializa_disco(int capacidade_bloco) {
    bloco* inicio = NULL;
    bloco* atual = NULL;

    for (int i = 0; i < 8; i++) {
        bloco* novo = malloc(sizeof(bloco));
        if (!novo) {
            perror("Erro ao alocar bloco");
            exit(1);
        }

        // Inicializa os campos do bloco
        novo->capacidade = capacidade_bloco;
        novo->p = 0;
        novo->prox = NULL;
        novo->arq.nome[0] = '\0'; // vazio
        novo->arq.size.valor = 0;
        novo->arq.size.prefixo = 'K'; // padrão

        if (inicio == NULL) {
            inicio = novo;
        } else {
            atual->prox = novo;
        }
        atual = novo;
    }

    return inicio;
}


int main(){
    int N,D; //N é o número de comandos e D o tamanho do disco
    
    // o tamanho do disco será da forma (VALOR) (PREFIXO)b
    int valor; 
    char prefixo; //K,M,G
    tamanho * disco = malloc(sizeof(tamanho));

    while(1){
        scanf("%d", &N);
        if (N == 0){
            return 0;
        }
        scanf("%d%cb", &disco->valor, &disco->prefixo);

        long capacidade_bloco = calcula_cap_bloco(disco);
        printf("Capacidade do bloco: %ld Kb\n", capacidade_bloco);

        bloco* lista_blocos = inicializa_disco(capacidade_bloco);
        

        int i;
        for(int i = 0; i < N; i++){
            char comando[10];
            scanf("%s", comando);

            if (strcmp(comando, "inserir") == 0){
                arquivo file;
                scanf("%s %d%cb", &file.nome, &file.size.valor, &file.size.prefixo);
                // chamar função inserir (arquivo)
            
            } else if (strcmp(comando, "remover") == 0){
                char nome[MAX_NOMES];
                scanf("%s", nome);
            
            } else if (strcmp(comando, "otimizar") == 0){
                printf("teste");

            } else {
                return 0;
            }
        }
    }
}
    

