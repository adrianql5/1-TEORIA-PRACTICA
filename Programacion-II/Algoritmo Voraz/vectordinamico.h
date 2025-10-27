#ifndef VECTORDINAMICO_H
#define VECTORDINAMICO_H
#include <stdbool.h>

typedef int TELEMENTO;//tipo de los elementos que contiene el vector 
typedef void * vectorD; //el vectorD es un tipo opaco, por lo que no se sabe a que está apuntando


void CreaVector(vectorD *v1,int tam1);//función que modifica el vector, por ello recibe un puntero
void AsignaVector(vectorD *v1,int posicion,TELEMENTO valor);//funcion que modifica el vector, por lo que recibe un puntero
void LiberaVector(vectorD *v1);//función que destruirá lo que contiene el vector, por lo que le paso un puntero

TELEMENTO Componentei(vectorD v1,int posicion);//función que devuleve un elemento (tipo float) y como no modifica se le pasa el vector

bool EsNulo(vectorD v1);//funcion que nos devuelve si está vacío o no

int tamano(vectorD v1);//función que no devuelve el tamaño

#endif /*VECTORDINAMICO_H*/
