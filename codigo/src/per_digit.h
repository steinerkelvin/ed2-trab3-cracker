#if !defined(PER_DIGIT_H)
#define PER_DIGIT_H

#include "key.h"

void perDigitTable_build(Key perDigitTable[C][R], Key table[N]);

Key perDigitTable_sum(Key perDigitTable[C][R], const Key* key);

#endif // PER_DIGIT_H