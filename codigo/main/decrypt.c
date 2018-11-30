#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "key.h"
#include "util.h"
#include "per_digit.h"

// TODO testar tabela de símbolos

Key perDigitTable[C][R];

int main(int argc, char** argv) {

	Key table[N];
	for (int i = 0; i < N; i++) {
		uchar_t aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

	Key in = init_key((uchar_t*) argv[1]);

    perDigitTable_build(perDigitTable, table);

	for (Key key = {{0}}; !Key_isMax(&key); Key_inc(&key)) {

        Key sum = perDigitTable_sum(perDigitTable, &key);
		if (Key_compare(&sum, &in) == 0) {
			print_key_char(key);
		}

	}

	return 0;
}
