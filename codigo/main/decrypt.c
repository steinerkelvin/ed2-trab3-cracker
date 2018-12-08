#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define VALUE_PTR_TYPE PartList
#define VALUE_NULL NULL

#include "util.h"
#include "key.h"
#include "part_list.h"
#include "table.h"
#include "part_list.h"
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
    int colisoes = 0;

    SumStack stack = SumStack_create(c_tbl, (Key*)perDigitTable[p_tbl]);
    Key *stKey = SumStack_getKey(&stack);
    Key *stSum = SumStack_getSum(&stack);

    do {
        SumStack_calc(&stack);

        PartList **plist;
        bool ins = HT_getOrAdd(table, stSum, &plist); // TRIPLE POINTER :D
        if (!ins) {
            colisoes++;
        }
        PartList_insert(plist, c_tbl, p_tbl, stKey);

    } while (SumStack_next(&stack));


    // fprintf(stderr, "hashmap size: %d\n", table->numItems); //* DEBUG
    // fprintf(stderr, "colisoes: %d\n", colisoes); //* DEBUG

    return table;
}

int main(int argc, char* argv[]) {
    check_params(argc, argv);
    Key target = init_key((uchar_t*) argv[1]);

    Key table[N];
    Key_readTable(table);
    perDigitTable_build(perDigitTable, table);


    // ==== Cria tabela de símbolos para combinações de `c_tbl` caracteres ====

    int p_tbl = 0;                   
    // Número de caracteres delegados à tabela (no máximo metade da senha)
    int c_tbl = MIN(C/2, C_TABLE);   
    int pos = c_tbl;
    // fprintf(stderr, "c_tbl: %d\n", c_tbl); //* DEBUG

    // Reserva espaço para os valores da tabela
    const int n_tbl = (1<<(B*c_tbl));
    #if FIXED_SPACE
        parts_reserveSpace(c_tbl, n_tbl);
    #endif

    HashTable* map = HT_create(n_tbl);
    buildSymbolTable(map, p_tbl, c_tbl, perDigitTable);


    // ==== Faz combinações para o resto da chave utilizando pilha de somas ====

    int p_stk = pos;    // primeira posição
    int c_br = (C-pos); 
    // fprintf(stderr, "c_br: %d\n", c_br); //* DEBUG

    {
        SumStack stack = SumStack_create(c_br, (Key*)perDigitTable[p_stk]);
        Key *stKey = SumStack_getKey(&stack);
        Key *stSum = SumStack_getSum(&stack);

        // Para cada combinação do resto da chave
        do {
            SumStack_calc(&stack);

            // subtrai do hash alvo
            Key needed; Key_sub(&needed, &target, stSum);
            // e consulta na tabela
            PartList *list;
            bool has = HT_search(map, &needed, &list);
            if (has) {
                Key result;
                copy_digits_to(c_br, p_stk, stKey->digit, &result);

                // Imprime para todas as chaves associadas à soma encontrada
                for (; list != NULL; list = list->next) {
                    copy_digits_to(c_tbl, p_tbl, list->part, &result);
                    print_key_char(result);
                }
            }

        } while (SumStack_next(&stack));
    }

    // fprintf(stderr, "Liberando...\n");  //* DEBUG

    #if FIXED_SPACE
        parts_freeSpace();
        HT_destroy(map, (cb_value_t)Value_nope);
    #else
        HT_destroy(map, (cb_value_t)PartList_free);
    #endif

    return 0;
}

