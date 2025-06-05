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

int inserir(tree * T, int x){
    if (T == NULL){
        return 0; // árvore inválida (não foi inicializada)
    }
    
    ArvNo * novo = criar_no(x);

    if (novo == NULL){
        return 0; // erro de alocação
    }

    /* Caso a árvore seja vazia, nosso novo nó é a raíz*/
    if (T->raiz == NULL){
        T->raiz = novo;
        return 1;
    }

    /* Agora, caso a árvore já tenha uma raíz, vamos ter que percorrer ela para encontrar a 
    posição de inserção */

    ArvNo * atual = T->raiz;
    ArvNo * pai = NULL;

    while (atual != NULL){
        pai = atual;

        if (x < atual->dado){
            atual = atual->left;
        } else if (x > atual->dado){
            atual = atual->right;
        } else{
            return 0;
        }
    }

    /* Após esse loop temos o ponteiro pai apontando para a folha que iremos inserir o novo nó. 
    Vamos agora inserir usando essa informação. */

    if (x < pai->dado){
        pai->left = novo;
    } else if (x > pai->dado){
        pai->right = novo;
    }

    return 1; // inserção bem sucedida.

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

