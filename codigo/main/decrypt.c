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



/**
 * Preenche a tabela de símbolos utilizando a pilha de somas para produzir as
 * somas das combinações de `c_tbl`
 */
HashTable* buildSymbolTable(
    HashTable *table,
    int p_tbl,
    int c_tbl,
    Key perDigitTable[C][R]
) {
    int sobreescritas = 0;

    SumStack stack = SumStack_create(c_tbl, (Key*)perDigitTable[p_tbl]);
    Key *stKey = SumStack_getKey(&stack);
    Key *stSum = SumStack_getSum(&stack);

    do {
        SumStack_calc(&stack);

        Value *pvalue;
        bool ins = HT_getOrAdd(table, stSum, &pvalue);
        if (ins) {
            *pvalue = KeyPart_create(c_tbl, 0, stKey);
        } else {
            //! TODO: TRATAR COLISÕES
            // utilizar lista de partes-de-chave para armazenar múltiplas chaves
            sobreescritas++;
        }

    } while (SumStack_next(&stack));


    // fprintf(stderr, "hashmap size: %d\n", table->numItems); //* DEBUG
    // fprintf(stderr, "chaves sobreescritas: %d\n", sobreescritas); //* DEBUG

    return table;
}

int main(int argc, char* argv[]) {
    check_params(argc, argv);
    Key target = init_key((uchar_t*) argv[1]);

    Key table[N];
    Key_readTable(table);
    perDigitTable_build(perDigitTable, table);


    // ==== Cria tabela de símbolos para combinações de `c_tbl` caracteres ====

    int p_tbl = 0;                   // primeira posição
    int c_tbl = MIN(C/2, C_TABLE);   // número de caracteres delegados
    int pos = c_tbl;
    // fprintf(stderr, "c_tbl: %d\n", c_tbl); //* DEBUG

    // Reserva espaço para os valores da tabela
    const int n_tbl = (1<<(B*c_tbl));
    #if FIXED_SPACE
        KeyPart_reserveSpace(c_tbl, n_tbl);
    #endif

    HashTable* map = HT_create(n_tbl);
    buildSymbolTable(map, p_tbl, c_tbl, perDigitTable);


    // ==== Faz combinações para o resto da chave utilizando pilha de somas ====

    int p_stk = pos;     // primeira posição
    int c_br = (C-pos); // número de caracteres delegados

    // fprintf(stderr, "c_br: %d\n", c_br); //* DEBUG

    {
        SumStack stack = SumStack_create(c_br, (Key*)perDigitTable[p_stk]);
        Key *stKey = SumStack_getKey(&stack);
        Key *stSum = SumStack_getSum(&stack);

        do {
            SumStack_calc(&stack);

            Key needed; Key_sub(&needed, &target, stSum);
            Value rest; bool has = HT_search(map, &needed, &rest);
            if (has) {
                Key result;
                KeyPart_copyTo(c_tbl, p_tbl, rest, &result);
                KeyPart_copyTo(c_br, p_stk, stKey->digit, &result);
                print_key_char(result);
            }

        } while (SumStack_next(&stack));
    }

    // fprintf(stderr, "Liberando...\n");  //* DEBUG

    #if FIXED_SPACE
        KeyPart_freeSpace();
        HT_destroy(map, (cb_value_t)Value_nope);
    #else
        HT_destroy(map, (cb_value_t)free);
    #endif

    return 0;
}

