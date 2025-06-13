#include "funcoes.h"

node * create_node(int x){
    node * new_node = malloc (sizeof(node));

    new_node->height = 0; // altura da subarvore com raíz nesse nó
    new_node->key = x;
    new_node->left = new_node->right = NULL;

    return new_node;

}


node* insert(node* root, int x) {
    if (root == NULL) {
        return create_node(x); 
    }

    if (x < root->key) {
        node* original = root->left; // backup
        root->left = insert(root->left, x);
        update_height(root);
        if (!balanced(root)) {
            root->left = original; // desfaz a inserção
            update_height(root);
        }
    } else if (x > root->key) {
        node* original = root->right; // backup
        root->right = insert(root->right, x);
        update_height(root);
        if (!balanced(root)) {
            root->right = original; // desfaz a inserção
            update_height(root);
        }
    }

    return root; // se x == root->key, só retorna (sem inserir elemento repetido)
}

int height(node * root){
    if (root == NULL){
        return -1;
    }

    return root->height;
}

void update_height(node * root){
    if (root != NULL){
        int lh = height(root->left); // altura da SAE
        int rh = height(root->right); // altura da SAD
        
        root->height = 1 + (lh > rh ? lh : rh);
    }
}

int balanced(node* root) {
    if (root == NULL) {
        return 1;
    }
    
    int dif = altura(root->left) - altura(root->right);
    
    return (dif >= -2 && dif <= 2);
}

