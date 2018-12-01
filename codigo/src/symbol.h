#if !defined(SYMBOL_H)
#define SYMBOL_H

#if !defined(ST_ITEM_TYPE)
#define ST_ITEM_TYPE void
#endif

typedef ST_ITEM_TYPE* Item;

// unary callback for Item type
typedef void (*cb_item_t)(Item);

#endif // SYMBOL_H
