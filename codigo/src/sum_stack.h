#if !defined(SUM_STACK_H)
#define SUM_STACK_H

#include <assert.h>
#include "util.h"
#include "key.h"

typedef void (*cb_sum_t)(int c, const Key* key, const Key* sum);

typedef struct sum_stack {
    // perDigitTable a partir do vetor para o primeiro caractere delegado
    Key *perDigitTable;
    int c;  // número de caracteres delegado à pilha
    int dp; // profundidade atual
    // bool finish;

    Key pos;
    Key sums[C+1];  

} SumStack;

static inline bool SumStack_running(const SumStack *stack) {
    return stack->dp;
}

SumStack SumStack_create(int c, Key *perDigitTable) {
    SumStack stack;
    stack.pos = (Key){{0}};
    stack.sums[0] = (Key){{0}};

    stack.perDigitTable = perDigitTable;    
    stack.c = c;
    stack.dp = 1;
    // stack.finish = 0;

    return stack;
}

bool SumStack_next(SumStack *st, cb_sum_t cb) {
    assert(st->dp);
    // garante o preenchimento da pilha
    while (st->dp <= st->c) {
        int prt = st->dp - 1;
        const uchar_t digit = st->pos.digit[prt];
        const Key *digitSum = (st->perDigitTable + R*prt + digit);
        Key_add(
            &st->sums[st->dp],
            &st->sums[prt],
            digitSum
        );
        st->dp++;
    }
    st->dp--;

    // assert(st->dp == st->c+1);
    // retorna o valor recem calculado
    cb(st->c, &st->pos, &st->sums[st->c]);

    // incrementa a chave e desempilha de acordo com o carries
    while ( st->dp && (++st->pos.digit[st->dp-1]) == R ) {
        st->pos.digit[st->dp-1] = 0;
        st->dp--;
    }
    return st->dp;
}


#endif // SUM_STACK_H
