#include "key_part.h"
#include <assert.h>
#include "space.h"

Space keypart_space;

void parts_reserveSpace(int c, int n) {
	keypart_space = space_alloc(n, sizeof(PartList) + sizeof(Digit[c]));
}

void parts_freeSpace() {
	space_free(&keypart_space);
}


void PartList_free(PartList* node) {
	PartList *aux;
	while (node != NULL) {
		aux = node->next;
		free(node);
		node = aux;
	}
}

void PartList_insert(PartList** ref, int c, int pos, Key *key) {
	#if FIXED_SPACE
		PartList *node = space_getNext(&keypart_space);
	#else
		PartList *node = malloc(sizeof(PartList) + sizeof(Digit[c]));
	#endif

	int k = pos;
	for (int i = 0; i < c; i++) {
		node->part[i] = key->digit[k++];
	}

	node->next = *ref;
	*ref = node;
}


void copy_digits_to(int c, int pos, Digit *part, Key *key) {
	int k = pos;
	for (int i = 0; i < c; i++) {
		key->digit[k++] = part[i];
	}
}

// Digit* KeyPart_create(int c, int pos, Key *key) {
// 	#if FIXED_SPACE
// 		Digit* part = space_getNext(&keypart_space);
// 	#else
// 		Digit* part = malloc(sizeof(PartNode) + sizeof(Digit[c]));
// 	#endif

// 	int k = pos;
// 	for (int i = 0; i < c; i++) {
// 		part[i] = key->digit[k++];
// 	}
// 	return part;
// }


