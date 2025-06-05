#include<stdio.h>
#include "funcoes.h"

int main() {
    tree* arvore = criar_arvore();
    
    printf("=== DEMONSTRAÇÃO DA ÁRVORE BINÁRIA ===\n\n");
    
    // Inserindo elementos
    printf("Inserindo elementos: 50, 30, 70, 20, 40, 60, 80\n");
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int numValores = sizeof(valores) / sizeof(valores[0]);
    
    for (int i = 0; i < numValores; i++) {
        if (inserir(arvore, valores[i])) {
            printf("Valor %d inserido com sucesso!\n", valores[i]);
        } else {
            printf("Falha ao inserir o valor %d\n", valores[i]);
        }
    }
    
    // Testando inserção de duplicata
    printf("\nTentando inserir duplicata (50):\n");
    if (inserir(arvore, 50)) {
        printf("Valor 50 inserido com sucesso!\n");
    } else {
        printf("Falha ao inserir o valor 50 (duplicata não permitida)\n");
    }
    
    printf("\nEstrutura visual da árvore:\n");
    imprimirArvore(arvore->raiz, 0);
    
    printf("\n=== PERCURSOS ===\n");
    printf("InOrder (crescente): ");
    percursoInOrder(arvore->raiz);
    printf("\n");
    
    printf("PreOrder: ");
    percursoPreOrder(arvore->raiz);
    printf("\n");
    
    printf("PostOrder: ");
    percursoPostOrder(arvore->raiz);
    printf("\n");


    return 0;
}