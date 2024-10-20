
#include "include/matriz.h"

matriz* suma(matriz *M1, matriz *M2) {
    matriz *aux = 0;
    int i, k;

    if (M1 != NULL && M2 != NULL) {
        if (M1->filas != M2->filas || M1->columnas != M2->columnas) {
            printf("El numero de filas y columnas deben ser iguales\n");
            return aux;
        }
        aux = crearMatriz(M1->filas, M1->columnas);
        for (i = 0; i < aux->filas; i++){
            //for (k = 0; k < aux->filas; k++)
            for (k = 0; k < aux->columnas; k++){
               // *(aux->datos + i * aux->columnas + (k - 1)) = *(M2->datos + i * M1->columnas + (k - 1)) + *(M2->datos + i * M2->columnas + (k - 1));  
                *(aux->datos + i * aux->columnas + k) = *(M1->datos + i * M1->columnas + k) + *(M2->datos + i * M2->columnas + k);       
      
            }       
        } return aux; 
            
    } else
        //printf("Alguna de las matrices no existe\n"); Esto lo comento, porque si no después me imprime este mensaje mas el mensaje de error de la función imprimir matriz y no tiene mucho sentido que escriba el mismo error 2 veces.
        return aux;
}

