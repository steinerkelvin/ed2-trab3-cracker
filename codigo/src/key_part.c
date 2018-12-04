#include "key_part.h"

void KeyPart_inc(KeyPart *part) {
    for (int i = C_TABLE-1; i >= 0; i--) {
        part->digit[i] += 1;
        if (part->digit[i] < R)
            break;
        part->digit[i] %= R;
    }
}

bool KeyPart_isMax(KeyPart *part) {
	for (int i = C_TABLE-1; i >= 0; i--) {
		if (part->digit[i] != (R-1))
			return 0;
	}
	return 1;
}
