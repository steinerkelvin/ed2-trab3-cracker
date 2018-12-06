#if !defined(KEY_PART_H)
#define KEY_PART_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * Tipo para armazenar um pedaço de chave de tamanho fixo na tabela
 * Expõe também uma implementação de lista para esse tipo
 */

#include "key.h"


void KeyPart_inc(int c, Digit *part);

bool KeyPart_isMax(int c, Digit *part);

// Seja c o tamanho de key. Seja pos a posição da string a partir da qual será realizada a copia;
// EX: SE Key = "athus"; c = 5; pos = 2; ENTÃO return "hus"; 
Digit* KeyPart_from(int c, int pos, Key *key);

// Seja c o tamanho de key. Seja pos a posição da string a partir da qual será realizada a copia;
// EX: SE part = "hus"; c = 5; pos = 2; ENTÃO key = "_ _ hus"; 
void KeyPart_copyTo(int c, int pos, Digit *part, Key *key);


#endif // KEY_PART_H
