#include "include/matriz.h"

void asignarElemento(int fila, int columna, float valor, matriz *M) {

    if (M != NULL)
        *((M->datos) + fila * M->columnas + columna) = valor;
    else
        printf("Debe definir primero la matriz\n");
}
