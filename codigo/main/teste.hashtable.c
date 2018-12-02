#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ST_ITEM_TYPE int

#include "util.h"
#include "key.h"
#include "hash_table.h"

int main(){
    HashTable* hs = HT_create();

    Key a = init_key((uchar_t*)"baaaaaaaaaaa");
    Key b = init_key((uchar_t*)"caaaaaaaaaaa");
    Key c = init_key((uchar_t*)"daaaaaaaaaaa");
    Key d = init_key((uchar_t*)"eaaaaaaaaaaa");
    Key e = init_key((uchar_t*)"faaaaaaaaaaa");

    HT_insert(hs, &a, &(int){1});
    HT_insert(hs, &b, &(int){2});
    HT_insert(hs, &c, &(int){3});
    HT_insert(hs, &d, &(int){4});
    HT_insert(hs, &e, &(int){5});
	printf("ok\n");

    int df = -1;

    int *ra = &df; HT_get(hs, &a, &ra);
    int *rb = &df; HT_get(hs, &b, &rb);
    int *rc = &df; HT_get(hs, &c, &rc);
    int *rd = &df; HT_get(hs, &d, &rd);
    int *re = &df; HT_get(hs, &e, &re);

    printf("%d %d %d %d %d\n",
        *ra,
        *rb,
        *rc,
        *rd,
        *re
    );

    HT_destroy(hs, NULL);

    return 0;
}

