#if !defined(KEY_PART_H)
#define KEY_PART_H

#include <stdbool.h>

/**
 * Tipo para armazenar um pedaço de chave de tamanho fixo na tabela
 * Expõe também uma implementação de lista para esse tipo
 */

#include "key.h"


void KeyPart_inc(int c, Digit *part);

bool KeyPart_isMax(int c, Digit *part);

Digit* KeyPart_from(int c, int pos, Key *key);

void KeyPart_copyTo(int c, int pos, Digit *part, Key *key);


#endif // KEY_PART_H
