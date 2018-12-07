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
    HashTable *table,
    int p_st,
    int c_st,
    Key perDigitTable[C][R]
) {
    int sobreescritas = 0;

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


    // fprintf(stderr, "hashmap size: %d\n", table->numItems);
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


    // Tabela de símbolos preenchida para `c_st` caracteres

    int p_st = 0;                   // primeira posição
    int c_st = MIN(C/2, C_TABLE);   // número de caracteres delegados
    int pos = c_st;

    fprintf(stderr, "c_st: %d\n", c_st);

    const int n_st = (1<<(B*c_st));

    #if FIXED_SPACE
        KeyPart_reserveSpace(c_st, n_st);
    #endif

    HashTable* map = HT_create(n_st);
    buildSymbolTable(map, p_st, c_st, perDigitTable);


    // Cálculo do resto das combinações utilizando a pilha de somas

    int p_br = pos;
    int c_br = (C-pos);

    fprintf(stderr, "c_br: %d\n", c_br);

    {
        SumStack stack = SumStack_create(c_br, (Key*)perDigitTable[p_br]);
        Key *stKey = SumStack_getKey(&stack);
        Key *stSum = SumStack_getSum(&stack);

        do {
            SumStack_calc(&stack);

            Key needed; Key_sub(&needed, &target, stSum);
            Value rest; bool has = HT_search(map, &needed, &rest);
            if (has) {
                Key result;
                KeyPart_copyTo(c_st, p_st, rest, &result);
                KeyPart_copyTo(c_br, p_br, stKey->digit, &result);
                print_key_char(result);
            }

        } while (SumStack_next(&stack));
    }

    fprintf(stderr, "LIBERANDO\n");

    #if FIXED_SPACE
        KeyPart_freeSpace();
        HT_destroy(map, (cb_value_t)Value_nope);
    #else
        HT_destroy(map, (cb_value_t)free);
    #endif

    return 0;
}

