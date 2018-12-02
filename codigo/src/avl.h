#ifndef AVL_H
#define AVL_H

#include "symbol.h"
#include "key.h"

// AVL para o tipo Key.

typedef struct avl AVL;

struct avl {
    Key k;
    Item item;

    int b;
    AVL* left;
    AVL* right;
};

AVL* avl_search(AVL* b, const Key* k);

int avl_height(AVL* tree);

int avl_insert(AVL** tree, const Key* k, Item item);

void avl_print(AVL* tree);

void avl_destroy(AVL* a, cb_item_t cb_destroy);

// FUNCAO NOVA: AO FINAL, item APONTA PARA UM NOVO ITEM VAZIO OU PARA UM ITEM JÁ EXISTENTE ANTERIORMENTE; 
int avl_search_or_add(AVL** tree, const Key* key, Item* item);

#endif
