#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "symbol.h"
#include "key.h"
#include "avl.h"

#define HT_SIZE 67867967


typedef struct hash_table {
    AVL** table;
    int nItems;
} HashTable;

HashTable* HT_create();

void HT_destroy(HashTable* hs);

void HT_insert(HashTable* hs, const Key* k, Item item);

int HT_get(HashTable* hs, const Key* k, Item* ret);


#endif // HASH_TABLE_H
