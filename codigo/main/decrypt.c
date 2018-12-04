#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "util.h"

#define VALUE_PTR_TYPE uchar_t
#define VALUE_NULL NULL
#define MAXC_TABLE 4
#define HT_SIZE 2097143

#include "table.h"
#include "key.h"
#include "per_digit.h"
#include "hash_table.h"


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
    int c_st = MIN(MAXC_TABLE, (C-pc)-1);

    int sobreescritas = 0;
    HashTable* map = HT_create();
    {
        pc += c_st;
        const int lstc = p_st + c_st - 1;

        Key one = {{0}};
        one.digit[lstc] = 1;
        for (Key key = {{0}}; ; Key_add(&key, &key, &one)) {
            // print_key(key);

            Key sum = perDigitTable_sum(perDigitTable, &key);

            Value *pvalue;
            bool ins = HT_getOrAdd(map, &sum, &pvalue);
            if (ins) {
                *pvalue = st_key_create(&key.digit[p_st], c_st);
            } else {
                sobreescritas++;
            }

            if (Key_isMaxFrom(&key, p_st, lstc))
                break;
        }
    }

    fprintf(stderr, "hashmap size: %d\n", map->numItems);
    fprintf(stderr, "chaves sobreescritas: %d\n", sobreescritas);

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

            Value rest;
            bool has = HT_search(map, &needed, &rest);
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

    HT_destroy(map, (cb_value_t)free);

    return 0;
}
