#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "avl.h"
#include "key.h"

// AVL modificada para ser usada na hashtable para o tipo Key.

void avl_destroy(AVL* node, cb_item_t cb_destroy){
    if (node == NULL) return;
    avl_destroy(node->left, cb_destroy);
    avl_destroy(node->right, cb_destroy);
    if (cb_destroy != NULL)
        cb_destroy(node->item);
    free(node);
}

int avl_height(const AVL* tree){
    if (tree == NULL) return -1;
    return tree->b;
}

AVL* avl_search(AVL* tree, const Key* k) {
    if (tree == NULL)
        return NULL;
    int diff = Key_compare(k, &tree->k);
    if (diff == 0)
        return tree;
    if (diff > 0)
        return avl_search(tree->right, k);
    else
        return avl_search(tree->left, k);
}

static void rotateRight(AVL** tree){
    AVL* temp = (*tree)->left;
    (*tree)->left = temp->right;
    temp->right = *tree;
    (*tree)->b = MAX(avl_height((*tree)->left), avl_height((*tree)->right)) + 1;
    temp->b = MAX(avl_height(temp->left), (*tree)->b) + 1;
    *tree = temp;
}

static void rotateLeft(AVL** tree){
    AVL* temp = (*tree)->right;
    (*tree)->right = temp->left;
    temp->left = (*tree);
    (*tree)->b = MAX(avl_height((*tree)->left),avl_height((*tree)->right)) + 1;
    temp->b = MAX(avl_height(temp->right), (*tree)->b) + 1;
    *tree = temp;
}

static void rotateRL(AVL** tree){
    rotateRight(&((*tree)->right));
    rotateLeft(tree);
}

static void rotateLR(AVL** tree){
    rotateLeft(&((*tree)->left));
    rotateRight(tree);
}

// void avl_print(AVL* tree){
//     printf("(");
//     if(tree) {
//         printf("%d ", tree->item);
//         avl_print(tree->left);
//         avl_print(tree->right);
//     }
//     printf(")");
// }

static inline int balancing(AVL* tree){
    if (tree == NULL) return 0;
    return avl_height(tree->left) - avl_height(tree->right);
}

bool avl_get_or_add(AVL** tree, const Key* key, Item** ret){
    if(!(*tree)){
        AVL* aux = malloc(sizeof(AVL));
        aux->k = *key;
        aux->item = Item_NULL;
        (*ret) = &(aux->item);
        aux->b = 0;
        aux->left = aux->right = NULL;
        (*tree) = aux;
        return true;
    }

    AVL* temp = (*tree);
    int diff = Key_compare(key, &temp->k);
	if(diff == 0) {
		(*ret) = &(temp->item);
		return false;
	}

    AVL** child = (diff < 0) ? (&(temp->left)) : (&(temp->right));
    const bool ins = avl_get_or_add(child, key, ret);
    if (ins) {
        const int bal = balancing(temp);
        if (bal > 1) {
            int lbal = balancing(temp->left);
            if      (lbal > 0) rotateRight(tree);
            else if (lbal < 0) rotateLR(tree);
        } else if (bal < -1) {
            int rbal = balancing(temp->right);
            if      (rbal < 0)  rotateLeft(tree);
            else if (rbal > 0)  rotateRL(tree);
        }

        temp->b = MAX( avl_height(temp->left), avl_height(temp->right) ) + 1;
    }

    return ins;
}
