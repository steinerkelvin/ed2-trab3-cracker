
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "key.h"

void check_decrypt_params(int argc, char* argv[]) {
    // Garante um parâmetro
    if (argc <= 1) {
        fprintf(stderr, "Falta parâmetro. Uso:\n");
        fprintf(stderr, "%s [hash]\n", argv[0]);
        exit(1);
    }
    char *param = argv[1];
    if (strlen(param) < C) {
        fprintf(stderr, "ERRO: hash de senha muito curto: '%s'\n", param);
        fprintf(stderr, "necessário mínimo de %d caracteres\n", C);
        exit(1);
    }
}
