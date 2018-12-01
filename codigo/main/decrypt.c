#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define ST_ITEM_TYPE uchar_t

#include "key.h"
#include "util.h"
#include "per_digit.h"
#include "hash_table.h"

#define MAXC_ST 4

Key perDigitTable[C][R];

bool Key_isMaxFrom(const Key *k, const int lo, const int hi) {
    for (int i = hi; i >= lo; i--) {
        if (k->digit[i] != (R-1))
            return 0;
    }
    return 1;
}

uchar_t* st_key_create(const uchar_t* key, const int size) {
    uchar_t* p = malloc(sizeof(uchar_t) * size);
    for (int i = 0; i < size; i ++) {
        p[i] = key[i];
    }
    return p;
}

int main(int argc, char* argv[]) {
    check_decrypt_params(argc, argv);

    Key table[N];
    for (int i = 0; i < N; i++) {
        uchar_t aux[C];
        scanf("%s",aux);
        table[i] = init_key(aux);
    }
    Key target = init_key((uchar_t*) argv[1]);
    perDigitTable_build(perDigitTable, table);

    int pc = 0;
    int p_st = pc;
    int c_st = MIN(MAXC_ST, (C-pc)-1);

    HashTable* map = HT_create();
    {
        pc += c_st;
        const int lstc = p_st + c_st - 1;

        Key one = {{0}};
        one.digit[lstc] = 1;
        for (Key key = {{0}}; ; Key_add(&key, &key, &one)) {
            // print_key(key);

            Key sum = perDigitTable_sum(perDigitTable, &key);

            Item value = st_key_create(&key.digit[p_st], c_st);
            HT_insert(map, &sum, value);

            if (Key_isMaxFrom(&key, p_st, lstc))
                break;
        }
    }

    fprintf(stderr, "hashmap size: %d\n", map->nItems);

    {
        int p_br = pc;
        int c_br = (C-pc);
        pc += c_br;
        const int lstc = p_br + c_br - 1;

        Key one = {{0}};
        one.digit[lstc] = 1;
        for (Key key = {{0}}; ; Key_add(&key, &key, &one)) {
            Key partial = perDigitTable_sum(perDigitTable, &key);
            Key needed; Key_sub(&needed, &target, &partial);

            Item rest;
            bool has = HT_get(map, &needed, &rest);
            if (has) {
                Key k = key;
                for (int i = 0; i < c_st; i++)
                    k.digit[p_st+i] = rest[i];
                print_key_char(k);
            }

            if (Key_isMaxFrom(&key, p_br, lstc))
                break;
        }
    }

    HT_destroy(map, (cb_item_t)free);

    return 0;
}
