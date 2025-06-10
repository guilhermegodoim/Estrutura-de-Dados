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

int altura(ArvNo* raiz) {
    if (raiz == NULL)
        return -1; // altura da árvore vazia é -1
    else {
        int alturaEsq = altura(raiz->left);
        int alturaDir = altura(raiz->right);
        return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
    }
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
