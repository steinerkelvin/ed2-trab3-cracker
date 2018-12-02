#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include "symbol.h"
#include "key.h"
#include "avl.h"

#define HT_SIZE 67867967


typedef struct hash_table {
    AVL** table;
    int nItems;
} HashTable;

HashTable* HT_create();

void HT_destroy(HashTable* hs, cb_item_t cb_destroy);

/**
 * Busca um entrada na tabela para uma dada chave
 * parametros:
 *   ret -> [retorna] o valor armazenado
 * retorna: se encontrou
 */
bool HT_search(const HashTable* hs, const Key* k, Item* ret);

/**
 * Busca ou cria um entrada na tabela para uma dada chave
 * parametros:  
 *   key -> chave a ser buscada
 *   ret -> [retorna] ponteiro para o valor armazenado
 * retorna: se houve inserção
 */
bool HT_getOrAdd(HashTable* hs, const Key* k, Item** ret);


#endif // HASH_TABLE_H
