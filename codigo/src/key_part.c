#include "key_part.h"

void KeyPart_inc(int c, Digit *part) {
    for (int i = c-1; i >= 0; i--) {
        part[i] += 1;
        if (part[i] < R)
            break;
        part[i] %= R;
    }
}

bool KeyPart_isMax(int c, Digit *part) {
	for (int i = c-1; i >= 0; i--) {
		if (part[i] != (R-1))
			return 0;
	}
	return 1;
}
