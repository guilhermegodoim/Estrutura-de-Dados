#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int main() {
    hash_table *ht = NULL;
    char comando;
    char linha[MAX_NAMES];
    int n, timestamp_atual = 0;
    
    while (scanf("%c", &comando) == 1) {
        switch (comando) {
            case 'c':
                if (scanf("%d", &n) == 1) {
                    if (ht) {
                        destroy_table(ht);
                    }
                    ht = create_table(n);
                    timestamp_atual = 0;  
                }
                break;
                
            case 'i':
                if (scanf(" %[^\n]", linha) == 1 && ht) {
                    int resultado = insert(ht, linha, timestamp_atual);
                    if (resultado == 1) {
                        timestamp_atual++;
                    }
                }
                break;
                
            case 'r':
                if (scanf(" %[^\n]", linha) == 1 && ht) {
                    remove_item(ht, linha);
                }
                break;
                
            case 'b':
                if (scanf(" %[^\n]", linha) == 1 && ht) {
                    int timestamp_encontrado;
                    if (search(ht, linha, &timestamp_encontrado)) {
                        printf("[%s] esta na tabela, timestamp %d\n", 
                               linha, timestamp_encontrado);
                    } else {
                        printf("[%s] nao esta na tabela\n", linha);
                    }
                }
                break;
            
            case 'p':
                if (ht) {
                    print_table(ht);
                }
                break;     
               
            case 'f':
                if (ht) {
                    destroy_table(ht);
                    ht = NULL;
                }
                return 0;
                
            case '\n':
                break;
                
            default:
                scanf("%*[^\n]");
                break;
        }
    }
    
    
    return 0;
}