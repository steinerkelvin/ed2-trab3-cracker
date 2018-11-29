#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "avl.h"

#define HT_SIZE 67867967


typedef struct {
    AVL** table;
    int nItems;
} HashTable;

HashTable* HT_create();

void HT_destroy(HashTable* hs);

void HT_insert(HashTable* hs, const Key* k, int n);

int HT_get(HashTable* hs, const Key* k);


#endif // HASH_TABLE_H
