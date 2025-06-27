#include "funcoes.h"

/* 

funções principais : 

- para as funções de inserir/remover, precisei fazer 2 funções para cada: uma que insere de forma normal (igual uma ABB)
e outra que verifica o balanceamento da árvore. 
- as duas funcionam de forma similar: fazem um backup dos dados da árvore, tentam inserir/remover igual uma abb comum. depois,
verificam o balanceamento e mantém/desfaz dependendo do balanceamento da árvore nova.

*/

node* create_node(int x, int timestamp) {
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->height = 0;
    new_node->key = x;
    new_node->timestamp = timestamp;
    new_node->left = new_node->right = NULL;

    return new_node;
}

// função de inserir que verifica o balanceamento
node* insert(node* root, int x, int timestamp) {
    // duplicata
    if (search_key(root, x)) {
        return root;
    }

    node* backup = copy_subtree(root);
    
    node* new_root = insert_simple(root, x, timestamp);
    
    // verificar balanceamento
    if (!tree_balanced(new_root)) {
        free_tree(new_root);
        return backup;
    } else {
        free_tree(backup);
        return new_root;
    }
}

// inserção simples igual abb
node* insert_simple(node* root, int x, int timestamp) {
    if (root == NULL) {
        return create_node(x, timestamp);
    }

    if (x == root->key) {
        return root; 
    }

    if (x < root->key) {
        root->left = insert_simple(root->left, x, timestamp);
    } else {
        root->right = insert_simple(root->right, x, timestamp);
    }

    update_height(root);
    return root;
}

// remoção simples igual abb
node* remove_simple(node* root, int x) {
    if (root == NULL) {
        return root;
    }

    if (x < root->key) {
        root->left = remove_simple(root->left, x);
    } else if (x > root->key) {
        root->right = remove_simple(root->right, x);
    } else {
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }
        node* successor = find_min(root->right);
        root->key = successor->key;
        root->timestamp = successor->timestamp;
        root->right = remove_simple(root->right, successor->key);
    }

    update_height(root);
    return root;
}

// remoção que verifica balanceamento
node* remove_node(node* root, int x) {
    if (!search_key(root, x)) {
        return root;
    }

    node* backup = copy_subtree(root);
    
    node* new_root = remove_simple(root, x);
    
    // verificar balanceamento
    if (!tree_balanced(new_root)) {
        free_tree(new_root);
        return backup;
    } else {
        free_tree(backup);
        return new_root;
    }
}

void search(node* root, int x) {
    if (root == NULL) {
        printf("nao ha chave %d\n", x);
        return;
    }

    if (x == root->key) {
        printf("chave %d: inserida no tempo %d\n", x, root->timestamp);
        return;
    }

    if (x < root->key) {
        search(root->left, x);
    } else {
        search(root->right, x);
    }
}

void print_inorder(node* root) {
    if (root != NULL) {
        print_inorder(root->left);
        printf("%d ", root->key);
        print_inorder(root->right);
    }
}

void info_tree(node* root, int* nodes, int* leaves) {
    *nodes = count_nodes(root);
    *leaves = count_leaves(root);
}

// funções auxiliares

int height(node* root) {
    if (root == NULL) {
        return -1;
    }
    return root->height;
}

void update_height(node* root) {
    if (root != NULL) {
        int lh = height(root->left);
        int rh = height(root->right);
        root->height = 1 + (lh > rh ? lh : rh);
    }
}

int balanced(node* root) {
    if (root == NULL) {
        return 1;
    }
    
    int dif = height(root->left) - height(root->right);
    return (dif >= -2 && dif <= 2);
}

// versão recursiva
int tree_balanced(node* root) {
    if (root == NULL) {
        return 1;
    }
    
    return balanced(root) && tree_balanced(root->left) && tree_balanced(root->right);
}

void free_inserted_subtree(node* subtree, node* original) {
    if (subtree != original && subtree != NULL) {
        free_tree(subtree);
    }
}

// função auxiliar pra ver se um numero existe na árvore
int search_key(node* root, int x) {
    if (root == NULL) {
        return 0;
    }
    if (x == root->key) {
        return 1;
    }
    if (x < root->key) {
        return search_key(root->left, x);
    } else {
        return search_key(root->right, x);
    }
}



node* find_min(node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

node* copy_subtree(node* root) {
    if (root == NULL) {
        return NULL;
    }
    
    node* new_node = create_node(root->key, root->timestamp);
    if (new_node == NULL) {
        return NULL;
    }
    
    new_node->height = root->height;
    new_node->left = copy_subtree(root->left);
    new_node->right = copy_subtree(root->right);
    
    return new_node;
}



int count_nodes(node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

int count_leaves(node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return count_leaves(root->left) + count_leaves(root->right);
}

void free_tree(node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}