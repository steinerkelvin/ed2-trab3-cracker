#if !defined(KEY_PART_H)
#define KEY_PART_H

/**
 * Tipo para listas de partes de chave de um certo tamanho
 */

#include <stdbool.h>
#include <stdlib.h>

#include "key.h"
#include "space.h"


typedef struct part_list PartList;

typedef struct part_list {
    PartList* next;
    Digit part[];
} PartList;


/**
 * Copia de um vetor de dígitos para uma certa posição em uma chave
 */
void copy_digits_to(int c, int pos, Digit *part, Key *key);


void PartList_insert(PartList** list, int c, int pos, Key *key);

void PartList_free(PartList* node);


void parts_reserveSpace(int c, int n);

void parts_freeSpace();


#endif // KEY_PART_H
