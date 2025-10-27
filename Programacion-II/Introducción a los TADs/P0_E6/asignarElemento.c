// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#include "include/matriz.h"

void asignarElemento(int fila, int columna, float valor, matriz *M) {

    if (M != NULL)
        *((M->datos) + fila * M->columnas + columna) = valor;
    else
        printf("Debe definir primero la matriz\n");
}
