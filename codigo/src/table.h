#if !defined(TABLE_H)
#define TABLE_H

// Um valor em uma tabela sempre é um ponteiro  
// O tipo do ponteiro pode ser ajustado nos arquivos que incluem os cabeçalhos
// da tabela setando previamente a macro VALUE_PTR_TYPE para permitir a checagem
// de tipo, de outro modo o ponteiro é genérico (void*)

#if !defined(VALUE_PTR_TYPE)
    #define VALUE_PTR_TYPE void
#endif
#if !defined(VALUE_NULL)
    #define VALUE_NULL NULL
#endif

typedef VALUE_PTR_TYPE* Value;

// Tipo de um callback que recebe um Value
typedef void (*cb_value_t)(Value);


#endif // TABLE_H
