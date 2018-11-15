#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "key.h"
#include "util.h"

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

void int_to_bin(int num, uchar_t* bin, int size){
	for (int aux = size-1; aux >= 0; aux--) {
		bin[aux] = num % 2;
		num = num / 2;
	}
}

int bin_to_int(uchar_t* bin, int size) {
	int s = size;
	int pos = 1;
	int num = 0;
	while (s--) {
		num += pos * bin[s];
		pos <<= 1;
	}
	return num;
}

void bin_to_string(uchar_t* bin, uchar_t* word) {
	int k = 0;
	uchar_t characterb[B];
	for (int i = 0; i < N; i = i+B){
		int aux = i;
		for (int j = 0; j < B; j++)
			characterb[j] = bin[aux++];
		word[k] = ALPHABET[bin_to_int(characterb, B)];
		k++;
	}
}


int main(int argc, char** argv) {

	Key table[N];
	for (int i = 0; i < N; i++) {
		uchar_t aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

	Key in = init_key((uchar_t*)argv[1]);

	// uchar_t comb[N];
	// uchar_t word[C];

	// Quantidade total de combinações de senhas
	const ulong_t quant = 1 << (B*C);

	for (int i = 0; i < quant; i++) {
		// int_to_bin(i, comb, N);
		// bin_to_string(comb, word);
		// Key kword = init_key(word);
		Key kword = int_to_key(i);
		Key sum = subset_sum(kword, table);
		if (compare_key(sum, in) == 0) {
			print_key_char(kword);
			return 0;
		}
	}

	return 1;
}
