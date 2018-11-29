#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "key.h"

// AVL modificada para ser usada na hashtable para o tipo Key.

AVL* avl_search(AVL* b, const Key* k) {
    if (b == NULL)
        return NULL;
    int diff = Key_compare(k, &b->k);
    if (diff == 0)
        return b;
    if (diff > 0)
        return avl_search(b->right, k);
    else
        return avl_search(b->left, k);
}

int avl_height(AVL* tree){
    if(tree){
	   return tree->b;
    }
	return -1;
}

int balancing(AVL* tree){
    return labs(avl_height(tree->left)-avl_height(tree->right));
}

static int max(int x, int y){
    return ((x > y) ? x : y);
}

void rotateLeft(AVL** tree){
    AVL* temp = (*tree)->left;
    (*tree)->left = temp->right;
    temp->right = *tree;
    (*tree)->b = max(avl_height((*tree)->left), avl_height((*tree)->right)) + 1;
    temp->b = max(avl_height(temp->left), (*tree)->b) + 1;
    *tree = temp;
}

void rotateRight(AVL** tree){
    AVL* temp = (*tree)->right;
    (*tree)->right = temp->left;
    temp->left = (*tree);
    (*tree)->b = max(avl_height((*tree)->left),avl_height((*tree)->right)) + 1;
    temp->b = max(avl_height(temp->right), (*tree)->b) + 1;
    *tree = temp;
}

void rotateRL(AVL** tree){
    rotateLeft(&((*tree)->right));
    rotateRight(tree);
}

void rotateLR(AVL** tree){
    rotateRight(&((*tree)->left));
    rotateLeft(tree);
}

int avl_insert(AVL** tree, Key k, int num){
    if(!(*tree)){
        AVL* aux = malloc(sizeof(AVL));
        aux->k = k;
        aux->n = num;
        aux->b = 0;
        aux->left = aux->right = NULL;
        (*tree) = aux;
        return 1;
    }

    int res;
    AVL* temp = (*tree);
    if(Key_compare(&k, &temp->k) < 0){
        if((res = avl_insert((&(temp->left)), k, num)) == 1)
            if(balancing(temp) >= 2) {
                if( Key_compare(&k, &temp->left->k ) < 0 )
                    rotateLeft(tree);
                else
                    rotateLR(tree);
            }
    } else {
        if((res = avl_insert((&(temp->right)), k, num)) == 1)
            if(balancing(temp) >= 2) {
                if( Key_compare(&k, &temp->right->k ) >= 0 )
                    rotateRight(tree);
                else
                    rotateRL(tree);
            }
    }

    temp->b = max( avl_height(temp->left), avl_height(temp->right) ) + 1;

    return res;
}

void avl_print(AVL* tree){
    printf("(");
    if(tree) {
        printf("%d ", tree->n);
        avl_print(tree->left);
        avl_print(tree->right);
    }
    printf(")");
}

void avl_free(AVL* a){
    if (a == NULL) return;
    avl_free(a->left);
    avl_free(a->right);
    free(a);
}
