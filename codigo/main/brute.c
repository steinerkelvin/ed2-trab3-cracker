#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "key.h"

int main(int argc, char* argv[]) {
	check_decrypt_params(argc, argv);

	Key table[N];
	for (int i = 0; i < N; i++) {
		uchar_t aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

	Key in = init_key((uchar_t*) argv[1]);

	for (Key key = {{0}}; ; Key_inc(&key)) {

        Key sum = subset_sum(key, table);
		if (Key_compare(&sum, &in) == 0) {
			print_key_char(key);
		}

		if (Key_isMax(&key))
			break;
	}

	return 0;
}
