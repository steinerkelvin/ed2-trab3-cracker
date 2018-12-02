#ifndef AVL_H
#define AVL_H

#include <stdbool.h>
#include "symbol.h"
#include "key.h"

// AVL associando valores do tipo Key a "Item"

typedef struct avl AVL;

struct avl {
    Key k;
    Item item;

    int b;
    AVL* left;
    AVL* right;
};

AVL* avl_search(AVL* tree, const Key* k);

int avl_height(AVL* tree);

int avl_insert(AVL** tree, const Key* k, Item item); // TODO remover

// void avl_print(AVL* tree);

void avl_destroy(AVL* a, cb_item_t cb_destroy);

// FUNCAO NOVA: AO FINAL, item APONTA PARA UM NOVO ITEM VAZIO OU PARA UM ITEM JÁ EXISTENTE ANTERIORMENTE; 
bool avl_get_or_add(AVL** tree, const Key* key, Item** ret);

#endif
