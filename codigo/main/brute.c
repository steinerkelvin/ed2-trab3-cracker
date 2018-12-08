#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "key.h"

int main(int argc, char* argv[]) {
	check_params(argc, argv);

	Key table[N];
	Key_readTable(table);

	Key in = init_key((uchar_t*) argv[1]);

	for (Key key = {{0}}; ; Key_inc(&key)) {

        Key sum = subset_sum(key, table);
		if (Key_isEqual(&sum, &in)) {
			print_key_char(key);
		}

		if (Key_isMax(&key))
			break;
	}

	return 0;
}
