#ifndef KEY_H
#define KEY_H

#include <stdbool.h>

// ==== PARÂMETROS DA CHAVE ==== //

#define C 5          // Número de caracteres na senha.
#define B 5          // Número de bits por caractere.
#define R (1 << B)   // Tamanho do alfabeto (sempre = 32).
#define N (B * C)    // Número de bits por senha.

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"

// ==== PARÂMETROS DE EXECUÇÃO ==== //

// #define HT_SIZE 2097143 
// #define C_TABLE 4

// Valores alternativos (usa ~32 vezes mais memória na tabela)
#define HT_SIZE 33554393
#define C_TABLE 5

// Usa `space.h` para alocar todo espaço para a tabela de uma vez
#define FIXED_SPACE 1

// ======== //

typedef unsigned char Digit;

// Um inteiro módulo R formado por C dígitos. O array está contido
// dentro de uma estrutura para facilitar a gerência de memória e
// a passagem de parâmetros nas funções.
typedef struct key {
    Digit digit[C];
} Key;

// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(Digit s[]);

// Exibe a chave 'k' em stdout em três formatos: chars, ints (base R) e binário.
void print_key(Key k);

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(Key k);

// Retorna o i-ésimo bit de k.
int bit(Key k, int i);

// Retorna a + b (mod 2^N) .
Key add(Key a, Key b);

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N]);

// ======== //

void Key_readTable(Key table[N]);

void Key_inc(Key *key);

bool Key_isMax(const Key *k);

// Compara duas Keys
int Key_compare(const Key* a, const Key* b);

bool Key_isEqual(const Key *k1, const Key *k2);

void Key_add(Key *res, const Key *a, const Key *b);

void Key_sub(Key *res, const Key *a, const Key *b);


#endif
