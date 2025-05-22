#include<stdio.h>
#include<math.h>

#define MAX 1000



void somar(int vetor[], int pos_inicial, int pos_final, int R[], int r){

    int soma = 0;
    int inicio_intervalo = pos_inicial / r;
    int fim_intervalo = pos_final / r;

    for (int i = inicio_intervalo + 1; i < fim_intervalo; i++) {
        soma += R[i];
    }
    for (int i = pos_inicial; i < (inicio_intervalo + 1) * r; i++) {
        soma += vetor[i];
    }
    for (int i = fim_intervalo * r; i <= pos_final; i++) {
        soma += vetor[i];
    }    

    printf("%d\n", soma);

}

void atualizar(int vetor[], int posicao, int elemento, int R[], int r) {
    int bloco = posicao / r;
    R[bloco] -= vetor[posicao]; // Remove o valor antigo do bloco
    vetor[posicao] = elemento;
    R[bloco] += elemento; // Adiciona o novo valor ao bloco
}

int main(){
    int n; // números de elementos de S
    int vetor[MAX];
    int r;

    scanf("%d", &n);
    r = ceil(sqrt(n));    
    int R[r];
    
    for(int i = 0; i < n; i++){ 
        scanf("%d", &vetor[i]); // adiciona os valores ao vetor
        }
    
    // Construindo vetor R
    for (int i = 0; i < r; i++) {
        R[i] = 0;
        int inicio = i * r;
        int fim = (i + 1) * r - 1;
        if (fim >= n) fim = n - 1;

        for (int j = inicio; j <= fim; j++) {
            R[i] += vetor[j];
        }
    }
    
    while(1){
        char comando;
        int i, j;

        scanf(" %c, %d, %d", &comando, &i, &j);
        
        if(comando == 'a'){
            atualizar(vetor, i, j, R, r); // irá chamar a trocar o numero da posição "i" pelo valor "j"
        } else if (comando == 's'){
            somar(vetor, i, j, R, r); // soma os valores do intervalo de i até j
        } else{
            return 0;}
    }
    
    return 0;
}

    
        