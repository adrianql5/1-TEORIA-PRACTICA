// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#include "include/matriz.h"

void destruirMatriz(matriz *M) {
    if (M != NULL) {
        free(M->datos);
        free(M);
    }
}
