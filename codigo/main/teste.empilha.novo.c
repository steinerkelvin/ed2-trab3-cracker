#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "key.h"
#include "util.h"
#include "per_digit.h"
#include "sum_stack.h"

Key perDigitTable[C][R];

Key target;

void verify(int c, const Key *key, const Key *sum) {
    if (Key_isEqual(sum, &target))
        print_key_char(*key);
}

int main(int argc, char* argv[]) {
    check_decrypt_params(argc, argv);

	Key table[N];
	for (int i = 0; i < N; i++) {
		uchar_t aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

	// Key in = init_key((uchar_t*) argv[1]);
    target = init_key((uchar_t*) argv[1]);;

    perDigitTable_build(perDigitTable, table);

    SumStack stack = SumStack_create(C, (Key*)perDigitTable);

    while (SumStack_next(&stack, verify)) { }

	return 0;
}
