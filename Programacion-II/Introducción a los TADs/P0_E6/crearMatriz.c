#include "include/matriz.h"

matriz* crearMatriz(int filas, int columnas) {
    int i;
    matriz *mat = 0;

    if (filas <= 0 || columnas <= 0)
        return 0;

    mat = (matriz*) malloc(sizeof (matriz));

    if (mat != 0) {
        mat->filas = filas;
        mat->columnas = columnas;
        //mat->datos = (float*) malloc(filas * filas * sizeof (float));
        mat->datos = (float*) malloc(filas * columnas *sizeof(float));
        
        //for (i = 0; i < filas * filas; i++) {
        for (i = 0; i < filas * columnas; i++){
            *((mat->datos) + i) = 0;
        }
    } else
        printf("Error en la reserva de memoria para la matriz\n");

    return mat;
}
