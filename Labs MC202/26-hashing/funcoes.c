#include "funcoes.h"
#include<string.h>

unsigned long djb2(unsigned char *str) {
  unsigned long hash = 5381;
  int c;
  
  while ((c = *str++))
    hash = ((hash << 5) + hash) ^ c;
  
  return hash;
}

int h1(unsigned long k, int size) { 
    return k % size;
}

int h2(unsigned long k, int size) { 
    return 1 + (k % (size - 1));
}

int is_empty(pairs *p) {
    return p->string[0] == '\0';
}

void mark_empty(pairs *p) {
    p->string[0] = '\0';
    p->timestamp = 0;
}

hash_table *create_table(int size) {
    int table_size = new_size(size); 

    hash_table *ht = malloc(sizeof(hash_table));
    if (!ht) {
        return NULL;
    }

    ht->dados = calloc(table_size, sizeof(pairs));
    if (!ht->dados) {
        free(ht);
        return NULL;
    }

    ht->size = table_size;
    
    int i;
    for (i = 0; i < table_size; i++) {
        mark_empty(&ht->dados[i]);
    }

    return ht;
}

int insert(hash_table* ht, char *str, int timestamp) {
    if (!ht || !str) return -1;
    
    unsigned long k = djb2((unsigned char*)str);
    int pos = h1(k, ht->size);
    int step = h2(k, ht->size);
    
    int i = 0;
    while(i < ht->size) {
        int nova_pos = (pos + i * step) % ht->size;
        
        if (is_empty(&ht->dados[nova_pos])) {
            strcpy(ht->dados[nova_pos].string, str);
            ht->dados[nova_pos].timestamp = timestamp;
            return 1;
        }
        
        if (strcmp(ht->dados[nova_pos].string, str) == 0) {
            return 0;
        }
        i++;
    }
    
    return -1;
}

int search(hash_table *ht, char *str, int *timestamp) {
    if (!ht || !str) return 0;
    
    unsigned long k = djb2((unsigned char*)str);
    int pos = h1(k, ht->size);
    int step = h2(k, ht->size);
    
    int i;
    for (i = 0; i < ht->size; i++) {
        int nova_pos = (pos + i * step) % ht->size;
        
        if (is_empty(&ht->dados[nova_pos])) {
            return 0;
        }
        
        if (strcmp(ht->dados[nova_pos].string, str) == 0) {
            if (timestamp) {
                *timestamp = ht->dados[nova_pos].timestamp;
            }
            return 1;
        }
    }
    
    return 0;
}

int remove_item(hash_table *ht, char *str) {
    if (!ht || !str) return 0;
    
    unsigned long k = djb2((unsigned char*)str);
    int pos = h1(k, ht->size);
    int step = h2(k, ht->size);
    
    int pos_to_remove = -1;
    int i;
    for (i = 0; i < ht->size; i++) {
        int nova_pos = (pos + i * step) % ht->size;
        
        if (is_empty(&ht->dados[nova_pos])) {
            return 0;
        }
        
        if (strcmp(ht->dados[nova_pos].string, str) == 0) {
            pos_to_remove = nova_pos;
            break;
        }
    }
    
    if (pos_to_remove == -1) {
        return 0;
    }
    
    mark_empty(&ht->dados[pos_to_remove]);
    
    int current_pos = (pos_to_remove + step) % ht->size;
    
    while (!is_empty(&ht->dados[current_pos])) {
        pairs temp = ht->dados[current_pos];
        
        mark_empty(&ht->dados[current_pos]);
        
        unsigned long temp_k = djb2((unsigned char*)temp.string);
        int temp_pos = h1(temp_k, ht->size);
        int temp_step = h2(temp_k, ht->size);
        
        int j = 0;
        while(j < ht->size) {
            int new_pos = (temp_pos + j * temp_step) % ht->size;
            
            if (is_empty(&ht->dados[new_pos])) {
                ht->dados[new_pos] = temp;
                break;
            }
            j++;
        }
        
        current_pos = (current_pos + step) % ht->size;
    }
    
    return 1;
}

int new_size(int size){ 
    return (10 * size) / 7;
}

void print_table(hash_table *ht) {
   printf("Tabela Hash (tamanho: %d):\n", ht->size);
   for (int i = 0; i < ht->size; i++) {
       if (!is_empty(&ht->dados[i])) {
           printf("[%d] %s (timestamp: %d)\n", i, ht->dados[i].string, ht->dados[i].timestamp);
       }
   }
   printf("\n");
}

void destroy_table(hash_table *ht) {
    if (ht) {
        if (ht->dados) {
            free(ht->dados);
        }
        free(ht);
    }
}