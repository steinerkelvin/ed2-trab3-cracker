#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "avl.h"
#include "key.h"

HashTable* HT_create() {
    HashTable* hs = malloc(sizeof(HashTable));
    hs->table = malloc(sizeof(AVL*) * HT_SIZE);
    for (int i = 0; i < HT_SIZE; i++) {
        hs->table[i] = NULL;
    }
    hs->nItems = 0;
    return hs;
}

void HT_destroy(HashTable* hs) {
    free(hs->table);
    free(hs);
}

static uint_t Key_hash_adler(const Key* k) {
    uint_t s1 = 1;
    uint_t s2 = 0;
    for(int i = 0; i < C; i++) {
        s1 = (s1 + k->digit[i]) % 65521;
        s2 = (s1 + s2) % 65521;
    }
    return ((s2 << 16) | s1) % HT_SIZE;
}

void HT_insert(HashTable* hs, const Key* k, int n) {
    uint_t hash = Key_hash_adler(k);
    hs->nItems++;
    avl_insert(&hs->table[hash], *k, n);
}

int HT_get(HashTable* hs, const Key* k) {
    uint_t hash = Key_hash_adler(k);
    AVL* avl = avl_search(hs->table[hash], k);
    return (avl) ? avl->n : -1;
}
