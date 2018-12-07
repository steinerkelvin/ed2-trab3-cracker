#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include "table.h"
#include "key.h"

typedef struct hash_table HashTable;

HashTable* HT_create(int num_max);

void HT_destroy(HashTable* hs, cb_value_t cb_destroy);

/**
 * Busca um entrada na tabela para uma dada chave
 * parametros:
 *   ret -> [retorna] o valor armazenado
 * retorna: se encontrou
 */
bool HT_search(const HashTable* hs, const Key* k, Value* ret);

/**
 * Busca ou cria um entrada na tabela para uma dada chave
 * parametros:  
 *   key -> chave a ser buscada
 *   ret -> [retorna] ponteiro para o valor armazenado
 * retorna: se houve inserção
 */
bool HT_getOrAdd(HashTable* hs, const Key* k, Value** ret);


#endif // HASH_TABLE_H
