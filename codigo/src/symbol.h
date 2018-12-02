#if !defined(SYMBOL_H)
#define SYMBOL_H

#if !defined(ST_ITEM_TYPE)
#define ST_ITEM_TYPE void
#endif

// Um valor da tabela sempre é um ponteiro  
// O tipo do ponteiro pode ser ajustado nos arquivos que incluem os cabeçalhos
// da tabela setando previamente a macro ST_ITEM_TYPE para permitir a checagem
// de tipo, de outro modo o ponteiro é genérico

typedef ST_ITEM_TYPE* Item;

#define Item_NULL (NULL)

// Tipo de um callback que recebe um Item
typedef void (*cb_item_t)(Item);

#endif // SYMBOL_H
