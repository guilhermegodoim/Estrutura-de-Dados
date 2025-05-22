#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 12000
#define MAX_K 15

int main() {
    int n, k;
    char cadeia[MAX];
    char sequencias[MAX][MAX_K]; // matriz em que cada linha é uma sequencia extraída da cadeia
    int frequencias[MAX] = {0}; // frequencia em que uma sequencia aparece na cadeia   
    int total;

    while (scanf("%d", &n) != EOF) {
        scanf("%s", cadeia);
        scanf("%d", &k);


        total = n - k + 1; // esse termo aparece repetidamente no código
        
        for (int i = 0; i < total; i++) {
            strncpy(sequencias[i], cadeia + i, k);
            sequencias[i][k] = '\0';
        } // aqui montamos a matriz com cada substring de tamanho k obtida em ordem

        // agora, percorrer a matriz e identificar as sequencias
        for (int i = 0; i < total; i++) {
            if (frequencias[i] == -1) continue;
            frequencias[i] = 1;
            for (int j = i + 1; j < total; j++) {
                if (strcmp(sequencias[i], sequencias[j]) == 0) {
                    frequencias[i]++;
                    frequencias[j] = -1;
                }
            }
        }
        
        // encontrar a frequencia maxima
        int freq_max = 0;
        for (int i = 0; i < total; i++) {
            if (frequencias[i] > freq_max) {
                freq_max = frequencias[i];
            }
        }

        // identificar as strings com frequencia maxima
        char resultado[MAX][MAX_K];
        int contador = 0;
        for (int i = 0; i < total; i++) {
            if (frequencias[i] == freq_max) {
                strcpy(resultado[contador++], sequencias[i]);
            }
        }

        // colocar em ordem alfabética
        for (int i = 0; i < contador - 1; i++) {
            for (int j = i + 1; j < contador; j++) {
                if (strcmp(resultado[i], resultado[j]) > 0) {
                    char temporario[MAX_K];
                    strcpy(temporario, resultado[i]);
                    strcpy(resultado[i], resultado[j]);
                    strcpy(resultado[j], temporario);
                }
            }
        }

        printf("%d %d:", k, freq_max);
        for (int i = 0; i < contador; i++) {
            printf(" %s", resultado[i]);
        }
        printf(" \n");
    }

    return 0;
}
