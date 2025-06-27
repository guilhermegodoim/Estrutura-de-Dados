#include<stdio.h>
#include "funcoes.h"

int main() {
   // Criar tabela para 10 elementos (será criada com tamanho ~14)
   hash_table *ht = create_table(10);
   
   printf("Testando inserção na tabela hash:\n\n");
   
   // Inserir alguns elementos
   int result;
   
   result = insert(ht, "Alice", 1001);
   printf("Inserir 'Alice': %s\n", result == 1 ? "Sucesso" : result == 0 ? "Atualizado" : "Falha");
   
   result = insert(ht, "Bob", 1002);
   printf("Inserir 'Bob': %s\n", result == 1 ? "Sucesso" : result == 0 ? "Atualizado" : "Falha");
   
   result = insert(ht, "Charlie", 1003);
   printf("Inserir 'Charlie': %s\n", result == 1 ? "Sucesso" : result == 0 ? "Atualizado" : "Falha");
   
   result = insert(ht, "Alice", 2001); // Tentativa de inserir duplicata
   printf("Inserir 'Alice' novamente: %s\n", result == 1 ? "Sucesso" : result == 0 ? "Atualizado" : "Falha");
   
   result = insert(ht, "Diana", 1004);
   printf("Inserir 'Diana': %s\n", result == 1 ? "Sucesso" : result == 0 ? "Atualizado" : "Falha");
   
   printf("\n");
   print_table(ht);

   return 0;}