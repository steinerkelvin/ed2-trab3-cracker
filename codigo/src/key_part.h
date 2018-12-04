#if !defined(KEY_PART_H)
#define KEY_PART_H

#include <stdbool.h>

/**
 * Tipo para armazenar um pedaço de chave de tamanho fixo na tabela
 * Expõe também uma implementação de lista para esse tipo
 */

#include "key.h"

typedef struct key_part {
    unsigned char digit[C_TABLE];
} KeyPart;


void KeyPart_inc(KeyPart *part);

bool KeyPart_isMax(KeyPart *part);


#endif // KEY_PART_H
