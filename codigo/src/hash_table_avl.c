#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "avl.h"

typedef struct hash_table {
    AVL** table;
    int numItems;
} HashTable;

HashTable* HT_create(int num_max) {
    #if FIXED_SPACE
        avl_reserve_space(num_max);
    #endif
    HashTable* hs = malloc(sizeof(HashTable));
    assert(hs);
    hs->table = malloc(sizeof(AVL*) * HT_SIZE);
    assert(hs->table);
    for (int i = 0; i < HT_SIZE; i++) {
        hs->table[i] = NULL;
    }
    hs->numItems = 0;
    return hs;
}

void HT_destroy(HashTable* hs, cb_value_t cb_destroy) {
    assert(hs);
    #if FIXED_SPACE
        avl_free_space();
    #else
        for (int i = 0; i < HT_SIZE; i++) {
            avl_destroy(hs->table[i], cb_destroy);
        }
    #endif
    free(hs->table);
    free(hs);
}


static uint_t Key_hash_horner(const Key* k) {
    uint_t h = 0;
    for (int i = 0; i < C; i++) {
        h = (31*h + k->digit[i]) % HT_SIZE;
    }
    return h;
}

bool HT_search(const HashTable* hs, const Key* k, Value* ret) {
    uint_t hash = Key_hash_horner(k);
    AVL* avl = avl_search(hs->table[hash], k);
    if (avl == NULL)
        return false;
    (*ret) = avl->item;
    return true;
}

bool HT_getOrAdd(HashTable* hs, const Key* k, Value** ret) {
	uint_t hash = Key_hash_horner(k);
    const bool ins = avl_get_or_add(&(hs->table[hash]), k, ret);
	if (ins)
        hs->numItems++;
    return ins;
}
