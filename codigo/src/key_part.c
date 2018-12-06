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

Digit* KeyPart_from(int c, int pos, Key *key) {
	Digit* part = malloc((c-pos)*sizeof(Digit));
	int k = (c-pos)-1;
	for (int i = c-1; ((i>=pos)&&(k>=0)); i--) {
		part[k] = key->digit[i];
		k--;
	}
	return part;
}

void KeyPart_copyTo(int c, int pos, Digit *part, Key *key) {
	int k = (c-pos)-1;
	for (int i = c-1; ((i>=pos)&&(k>=0)); i--) {
		key->digit[i] = part[k];
		k--;
	}
}

