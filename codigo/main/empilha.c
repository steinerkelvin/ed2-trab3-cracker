#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "key.h"
#include "util.h"
#include "per_digit.h"

Key perDigitTable[C][R];

void executa(const Key in) {
    Key stackPos = {{0}};
    Key stackSum[C+1] = { {{0}} };  

    int dp = 1;
    while (dp) {
        Key_add(
            &stackSum[dp],
            &stackSum[dp-1],
            &perDigitTable[dp-1][stackPos.digit[dp-1]]
        );
        if (dp == C) {
            if (Key_isEqual(&stackSum[dp], &in))
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

int main(int argc, char* argv[]) {
    check_decrypt_params(argc, argv);

	Key table[N];
	for (int i = 0; i < N; i++) {
		uchar_t aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

	Key in = init_key((uchar_t*) argv[1]);

    perDigitTable_build(perDigitTable, table);

    executa(in);

	return 0;
}
