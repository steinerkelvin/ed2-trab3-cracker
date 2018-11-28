#ifndef HASH_H
#define HASH_H

#include "avl.h"

#define PRIME 67867967

typedef struct{
    AVL* table[PRIME];
    int nItems;
}HashTable;

HashTable* newHash();

void insert_hash(HashTable* hs, Key k, int n);

int hashAt(HashTable* hs, Key k);

#endif
