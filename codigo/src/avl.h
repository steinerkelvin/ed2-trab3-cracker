#ifndef AVL_H
#define AVL_H

// AVL para o tipo Key.

#include "key.h"

typedef struct avl AVL;

struct avl{
    Key k;
    int n;
    int b;
    AVL* left;
    AVL* right;
};

AVL* avl_search(AVL* b, const Key* k);

int avl_height(AVL* tree);

int avl_insert(AVL** tree, Key k, int num);

void avl_print(AVL* tree);

void avl_free(AVL* a);

#endif
