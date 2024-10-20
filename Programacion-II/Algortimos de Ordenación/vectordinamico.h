#ifndef VECTORDINAMICO_H
#define VECTORDINAMICO_H
#include <stdbool.h>

typedef int TELEMENTO;//tipo de los elementos que contiene el vector 
typedef void * vectorD; //el vectorD es un tipo opaco, por lo que no se sabe a que está apuntando


void CreaVector(vectorD *v1,unsigned long tam1);//función que modifica el vector, por ello recibe un puntero
void AsignaVector(vectorD *v1,unsigned long posicion,TELEMENTO valor);//funcion que modifica el vector, por lo que recibe un puntero
void LiberaVector(vectorD *v1);//función que destruirá lo que contiene el vector, por lo que le paso un puntero

TELEMENTO Componentei(vectorD v1,unsigned long posicion);//función que devuleve un elemento (tipo float) y como no modifica se le pasa el vector

bool EsNulo(vectorD v1);//funcion que nos devuelve si está vacío o no

unsigned long tamano(vectorD v1);//función que no devuelve el tamaño

void inicializaVectorRand(vectorD *v1);//funcion que inicializa el vecotrcon valores aleatorios

void swap(vectorD *pvector, unsigned long m, unsigned long n);//funcion que intercambia los elemetnos del vector de las posiciones m y n

#endif /*VECTORDINAMICO_H*/