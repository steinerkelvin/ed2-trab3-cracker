#include "part_list.h"
#include <assert.h>
#include "space.h"

Space partlist_space;

void parts_reserveSpace(int c, int n) {
	partlist_space = space_alloc(n, sizeof(PartList) + sizeof(Digit[c]));
}

void parts_freeSpace() {
	space_free(&partlist_space);
}


void copy_digits_to(int c, int pos, Digit *part, Key *key) {
	int k = pos;
	for (int i = 0; i < c; i++) {
		key->digit[k++] = part[i];
	}
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
		PartList *node = space_getNext(&partlist_space);
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

