#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ST_ITEM_TYPE int
#include "symbol.h"
#include "util.h"
#include "key.h"
#include "hash_table.h"

int* alloc_int(int x) {
    int *p = malloc(sizeof(int));
    *p = x;
    return p;
}

int main(){
    HashTable* hs = HT_create();

    Key a = init_key((uchar_t*)"baaaaaaaaaaa");
    Key b = init_key((uchar_t*)"caaaaaaaaaaa");
    Key c = init_key((uchar_t*)"daaaaaaaaaaa");
    Key d = init_key((uchar_t*)"eaaaaaaaaaaa");
    Key e = init_key((uchar_t*)"faaaaaaaaaaa");
    Key n = init_key((uchar_t*)"notaaaaaaaaa");

    int **val;
    assert( HT_getOrAdd(hs, &a, &val) ); *val = alloc_int(1);
    assert( HT_getOrAdd(hs, &b, &val) ); *val = alloc_int(2);
    assert( HT_getOrAdd(hs, &c, &val) ); *val = alloc_int(3);
    assert( HT_getOrAdd(hs, &d, &val) ); *val = alloc_int(4);
    assert( HT_getOrAdd(hs, &e, &val) ); *val = alloc_int(5);

    assert(!HT_getOrAdd(hs, &c, &val) ); assert( **val == 3 );

    int df = -1;
    int *ra = &df; assert( HT_search(hs, &a, &ra) );
    int *rb = &df; assert( HT_search(hs, &b, &rb) );
    int *rc = &df; assert( HT_search(hs, &c, &rc) );
    int *rd = &df; assert( HT_search(hs, &d, &rd) );
    int *re = &df; assert( HT_search(hs, &e, &re) );
    int *rn = &df; assert( !HT_search(hs, &n, &re) );

    printf("%d %d %d %d %d %d\n",
        *ra,
        *rb,
        *rc,
        *rd,
        *re,
        *rn
    );

    HT_destroy(hs, (cb_item_t)free);

    return 0;
}
