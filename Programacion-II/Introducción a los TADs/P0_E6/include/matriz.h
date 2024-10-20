#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *datos;
    int filas, columnas;
} matriz;

void asignarElemento(int fila, int columna, float valor, matriz *M);
matriz* crearMatriz(int filas, int columnas);
void destruirMatriz(matriz *M);
void imprimirMatriz(matriz *M);
float obtenerElemento(int fila, int columna, matriz *M);
matriz* producto(matriz *M1, matriz *M2);
matriz* suma(matriz *M1, matriz *M2);


#endif	// MATRIZ_H

