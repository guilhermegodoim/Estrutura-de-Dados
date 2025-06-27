#include "funcoes.h"
#include<string.h>


// Funções de hashing
unsigned long djb2(unsigned char *str) {
  unsigned long hash = 5381;
  int c;
  
  while ((c = *str++))
    hash = ((hash << 5) + hash) ^ c; // hash * 33 XOR c
  
  return hash;
}

int h1(unsigned long k, int size) { // Primeira função de hash
    return k % size;
}

int h2(unsigned long k, int size) { // Segunda função de hash (incremento)
    return 1 + (k % (size - 1));
}

// Funções auxiliares

hash_table *create_table(int size) {
    int table_size = new_size(size); // você já tem essa função

    hash_table *ht = malloc(sizeof(hash_table));
    if (!ht) return NULL;

    ht->dados = calloc(table_size, sizeof(pairs));
    if (!ht->dados) {
        free(ht);
        return NULL;
    }

    ht->size = table_size;
    return ht;
}


int new_size(int size){ // retorna o novo tamanho para que tabela fique apenas 70% ao armazenar todoos os n pares
    return size = (10 * size) / 7;
}


// Funções principais

int insert(hash_table* ht, char *str, int timestamp) {
   unsigned long k = djb2((unsigned char*)str);
   int pos = h1(k, ht->size);
   int step = h2(k, ht->size);
   
   for (int i = 0; i < ht->size; i++) {
       int nova_pos = (pos + i * step) % ht->size;
       
       // Posição vazia (assumindo que string vazia indica posição livre)
       if (ht->dados[nova_pos].string[0] == '\0') {
           strcpy(ht->dados[nova_pos].string, str);
           ht->dados[nova_pos].timestamp = timestamp;
           return 1; // Sucesso
       }
       
       // Verifica se o elemento já existe
       if (strcmp(ht->dados[nova_pos].string, str) == 0) {
           // Atualiza timestamp se já existe
           ht->dados[nova_pos].timestamp = timestamp;
           return 0; // Elemento já existia
       }
   }
   
   return -1; // Tabela cheia
}

void print_table(hash_table *ht) {
   printf("Tabela Hash (tamanho: %d):\n", ht->size);
   for (int i = 0; i < ht->size; i++) {
       if (ht->dados[i].string[0] != '\0') {
           printf("[%d] %s (timestamp: %d)\n", i, ht->dados[i].string, ht->dados[i].timestamp);
       }
   }
   printf("\n");
}