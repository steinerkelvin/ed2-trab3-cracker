#if !defined(SUM_STACK_H)
#define SUM_STACK_H

#include <assert.h>
#include "util.h"
#include "key.h"

typedef struct sum_stack {
    // perDigitTable a partir do vetor para o primeiro caractere delegado
    Key *perDigitTable;
    int c;  // número de caracteres delegado à pilha
    int dp; // profundidade atual

    Key pos;
    Key sums[C+1];  

} SumStack;

/**
 * Inicializa a pilha mágica
 * entrada:
 *   c -> número de caracteres a ser empilhado
 *   perDigitTable ->
 *      ponteiro para a tabela de somas por dígito, apontando para  
 *      a coluna correspondente à primeira posição delegada à pilha
 */
SumStack SumStack_create(int c, Key *perDigitTable);

/**
 * Obtém ponteiro para a combinação de dígitos selecionada
 */
Key* SumStack_getKey(SumStack *stack);

/**
 * Obtém ponteiro para a soma computada
 */
Key* SumStack_getSum(SumStack *stack);


/**
 * Empilha até formar uma combinação, calculando todas as somas 
 */
void SumStack_calc(SumStack *st);

/**
 * Incrementa para a próxima combinação
 */
bool SumStack_next(SumStack *st);


#endif // SUM_STACK_H
