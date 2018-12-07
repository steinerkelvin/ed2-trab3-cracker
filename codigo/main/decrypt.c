#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define VALUE_PTR_TYPE Digit
#define VALUE_NULL NULL

#include "util.h"
#include "key.h"
#include "table.h"
#include "key_part.h"
#include "per_digit.h"
#include "sum_stack.h"
#include "hash_table.h"

Key perDigitTable[C][R];

void Value_nope(Value* val) { }


static inline Key* mat_get_pos(Key *mat, int c_mat, Digit *digits) {
    size_t range = (1 << (B*c_mat));
    for (int i = 0; i < c_mat; i++) {
        range >>= B;
        mat += (range) * digits[i];
    }
    return mat;
}

HashTable* buildSymbolTable(
    int p_st,
    int c_st,
    Key perDigitTable[C][R]
) {
    int sobreescritas = 0;
    HashTable* table = HT_create();

    SumStack stack = SumStack_create(c_st, (Key*)perDigitTable[p_st]);
    Key *stKey = SumStack_getKey(&stack);
    Key *stSum = SumStack_getSum(&stack);

    do {
        SumStack_calc(&stack);

        Value *pvalue;
        bool ins = HT_getOrAdd(table, stSum, &pvalue);
        if (ins) {
            *pvalue = KeyPart_create(c_st, p_st, stKey);
        } else {
            //! TODO: TRATAR COLISÕES
            // utilizar lista de partes-de-chave para armazenar múltiplas chaves
            sobreescritas++;
        }

    } while (SumStack_next(&stack));


    fprintf(stderr, "hashmap size: %d\n", table->numItems);
    fprintf(stderr, "chaves sobreescritas: %d\n", sobreescritas);

    return table;
}

int main(int argc, char* argv[]) {
    check_decrypt_params(argc, argv);

    Key table[N];
    // TODO separar em função e tratar entrada
    for (int i = 0; i < N; i++) {
        uchar_t aux[C];
        scanf("%s",aux);
        table[i] = init_key(aux);
    }
    Key target = init_key((uchar_t*) argv[1]);
    perDigitTable_build(perDigitTable, table);


    // TABELA DE SÍMBOLOS //

    int p_st = 0;                   // primeira posição
    int c_st = MIN(C/2, C_TABLE);   // número de caracteres delegados
    int pos = c_st;

    fprintf(stderr, "c_st: %d\n", c_st);

    #if FIXED_SPACE
        const int n_st = (1<<(B*c_st));
        avl_reserve_space(n_st);
        KeyPart_reserveSpace(c_st, n_st);
    #endif

    HashTable* map = buildSymbolTable(p_st, c_st, perDigitTable);


    // MATRIZ DE SOMAS PRECOMPUTADAS //
    // TODO pensar uma maneira decente de iterar nessa matriz
    // do jeito que está a matriz não ajuda no desempenho

    #if MATRIX_ENABLE

    int p_mat = pos;
    int c_mat = MIN(C-pos, C_MATRIX);
    pos += c_mat;
    const ulong_t n_mat = 1 << (B * c_mat);

    fprintf(stderr, "c_mat: %d\n", c_mat);

    // Preenche matriz de somas precomputadas
    Key *sumMat = malloc( n_mat * sizeof(Key) );
    {
        SumStack stack = SumStack_create(c_mat, (Key*)perDigitTable[p_mat]);
        Key *stKey = SumStack_getKey(&stack);
        Key *stSum = SumStack_getSum(&stack);
        do {
            SumStack_calc(&stack);

            // Key ptKey = {{0}}; KeyPart_copyTo(c_mat, p_mat, stKey->digit, &ptKey);
            // print_key(ptKey);

            Key *pos = mat_get_pos(sumMat, c_mat, stKey->digit);
            *pos = *stSum;
        } while (SumStack_next(&stack));
    }

    #endif



    // BRUTE FORCE //

    int p_br = pos;
    int c_br = (C-pos);

    fprintf(stderr, "c_br: %d\n", c_br);

    {
        SumStack stack = SumStack_create(c_br, (Key*)perDigitTable[p_br]);
        Key *stKey = SumStack_getKey(&stack);
        Key *stSum = SumStack_getSum(&stack);

        do {
            SumStack_calc(&stack);

            #if MATRIX_ENABLE

            Key partial;
            Key *const ppartial = &partial;
            Digit index[c_mat];  for (int i=0; i < c_mat; i++) index[i] = 0;
            for (int i = 0; i < n_mat; i++)
            {
                Key *matSum = mat_get_pos(sumMat, c_mat, index);
                Key_add(&partial, matSum, stSum);
            #else
                Key *ppartial = stSum;
            #endif

                Key needed; Key_sub(&needed, &target, ppartial);
                Value rest; bool has = HT_search(map, &needed, &rest);
                if (has) {
                    Key result;
                    KeyPart_copyTo(c_st, p_st, rest, &result);
                    #if MATRIX_ENABLE
                        KeyPart_copyTo(c_mat, p_mat, index, &result);
                    #endif
                    KeyPart_copyTo(c_br, p_br, stKey->digit, &result);
                    print_key_char(result);
                }

            #if MATRIX_ENABLE
                KeyPart_inc(c_mat, index);
            }
            #endif

        } while (SumStack_next(&stack));
    }

    fprintf(stderr, "LIBERANDO\n");

    #if FIXED_SPACE
        KeyPart_freeSpace();
        avl_free_space();
        HT_destroy(map, (cb_value_t)Value_nope);
    #else
        HT_destroy(map, (cb_value_t)free);
    #endif

    #if MATRIX_ENABLE
    free(sumMat);
    #endif

    return 0;
}

