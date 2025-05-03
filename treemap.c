#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap *mapa = (TreeMap*)malloc(sizeof(TreeMap));
    if (mapa == NULL) return NULL;

    mapa->root = NULL;
    mapa->current = NULL;
    mapa->lower_than = lower_than;

    return mapa;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode *node = createTreeNode(key, value);
    if (tree->root == NULL){
        tree->root = node;
        tree->current = node;
        return;
    }

    TreeNode * aux = tree->root; 
    TreeNode * parent = NULL;
    while (aux != NULL){
        parent = aux;

        if (is_equal(tree, key, aux->pair->key)) return;

        if (tree->lower_than(key, aux->pair->key)){
            aux = aux->left;
        } else{
            aux = aux->right;
        }
    }
    node->parent = parent;

    if (tree->lower_than(key, parent->pair->key)){
        parent->left = node;
    } else{
        parent->right = node;
    }

    tree->current = node;
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;
    
    while (x->left != NULL){
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (node == NULL) return;

    if (node->left == NULL && node->right == NULL){
        if (node->parent == NULL){
            tree->root = NULL;
        } else {
            if (node->parent->left == node){
                node->parent->left = NULL;
            } else{
                node->parent->right = NULL;
            }
        }
        free(node->pair);
        free(node);
        return;
    }

    if (node->left == NULL || node->right == NULL){
        TreeNode * son;
        if (node->left != NULL) {
            son = node->left;
        } else {
            son = node->right;
        }

        if (node->parent = NULL) {
            tree->root = son;
        } else{
            if (node->parent->left == node){
                node->parent->left = son;
            } else{
                node->parent->right = son;
            }
        }
        son->parent = node->parent;
        free(node->pair);
        free(node);
        return;
    }
    TreeNode *sucesor = minimum(node->right);
    node->pair->key = sucesor->pair->key;
    node->pair->value = sucesor->pair->value;
    removeNode(tree,sucesor);
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode *aux = tree->root;

    while (aux != NULL){
        if (is_equal(tree, key, aux->pair->key)){
            tree->current = aux;
            return aux->pair;
        }
        if (tree->lower_than(key, aux->pair->key)){
            aux = aux->left;
        } else{
            aux = aux->right;
        }
    }

    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
