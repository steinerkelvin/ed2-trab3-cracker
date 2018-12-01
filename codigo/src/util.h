#if !defined(UTIL_H)
#define UTIL_H

#define MAX(A, B) ((A > B) ? (A) : (B))

typedef unsigned char uchar_t;
typedef unsigned int uint_t;
typedef unsigned long int ulong_t;

void check_decrypt_params(int argc, char* argv[]);


#endif // UTIL_H
