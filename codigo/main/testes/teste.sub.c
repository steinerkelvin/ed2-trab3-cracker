#include <stdio.h>
#include "key.h"
#include "util.h"

int main(int argc, char* argv[]) {
    // check_decrypt_params(argc, argv);

	Key table[N];
	for (int i = 0; i < N; i++) {
		uchar_t aux[C];
		scanf("%s",aux);
		table[i] = init_key(aux);
	}

    Key htgt = init_key((uchar_t*)"lxd55");
    print_key(htgt);
    printf("\n");

    Key pass = init_key((uchar_t*)"athus");
    Key hpass = subset_sum(pass, table);

    Key a = init_key((uchar_t*)"ataaa");
    Key b = init_key((uchar_t*)"aahus");
    Key ha = subset_sum(a, table);
    Key hb = subset_sum(b, table);

    printf("pass\n");
    print_key(pass);
    print_key(hpass);
    printf("\n");

    printf("a\n");
    print_key(a);
    print_key(ha);
    printf("\n");

    printf("b\n");
    print_key(b);
    print_key(hb);
    printf("\n");

    Key sub; Key_sub(&sub, &hpass, &hb);

    printf("hash(pass) - hash(a)\n");
    print_key(sub);
    printf("\n");

    return 0;
}
