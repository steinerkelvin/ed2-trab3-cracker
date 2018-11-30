#include "per_digit.h"

void perDigitTable_build(Key perDigitTable[C][R], Key table[N]) {
    for (int i=0; i < C; i++) {
        for (int j = 0; j < R; j++) {
            Key key = {{0}};
            key.digit[i] = j;
            perDigitTable[i][j] = subset_sum(key, table);
        }
    }
}

Key perDigitTable_sum(const Key perDigitTable[C][R], const Key *key) {
    Key sum = {{0}};
    for (int i = 0; i < C; i++) {
        int d = key->digit[i];
        sum = add(sum, perDigitTable[i][d]);
    }
    return sum;
}
