#include<stdio.h>
#include "funcoes.h"
#include<string.h>

int main() {
    char instruction[20];
    node* tree = NULL;
    int timestamp = 0;
    int key;

    while (1) {
        scanf("%s", instruction);
        
        if (strcmp(instruction, "criar") == 0) {
            if (tree != NULL) {
                free_tree(tree);
            }
            tree = NULL;
            timestamp = 0;
            
        } else if (strcmp(instruction, "inserir") == 0) {
            scanf("%d", &key);
            node* new_tree = insert(tree, key, timestamp);
            if (new_tree == NULL && tree == NULL) {
                printf("memoria insuficiente\n");
            } else {
                tree = new_tree;
            }
            timestamp++;
            
        } else if (strcmp(instruction, "remover") == 0) {
            scanf("%d", &key);
            tree = remove_node(tree, key);
            timestamp++;
            
        } else if (strcmp(instruction, "buscar") == 0) {
            scanf("%d", &key);
            search(tree, key);
            
        } else if (strcmp(instruction, "imprimir") == 0) {
            if (tree == NULL) {
                printf("arvore vazia\n");
            } else {
                printf("em-ordem: ");
                print_inorder(tree);
                printf("\n");
            }
            
        } else if (strcmp(instruction, "info") == 0) {
            if (tree == NULL) {
                printf("nos: 0, folhas: 0, altura: 0\n");
            } else {
                int nodes, leaves;
                info_tree(tree, &nodes, &leaves);
                printf("nos: %d, folhas: %d, altura: %d\n", nodes, leaves, height(tree));
            }
            
        } else if (strcmp(instruction, "terminar") == 0) {
            if (tree != NULL) {
                free_tree(tree);
            }
            break;
        }
    }

    return 0;
}
