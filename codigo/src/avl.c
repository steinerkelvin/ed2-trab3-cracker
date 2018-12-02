#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "key.h"

// AVL modificada para ser usada na hashtable para o tipo Key.

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

int avl_height(AVL* tree){
    if (tree == NULL) return -1;
    return tree->b;
}

static int balancing(AVL* tree){
    if (tree == NULL) return 0;
    return avl_height(tree->left) - avl_height(tree->right);
}

static int max(int x, int y){
    return ((x > y) ? x : y);
}

static void rotateRight(AVL** tree){
    AVL* temp = (*tree)->left;
    (*tree)->left = temp->right;
    temp->right = *tree;
    (*tree)->b = max(avl_height((*tree)->left), avl_height((*tree)->right)) + 1;
    temp->b = max(avl_height(temp->left), (*tree)->b) + 1;
    *tree = temp;
}

static void rotateLeft(AVL** tree){
    AVL* temp = (*tree)->right;
    (*tree)->right = temp->left;
    temp->left = (*tree);
    (*tree)->b = max(avl_height((*tree)->left),avl_height((*tree)->right)) + 1;
    temp->b = max(avl_height(temp->right), (*tree)->b) + 1;
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

int avl_insert(AVL** tree, const Key* key, Item item){
    if(!(*tree)){
        AVL* aux = malloc(sizeof(AVL));
        aux->k = *key;
        aux->item = item;
        aux->b = 0;
        aux->left = aux->right = NULL;
        (*tree) = aux;
        return 1;
    }

    int res = 0;
    AVL* temp = (*tree);
    if(Key_compare(key, &temp->k) < 0){
        if((res = avl_insert((&(temp->left)), key, item)) == 1)
            if(balancing(temp) >= 2) {
                if( Key_compare(key, &temp->left->k ) < 0 )
                    rotateRight(tree);
                else
                    rotateLR(tree);
            }
    } else {
        if((res = avl_insert((&(temp->right)), key, item)) == 1)
            if(balancing(temp) >= 2) {
                if( Key_compare(key, &temp->right->k ) >= 0 )
                    rotateLeft(tree);
                else
                    rotateRL(tree);
            }
    }

    temp->b = max( avl_height(temp->left), avl_height(temp->right) ) + 1;

    return res;
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

void avl_destroy(AVL* node, cb_item_t cb_destroy){
    if (node == NULL) return;
    avl_destroy(node->left, cb_destroy);
    avl_destroy(node->right, cb_destroy);
    if (cb_destroy != NULL)
        cb_destroy(node->item);
    free(node);
}

// Busca ou cria um nó para uma dada chave
// param:  
//   [saida] ret -> retorna ponteiro para o item
// retorna: se houve inserção
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

        temp->b = max( avl_height(temp->left), avl_height(temp->right) ) + 1;
    }

    return ins;
}
