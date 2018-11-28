#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "avl.h"
#include "key.h"

HashTable* newHash(){
    HashTable* hs = malloc(sizeof(HashTable));
    return hs;
}

unsigned int adler_hash(Key k) {
    unsigned int s1 = 1;
    unsigned int s2 = 0;
    for(int i = 0; i < C; i++) {
        s1 = (s1 + k.digit[i]) % 65521;
        s2 = (s1 + s2) % 65521;
    }
    return ((s2 << 16) | s1) % PRIME;
}

void insert_hash(HashTable* hs, Key k, int n) {
    hs->nItems++;
    avl_insert(&hs->table[adler_hash(k)], k, n);
}

int hashAt(HashTable* hs, Key k) {
    AVL* avl = recursiveSearch(hs->table[adler_hash(k)], k);
    if (avl == NULL) return -1;
    else return avl->n;
}


