#include "include/matriz.h"

void destruirMatriz(matriz *M) {
    if (M != NULL) {
        free(M->datos);
        free(M);
    }
}
