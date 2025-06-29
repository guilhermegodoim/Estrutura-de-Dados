#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_NAMES 250

#include<stdlib.h>
#include<stdio.h>

typedef struct pairs{
    char string[MAX_NAMES];
    int timestamp;
}pairs;

typedef struct hash_table{
    pairs *dados; 
    int size;     
}hash_table;

unsigned long djb2(unsigned char *str); 
int h1(unsigned long k, int size);
int h2(unsigned long k, int size);
hash_table *create_table(int size);
int new_size(int size);
void print_table(hash_table *ht);
int insert(hash_table* ht, char *str, int timestamp);
int remove_item(hash_table *ht, char *str); 
void destroy_table(hash_table *ht);
int search(hash_table *ht, char *str, int *timestamp);

#endif