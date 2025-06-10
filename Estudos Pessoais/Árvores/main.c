#include<stdio.h>
#include "funcoes.h"

int main() {
    tree* arvore = criar_arvore();
    
    printf("=== DEMONSTRAÇÃO DA ÁRVORE BINÁRIA ===\n\n");
    
    // Inserindo elementos
    printf("Inserindo elementos: ,2,3,4,5,6,7,8,9,10\n");
    int valores[] = {1,2,3,4,5,6,7,8,9,10};
    int numValores = sizeof(valores) / sizeof(valores[0]);
    
    for (int i = 0; i < numValores; i++) {
        if (inserir(arvore, valores[i])) {
            printf("Valor %d inserido com sucesso!\n", valores[i]);
        } else {
            printf("Falha ao inserir o valor %d\n", valores[i]);
        }
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

    
    int h = altura(arvore->raiz);
    printf("Altura da árvore: %d\n", h);





    return 0;
}