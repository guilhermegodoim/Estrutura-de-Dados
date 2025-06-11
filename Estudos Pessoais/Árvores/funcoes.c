#include "funcoes.h"

tree * criar_arvore(){
    tree * arv = malloc(sizeof(tree));
    if (arv != NULL){
        arv->raiz = NULL;
    }
    return arv;
}

ArvNo * criar_no(int x){
    ArvNo* novo = malloc(sizeof(ArvNo));
    if (novo != NULL){
        novo->dado = x;
        novo->left = NULL;
        novo->right = NULL;
    }

    return novo;
}

/* A função insere com a propriedade BST (binary search tree), em que o valor se o valor
do nó a ser inserido é menor que o nó atual, ele é inserido na SAE. Caso seja maior, é in-
serido na SAD. Se for igual, não insere. */

ArvNo* inserir(ArvNo *raiz, int x){
    if (raiz == NULL){
        return criar_no(x);  // cria e retorna o novo nó
    }

    if (x > raiz->dado){
        raiz->right = inserir(raiz->right, x);
    } else if (x < raiz->dado){
        raiz->left = inserir(raiz->left, x);
    }
    // Se for igual, não insere
    return raiz;
}
    

// Percurso em ordem (inorder) - esquerda, raiz, direita
void percursoInOrder(ArvNo* raiz) {
    if (raiz != NULL) {
        percursoInOrder(raiz->left);
        printf("%d ", raiz->dado);
        percursoInOrder(raiz->right);
    }
}

// Percurso pré-ordem (preorder) - raiz, esquerda, direita
void percursoPreOrder(ArvNo* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        percursoPreOrder(raiz->left);
        percursoPreOrder(raiz->right);
    }
}

// Percurso pós-ordem (postorder) - esquerda, direita, raiz
void percursoPostOrder(ArvNo* raiz) {
    if (raiz != NULL) {
        percursoPostOrder(raiz->left);
        percursoPostOrder(raiz->right);
        printf("%d ", raiz->dado);
    }
}

void imprimirArvore(ArvNo* raiz, int espaco) {
    if (raiz == NULL) {
        return;
    }
    
    espaco += 10;
    
    imprimirArvore(raiz->right, espaco);
    
    printf("\n");
    for (int i = 10; i < espaco; i++) {
        printf(" ");
    }
    printf("%d\n", raiz->dado);
    
    imprimirArvore(raiz->left, espaco);
}

ArvNo* remover_no(ArvNo* raiz, int x) {
    if (raiz == NULL)
        return NULL;

    if (x < raiz->dado) {
        raiz->left = remover_no(raiz->left, x);
    } else if (x > raiz->dado) {
        raiz->right = remover_no(raiz->right, x);
    } else {
        // Caso 1: sem filhos
        if (raiz->left == NULL && raiz->right == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: um filho (direita)
        else if (raiz->left == NULL) {
            ArvNo* temp = raiz->right;
            free(raiz);
            return temp;
        }
        // Caso 2: um filho (esquerda)
        else if (raiz->right == NULL) {
            ArvNo* temp = raiz->left;
            free(raiz);
            return temp;
        }
        // Caso 3: dois filhos
        else {
            ArvNo* sucessor = raiz->right;
            while (sucessor->left != NULL) {
                sucessor = sucessor->left;
            }
            raiz->dado = sucessor->dado;
            raiz->right = remover_no(raiz->right, sucessor->dado);
        }
    }

    return raiz;
}


int altura(ArvNo * raiz){
    if (raiz == NULL){
        return -1;
    }

    int h_esq = altura(raiz->left);
    int h_dir = altura(raiz->right);

    return (h_esq > h_dir ? h_esq : h_dir) + 1;



}

