#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "key.h"
#include "util.h"

void inc_key(Key *key) {
    for (int i = C-1; i >= 0; i--) {
		key->digit[i] += 1;
		if (key->digit[i] < R)
			break;
		key->digit[i] %= R;
    }
}

int compare_key(Key k1, Key k2) {
	for (int i = 0; i < C; i++) {
		if ( k1.digit[i] > k2.digit[i] ) return 1;
		if ( k1.digit[i] < k2.digit[i] ) return -1;
	}
	return 0;
}

Key int_to_key(ulong_t num) {
	Key key;
	for (int i = C-1; i >= 0; i--) {
		key.digit[i] = num % R;
		num = num >> B;
	}
	return key;
}

ulong_t key_to_int(Key key) {
	ulong_t num = 0;
	ulong_t pos = 1;
	for (int i = C-1; i >= 0; i--) {
		num += key.digit[i] * pos;
		pos = pos << B;
	}
	return num;
}

int main(int argc, char** argv) {

	Key table[N];
	for (int i = 0; i < N; i++) {
		uchar_t aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

	Key in = init_key((uchar_t*)argv[1]);

	// Quantidade total de combinações de senhas
	const ulong_t quant = 1UL << N;

    Key key;
	for (ulong_t i = 0; i < quant; i++) {
		// Key key = int_to_key(i);
		inc_key(&key);

		Key sum = subset_sum(key, table);
		if (compare_key(sum, in) == 0) {
			print_key_char(key);
		}
	}

	return 0;
}
