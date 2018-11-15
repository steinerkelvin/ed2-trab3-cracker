#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "key.h"

int compare_key(Key k1, Key k2) {
	for (int i = 0; i < C; i++) {
		if ( k1.digit[i] > k2.digit[i] ) return 1;
		if ( k1.digit[i] < k2.digit[i] ) return -1;
	}
	return 0;
}

void dec_to_bin(int num, unsigned short int* bin, int size){
	for (int aux = size-1; aux >= 0; aux--) {
		if (num % 2 == 0) bin[aux] = 0;
		else bin[aux] = 1;
		num = num / 2;
	}
}

int bin_to_dec(unsigned short int* bin, int size) {
	int s = size;
	int dec = 0;
	int i = 0;
	while(s--) dec = dec + pow(2, i++) * bin[s];
	return dec;
}

void bin_to_string(unsigned short int* bin, char* word) {
	int k = 0;
	unsigned short int characterb[B];
	for (int i = 0; i < N; i = i+B){
		int aux = i;
		for (int j = 0; j < B; j++) characterb[j] = bin[aux++];
		word[k] = ALPHABET[bin_to_dec(characterb,B)];
		k++;
	}
}

void main(int argc, char** argv) {

	Key table[N];
	for (int i = 0; i < N; i++) {
		char aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

	Key in = init_key(argv[1]);
	int size = pow(32,B);

	unsigned short int comb[N];
	char word[C];

	for (int i = 0; i < size; i++) {
		dec_to_bin(i,comb,N);
		bin_to_string(comb,word);
		Key kword = init_key(word);
		Key sum = subset_sum(kword,table);
		if (compare_key(sum,in) == 0) print_key_char(kword);
	}

}
