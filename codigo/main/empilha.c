#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "key.h"
#include "util.h"

static inline bool is_equal(const Key *k1, const Key *k2) {
	for (int i = 0; i < C; i++) {
		if ( k1->digit[i] != k2->digit[i] )
            return 0;
	}
	return 1;
}

static inline void key_add(Key *res, const Key *a, const Key *b) {
    int carry = 0;
    for (int i = C-1; i >= 0; i--) {
        int sum       = a->digit[i] + b->digit[i] + carry;
        res->digit[i] = sum  % R;
        carry         = (sum >= R);
    }
}

Key tabelinha[C][R];

void executa(const Key in) {
    Key stackPos = {{0}};
    Key stackSum[C+1] = { {{0}} };  

    int dp = 1;
    while (dp) {
        key_add(
            &stackSum[dp],
            &stackSum[dp-1],
            &tabelinha[dp-1][stackPos.digit[dp-1]]
        );
        if (dp == C) {
            if (is_equal(&stackSum[dp], &in))
                print_key(stackPos);
            
            while ( dp && (++stackPos.digit[dp-1]) == R ) {
                stackPos.digit[dp-1] = 0;
                dp--;
            }
        } else {
            dp++;
        }
    }
}

int main(int argc, char** argv) {

	Key table[N];
	for (int i = 0; i < N; i++) {
		uchar_t aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

	Key in = init_key((uchar_t*) argv[1]);

    // Inicializa a tabelinha
    for (int i=0; i < C; i++) {
        for (int j = 0; j < R; j++) {
            Key key = {{0}};
            key.digit[i] = j;
            tabelinha[i][j] = subset_sum(key, table);
        }
    }

    executa(in);

	return 0;
}
