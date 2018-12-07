#if !defined(SPACE_H)
#define SPACE_H

/**
 * Gerencia espaço alocado para um número pré-determinado de elementos  
 * O espaço necessário é alocado todo de uma vez e os slots devem ser usados
 * sequencialmente
 */

#include <stdlib.h>
#include <assert.h>

typedef struct space {
    size_t item_size;
    size_t max_num;
    size_t num;
    char *ptr;
} Space;

/**
 * Aloca um espaço para `num` elementos de tamanho `size`
 */
Space space_alloc(size_t num, size_t size);

/**
 * Retorna ponteiro para o próximo slot disponível
 * pre: ainda há slots disponíveis
 * pos: há menos um slot disponível
 */
void * space_getNext(Space *space);

/**
 * Libera todo o espaço
 */
void space_free(Space *space);


#endif // SPACE_H
