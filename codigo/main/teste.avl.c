#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define ST_ITEM_TYPE int
#include "util.h"
#include "avl.h"

void repeatPrint(int rp, char *str) {
    for (int i = 0; i < rp; i++)
        printf("%s", str);
}

int printRecur(AVL* node, int dp) {
    if (node == NULL)
        return 0;

    printf("\n");
    repeatPrint(dp, "    ");
    printf("<%2d", (node->item != Item_NULL) ? *(node->item) : -1);
    int ch = 0;
    ch = printRecur(node->left, dp+1) || ch;
    ch = printRecur(node->right, dp+1) || ch;
    if (ch) {
        printf("\n");
        repeatPrint(dp, "    ");
    }
    printf(">");

    return 1;
}

void printTree(AVL* node) {
    printRecur(node, 0);
    printf("\n");
}

void printOrderRecur(AVL* node) {\
    if (node == NULL) return;
    printOrderRecur(node->left);
    if (node->item == Item_NULL) {
        printf(". ");
    } else {
        printf("%d ", *(node->item));
    }
    
    printOrderRecur(node->right);
}

void printOrder(AVL* node) {
    printOrderRecur(node);
    printf("\n");
}

int main() {
    AVL* avl = NULL;

    {
        Key key = {{0}};
        for (int i = 0; i < 25; i++) {
            int *p = malloc(sizeof(int));
            *p = i;

            int **it;
            // print_key(key);
            // printf("inserindo: %d\n", i);
            int ins = avl_get_or_add(&avl, &key, &it);
            assert(ins);
            *it = p;

            Key_inc(&key);
        }
    }

    {
        Key key = {{0}};    
        for (int i = 0; i < 35; i++) {
            int **it;
            int ins = avl_get_or_add(&avl, &key, &it);
            if (ins) {
                printf("INSERIU %d\n", i);
            } else {
                printf("BUSCOU %d -> %d\n", i, **it);
            }

            Key_inc(&key);
        }
    }

    printTree(avl);
    printOrder(avl);

    avl_destroy(avl, (cb_item_t)free);

}
