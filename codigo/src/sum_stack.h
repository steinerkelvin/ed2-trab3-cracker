#if !defined(SUM_STACK_H)
#define SUM_STACK_H

#include <assert.h>
#include "util.h"
#include "key.h"

typedef struct sum_stack {
    // perDigitTable a partir do vetor para o primeiro caractere delegado
    Key *perDigitTable;
    int c;  // número de caracteres delegado à pilha
    int dp; // profundidade atual
    // bool finish;

    Key pos;
    Key sums[C+1];  

} SumStack;

static inline bool SumStack_running(SumStack *stack) {
    return stack->dp;
}

static inline Key* SumStack_getKey(SumStack *stack) {
    return &(stack->pos);
}

static inline Key* SumStack_getSum(SumStack *stack) {
    return &(stack->sums[stack->c]);
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

void SumStack_calc(SumStack *st) {
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
    assert(st->dp == st->c);
}

bool SumStack_next(SumStack *st) {
    // incrementa a chave e desempilha de acordo com o carries
    while ( st->dp && (++st->pos.digit[st->dp-1]) == R ) {
        st->pos.digit[st->dp-1] = 0;
        st->dp--;
    }
    return st->dp;
}


#endif // SUM_STACK_H