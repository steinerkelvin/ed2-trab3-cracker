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

    int b;  //? mudar de nome ?
    AVL* left;
    AVL* right;
};

// TODO comentar

void avl_destroy(AVL* a, cb_item_t cb_destroy);

int avl_height(const AVL* tree);

AVL* avl_search(AVL* tree, const Key* k);

// void avl_print(AVL* tree);

/** Busca ou cria um nó para uma dada chave
 * parametros:  
 *   key -> chave a ser buscada
 *   ret -> [retorna] ponteiro para o item
 * retorna: se houve inserção
 */
bool avl_get_or_add(AVL** tree, const Key* key, Item** ret);

#endif
