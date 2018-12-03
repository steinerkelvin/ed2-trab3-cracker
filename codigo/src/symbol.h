#if !defined(SYMBOL_H)
#define SYMBOL_H

#if !defined(ST_ITEM_TYPE)
#define ST_ITEM_TYPE void
#endif

#include "key.h"

// ======== //

#define MAXC_ST 5


// ======== //

// Um valor da tabela sempre é um ponteiro  
// O tipo do ponteiro pode ser ajustado nos arquivos que incluem os cabeçalhos
// da tabela setando previamente a macro ST_ITEM_TYPE para permitir a checagem
// de tipo, de outro modo o ponteiro é genérico

typedef ST_ITEM_TYPE* Item;

#define Item_NULL (NULL)

// Tipo de um callback que recebe um Item
typedef void (*cb_item_t)(Item);


// ======== //

// //                              0   1   2       3       4        5
// static const int SIZES[6] = {   0,  31, 1021,   32749,  1048573, 33554393 };

#endif // SYMBOL_H
