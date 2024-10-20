#ifndef MONEDAS_H
#define MONEDAS_H
#include "vectordinamico.h"
#include<stdio.h>


int cambio(int x, vectorD *valor, vectorD *solucion, vectorD *stock);

void añadirstock(vectorD v2, char* cadena);

void leerstock(vectorD *v1, char* cadena );

void imprimir(vectorD v1, vectorD v2);



#endif /*MONEDAS_H*/