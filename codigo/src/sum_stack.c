#include "sum_stack.h"

Key* SumStack_getKey(SumStack *stack) {
    return &(stack->pos);
}

Key* SumStack_getSum(SumStack *stack) {
    return &(stack->sums[stack->c]);
}

SumStack SumStack_create(int c, Key *perDigitTable) {
    assert(c >= 0);

    SumStack stack;
    stack.pos = (Key){{0}};
    stack.sums[0] = (Key){{0}};

    stack.perDigitTable = perDigitTable;    
    stack.c = c;
    stack.dp = 1;

    return stack;
}

void SumStack_calc(SumStack *st) {
    // garante o preenchimento da pilha
    while (st->dp <= st->c) {
        int pos = st->dp - 1;
        const uchar_t digit = st->pos.digit[pos];
        const Key *digitSum = (st->perDigitTable + R*pos + digit);
        Key_add(
            &st->sums[st->dp],
            &st->sums[pos],
            digitSum
        );
        st->dp++;
    }
    st->dp--;
}

bool SumStack_next(SumStack *st) {
    // incrementa a chave e desempilha de acordo com o carries
    while ( st->dp && (++st->pos.digit[st->dp-1]) == R ) {
        st->pos.digit[st->dp-1] = 0;
        st->dp--;
    }
    return st->dp;
}
