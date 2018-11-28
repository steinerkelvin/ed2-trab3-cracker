#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "key.h"

//AVL modificada para ser usada na hashtable para o tipo Key.

AVL* recursiveSearch(AVL* b, Key k) {
    if (b == NULL) return NULL;
    if (strcmp(b->k.digit,k.digit) == 0) return b;
    if (strcmp(b->k.digit,k.digit) < 0) return recursiveSearch(b->right,k);
    else return recursiveSearch(b->right,k);
}

int height(AVL* tree){
    if(tree){
	   return tree->b;
    }
	return -1;
}

int balancing(AVL* tree){
    return labs(height(tree->left)-height(tree->right));
}

int returnsGreater(int x, int y){
    return ((x > y) ? x : y);
}

void rotateLeft(AVL** tree){
    AVL* temp = (*tree)->left;
    (*tree)->left = temp->right;
    temp->right = *tree;
    (*tree)->b = returnsGreater(height((*tree)->left), height((*tree)->right)) + 1;
    temp->b = returnsGreater(height(temp->left), (*tree)->b) + 1;
    *tree = temp;
}

void rotateRight(AVL** tree){
    AVL* temp = (*tree)->right;
    (*tree)->right = temp->left;
    temp->left = (*tree);
    (*tree)->b = returnsGreater(height((*tree)->left),height((*tree)->right)) + 1;
    temp->b = returnsGreater(height(temp->right), (*tree)->b) + 1;
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
	printf("inserindo %d\n",num);
    int res;
    if(!(*tree)){
        AVL* aux = malloc(sizeof(AVL));
        aux->k = k; aux->n = num; aux->b = 0; aux->left = aux->right = NULL;
        (*tree) = aux;
        return 1;
    }

    AVL* temp = (*tree);
    if(num < temp->n){
        if((res = avl_insert((&(temp->left)), k, num)) == 1)
            if(balancing(temp) >= 2){
                if( num < (*tree)->left->n )
                    rotateLeft(tree);
                else
                    rotateLR(tree);
            }
    }
    else{
        if((res = avl_insert((&(temp->right)), k, num)) == 1)
            if(balancing(temp) >= 2) {
                if(num >= (*tree)->right->n) rotateRight(tree);
                else rotateRL(tree);
            }
    }

    temp->b = returnsGreater( height(temp->left), height(temp->right) ) + 1;

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
  return;
}
