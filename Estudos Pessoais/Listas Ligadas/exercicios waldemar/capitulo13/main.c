#include <stdio.h>
#include "funcoes.h"

int main() {
   
   no * lista = NULL;

   insere_final(&lista, 13);
   insere_final(&lista, 17);

   imprime_lista(lista);

   
   return 0;
}
