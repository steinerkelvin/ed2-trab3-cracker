#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "key.h"
#include "per_digit.h"

int main(int argc, char* argv[]) {
	check_params(argc, argv);

	Key table[N];
	Key perDigitTable[C][R];

	for (int i = 0; i < N; i++) {
		uchar_t aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

	Key in = init_key((uchar_t*) argv[1]);

    perDigitTable_build(perDigitTable, table);

	for (Key key = {{0}}; ; Key_inc(&key)) {

        Key sum = perDigitTable_sum(perDigitTable, &key);
		if (Key_compare(&sum, &in) == 0) {
			print_key_char(key);
		}

		if (Key_isMax(&key))
			break;
	}

	return 0;
}
