#include <stdio.h>
#include "key.h"

#include <stdlib.h>
#include <stdio.h>

// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[]) {
    // Converte cada char em um int no intervalo 0-31.
    Key k;
    for (int i = 0; i < C; i++) {
        k.digit[i] = 0;
        for (int j = 0; j < R; j++) {
            if (s[i] == ALPHABET[j]) {
                k.digit[i] = j;
                break;
            }
        }
    }
    // Note que não há problema de retornar uma variável local aqui porque
    // a semântica do C para variáveis do tipo struct (não struct*) é fazer
    // uma cópia da struct inteira. Isso pode parecer ineficiente mas lembre
    // que o vetor da struct de chave é muito pequeno.
    return k;
}

// Exibe a chave 'k' em stdout em três formatos: chars, ints (base R) e binário.
void print_key(Key k) {
    for (int i = 0; i < C; i++) {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("  ");
    for (int i = 0; i < C; i++) {
        printf("%2d ", k.digit[i]);
    }
    printf("  ");
    for (int i = 0; i < N; i++) {
        printf("%d", bit(k, i));
    }
    printf("\n");
}

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(Key k) {
    for (int i = 0; i < C; i++) {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("\n");
}

// Retorna o i-ésimo bit de k.
int bit(Key k, int i) {
    return (k.digit[i/B] >> (B - 1 - i % B)) & 1;
}

// Retorna a + b (mod 2^N) .
Key add(Key a, Key b) {
    Key c = {{0}};
    int carry = 0;
    for (int i = C-1; i >= 0; i--) {
        int sum = a.digit[i] + b.digit[i] + carry;
        c.digit[i] = sum  % R;
        carry      = sum >= R;
    }
    return c;
}

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N]) {
    Key sum = {{0}};
    for (int i = 0; i < N; i++) {
        if (bit(k, i)) {
            sum = add(sum, T[i]);
           // printf("%2d ", i);           // Para teste.
           // print_key(T[i]);             // Para teste.
        }
    }
   return sum;
}

// ===== //

void Key_readTable(Key table[N]) {
    for (int i = 0; i < N; i++) {
        Digit aux[C];
        int rt = scanf("%s",aux);
        if (rt != 1) {
            fprintf(stderr, "Falha ao ler a tabela\n");
            exit(1);
        }
        table[i] = init_key(aux);
    }
}

int Key_compare(const Key* a, const Key* b){
    for (int i = 0; i < C; i++) {
        const int diff = a->digit[i] - b->digit[i];
	    if (diff)
            return diff;
    }
    return 0;
}

bool Key_isEqual(const Key *k1, const Key *k2) {
	for (int i = 0; i < C; i++) {
		if ( k1->digit[i] != k2->digit[i] )
            return 0;
	}
	return 1;
}

void Key_inc(Key *key) {
    for (int i = C-1; i >= 0; i--) {
		key->digit[i] += 1;
		if (key->digit[i] < R)
			break;
		key->digit[i] %= R;
    }
}

bool Key_isMax(const Key *k) {
	for (int i = C-1; i >= 0; i--) {
		if (k->digit[i] != (R-1))
			return 0;
	}
	return 1;
}

void Key_add(Key *res, const Key *a, const Key *b) {
    int carry = 0;
    for (int i = C-1; i >= 0; i--) {
        int sum       = a->digit[i] + b->digit[i] + carry;
        res->digit[i] = sum  % R;
        carry         = (sum >= R);
    }
}

// Operação de módulo (resto) de divisão por R com resultado positivo
static inline int modR(const int num) {
    return ((num % R + R) % R);
}

void Key_sub(Key *res, const Key *a, const Key *b) {
    int carry = 0;
    for (int i = C-1; i >= 0; i--) {
        int sum       = a->digit[i] - b->digit[i] - carry;
        res->digit[i] = modR(sum);
        carry         = (sum < 0);
    }
}
