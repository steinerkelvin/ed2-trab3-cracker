#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "util.h"
#include "key.h"

#define VALUE_PTR_TYPE Digit
#define VALUE_NULL NULL
#define C_TABLE 4       // 5
#define HT_SIZE 2097143 // 33554393

#include "table.h"
#include "key_part.h"
#include "per_digit.h"
#include "sum_stack.h"
#include "hash_table.h"

Key perDigitTable[C][R];

//bool Key_isMaxFrom(const Key *k, const int lo, const int hi) {
//    for (int i = hi; i >= lo; i--) {
//        if (k->digit[i] != (R-1))
//            return 0;
//    }
//    return 1;
//}

uchar_t* value_create(const uchar_t* key, const int size) {
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

    int pos = 0;

    int p_st = pos;
    int c_st = C_TABLE;
    pos += c_st;

    int sobreescritas = 0;

    HashTable* map = HT_create();

    // Preenche 
    {
        SumStack stack = SumStack_create(c_st, (Key*)perDigitTable[p_st]);
        Key *pkey = SumStack_getKey(&stack);
        Key *psum = SumStack_getSum(&stack);

        do {
            SumStack_calc(&stack);

            Value *pvalue;
            bool ins = HT_getOrAdd(map, psum, &pvalue);
            if (ins) {
                *pvalue = KeyPart_from(c_st, p_st, pkey);
            } else {
                // TODO utilizar lista de partes-de-chave para armazenar
                // múltiplas em vez de descartar
                sobreescritas++;
            }

        } while (SumStack_next(&stack));

    }

    fprintf(stderr, "hashmap size: %d\n", map->numItems);
    fprintf(stderr, "chaves sobreescritas: %d\n", sobreescritas);

    // Brute force
    {
        int p_br = pos;
        int c_br = (C-pos);

        SumStack stack = SumStack_create(c_br, (Key*)perDigitTable[p_br]);
        Key *pkey = SumStack_getKey(&stack);
        Key *psum = SumStack_getSum(&stack);

        do {
            SumStack_calc(&stack);

            Key needed; Key_sub(&needed, &target, psum);
            Value rest; bool has = HT_search(map, &needed, &rest);
            if (has) {
                Key result;
                KeyPart_copyTo(c_st, p_st, rest, &result);
                KeyPart_copyTo(c_br, p_br, pkey->digit, &result);
                print_key_char(result);
            }

        } while (SumStack_next(&stack));
    }

    HT_destroy(map, (cb_value_t)free);

    return 0;
}
