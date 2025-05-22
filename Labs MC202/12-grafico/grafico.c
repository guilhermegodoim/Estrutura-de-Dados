#include <stdio.h>

int main() {
    int numero, frequencia;
    char caractere;
    
    while (scanf(" (%d , %d , %c )", &numero, &frequencia, &caractere) == 3) {
        printf("%4d |", numero);

        for (int i = 0; i < frequencia; i++) {
            putchar(caractere);
        }

        printf(" %d\n", frequencia);
    }

    return 0;
}
