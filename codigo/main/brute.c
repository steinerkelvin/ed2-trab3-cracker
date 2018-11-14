#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned short int bit;

#define C 5

void dec_to_bin(int num, unsigned short int* bin, int size){
   for (int aux = size-1; aux >= 0; aux--) {
      if (num % 2 == 0) bin[aux] = 0;
      else bin[aux] = 1;
      num = num / 2;
   }
}

unsigned char assoc_int_char(int a) {
	if (a < 27 && a > 0) {
		a = a + 97;
		return a;
	}
	if (a > 26 && a  < 32) {
		a = a + 48;
		return a;
	}
	return 0;
}

int assoc_char_int(unsigned char a) {
	if (a < 123 && a > 96) {
		a = a - 97;
		return a;
	}
	if (a > 47 && a  < 54) {
		a = a - 48;
		return a+26;
	}
	return 0;
}

int bin_to_int(bit* bin, int size) {
	int s = size;
	int dec = 0;
	int i = 0;
	while(s--) dec = dec + pow(2, i++) * bin[s];
	return dec;
}

void bin_to_char(bit* result, char* word, int size) {
	int j = 0;
	for (int i = 0; i < size*C; i = i+C){
		bit characterb[5] = {result[i],result[i+1],result[i+2],result[i+3],result[i+4]}; //ao inves de fazer 5x, fazer size vezes...
		word[j] = assoc_int_char(bin_to_int(characterb,size));
		j++;
	}
}

void soma(bit* index, bit* total, int size, char** table) {
	bit temp[size*C];
	bit piece[size];
	dec_to_bin(0,total,size*C);
	int k = 0;
	for (int i = 0; i < size*C; i++){
		if (index[i] == 1) {
			for (int j = 0; j < size; j++) {
				dec_to_bin(assoc_char_int(table[i][j]),piece,size);
				temp[k] = piece[0];
				temp[k+1] = piece[1];
				temp[k+2] = piece[2];
				temp[k+3] = piece[3];
				temp[k+4] = piece[4]; //ao inves de fazer 5x, deve-se fazer size vezes...
				k = k+5;
			}
			dec_to_bin((bin_to_int(total,size*C) + bin_to_int(temp,size*C)),total,size*C);
			k = 0;
		}
	}
}

int main(int argc, char** argv){

	int size = strlen(argv[1]);

	char** table = malloc(size*C*sizeof(char*));
	for (int i = 0; i < size*C; i++) {
		table[i] = malloc(size*sizeof(char));
		scanf("%s",table[i]);
	}

	bit bin[C*size];
	bit result[C*size];
	dec_to_bin(0,result,size*C);
	char word[size];

	long long int comb = pow(32,size);

	for (int i = 0; i < comb; i++) {
		dec_to_bin(i,bin,size*C);
		soma(bin,result,size,table);
		bin_to_char(result,word,size);
		if (strcmp(word,argv[1])==0) {
			printf("ACHOU\n");
			char passwd[size];
			bin_to_char(bin,passwd,size);
			printf("%s\n",passwd);
		}
	}

	// dar free na table alocada dinamicamente;

	return 0;
}
