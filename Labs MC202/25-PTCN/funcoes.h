#ifndef FUNCOES_H
#define FUNCOES_H

#include<stdlib.h>
#include<stdio.h>

// struct alterada para conter a altura e o timestamp. Nesse caso a altura é relativa a subárvore no qual determinado nó é o pai
typedef struct node{
    int key;
    struct node *left;
    struct node *right;
    int height;
    int timestamp;
}node;


node* create_node(int x, int timestamp);
node* insert(node* root, int x, int timestamp);
node* insert_simple(node* root, int x, int timestamp);
node* remove_node(node* root, int x);
node* remove_simple(node* root, int x);
node* find_min(node* root);
void search(node* root, int x);
void print_inorder(node* root);
void info_tree(node* root, int* nodes, int* leaves);
int height(node* root);
void update_height(node* root);
int balanced(node* root);
int tree_balanced(node* root);
int search_key(node* root, int x);
node* copy_subtree(node* root);
void free_tree(node* root);
int count_nodes(node* root);
int count_leaves(node* root);

#endif
