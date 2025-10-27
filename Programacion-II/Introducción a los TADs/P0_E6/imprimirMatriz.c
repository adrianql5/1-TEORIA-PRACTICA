// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#include "include/matriz.h"

void imprimirMatriz(matriz *M) {
    int i, k;

    if (M != NULL) {
        for (i = 0; i < M->filas; i++) {
            for (k = 0; k < M->columnas; k++)
                //printf("%f ", *((M->datos) +i  *M->filas + k));
                printf("%f ", *((M->datos) +i  *M->columnas + k));
            printf("\n");
        }
        printf("\n");
    } else
        printf("La matriz no existe\n");
}
