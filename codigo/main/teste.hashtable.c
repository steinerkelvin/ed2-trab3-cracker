#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "key.h"
#include "hash_table.h"

int main(){
    HashTable* hs = HT_create();

    Key a = init_key((uchar_t*)"kaaaaaaaaaaa");
    Key b = init_key((uchar_t*)"aaaaaaaaaaab");
    Key c = init_key((uchar_t*)"jaaaaaaaaaac");
    Key d = init_key((uchar_t*)"aaaaaaaaaaak");
    Key e = init_key((uchar_t*)"aaaaaaaaaaal");
	printf("ok\n");

    HT_insert(hs, &a, 1);
    HT_insert(hs, &b, 2);
    HT_insert(hs, &c, 3);
    HT_insert(hs, &d, 4);
    HT_insert(hs, &e, 5);
	printf("ok\n");

    printf("%d %d %d %d %d\n",
        HT_get(hs, &a),
        HT_get(hs, &b),
        HT_get(hs, &c),
        HT_get(hs, &d),
        HT_get(hs, &e)
    );

    HT_destroy(hs);

    return 0;
}

