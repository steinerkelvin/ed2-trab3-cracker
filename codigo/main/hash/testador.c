#include <stdio.h>
#include <stdlib.h>
#include "key.h"
#include "hash.h"

void main(){
    HashTable* hs = newHash();
    Key a = init_key("aaaaaaaaaaaa");
    Key b = init_key("aaaaaaaaaaab");
    Key c = init_key("aaaaaaaaaaac");
	printf("ok\n");
    insert_hash(hs, a, 1);
    insert_hash(hs, b, 2);
    insert_hash(hs, c, 3);
	printf("ok\n");
    printf("%d %d %d\n",hashAt(hs,a),hashAt(hs,b),hashAt(hs,c));
}
	
