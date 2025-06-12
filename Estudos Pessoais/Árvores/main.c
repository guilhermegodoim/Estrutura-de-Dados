#include<stdio.h>
#include "funcoes.h"

int main() {
    tree* arvore = criar_arvore();
    tree* arvore2 = criar_arvore();

    arvore2->raiz = inserir(arvore2->raiz, 23);
    arvore2->raiz = inserir(arvore2->raiz, 24);
    arvore2->raiz = inserir(arvore2->raiz, 25);
    arvore2->raiz = inserir(arvore2->raiz, 26);


    
    printf("=== DEMONSTRAÇÃO DA ÁRVORE BINÁRIA ===\n\n");
    
    printf("Inserindo elementos: 12, 45, 2, 99, 13, 54\n");
    int valores[] = {12, 45, 2, 99, 13, 54};
    int numValores = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < numValores; i++) {
        arvore->raiz = inserir(arvore->raiz, valores[i]);
        

        // Checando se o valor foi inserido (simplesmente aceitamos não duplicados)
        printf("Valor %d inserido com sucesso!\n", valores[i]);
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

    if (sao_iguais(arvore->raiz, arvore2->raiz)){
        printf("As árvores são iguais\n");
    }else{
        printf("Não são iguais\n");
    }





    return 0;
}