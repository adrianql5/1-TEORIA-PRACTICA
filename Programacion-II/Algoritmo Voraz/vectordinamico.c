#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

typedef int TELEMENTO; //telemento es ahora un float

typedef struct {
    TELEMENTO *datos;//puntero que apunta a datos del tipo telemento(floats)
    int tam;
} STVECTOR;

typedef STVECTOR *vectorD;//vectorD que antes apuntaba a un tipo desconcido ahora apunta a la estructura STVECTOR

/*Función CreaVector: asigna memoria y devuelve la asignación al vector*/
void CreaVector(vectorD *v1, int tam1) {
    //LiberaVector(v1);
    *v1 = (vectorD) malloc(sizeof (STVECTOR));//cast vectorD y reservo el tamaño de la estructura
    (*v1)->datos = (TELEMENTO*) malloc(tam1 * sizeof (TELEMENTO)); //como tengo un puntero en la estructura necesito reservar la memoria, por lo que multiplico el tamaño que introduce el ususario por lo que ocupa TELEMENTO(float)
    (**v1).tam = tam1;
    
}

/*Función AsignaVector: Llena una posición del vector con un valor*/
void AsignaVector(vectorD *v1, int posicion, TELEMENTO valor) {
    *( (*v1) ->datos + posicion) = valor;
}


bool EsNulo(vectorD v1) {//funcion que nos dice si el vector es nulo
    if (v1 == NULL)
        return true;
    return false;
}

void LiberaVector(vectorD *v1) {//funcion que libera la memoria del vector
    if (!EsNulo(*v1)) {
        free((*v1)->datos);//libero el dato
        free(*v1);//libero el vector
        *v1=0;
    }
}

TELEMENTO Componentei(vectorD v1,int posicion){//devuelvo el valor de la posicion
    if (!EsNulo(v1))
        if (posicion < v1->tam && posicion>=0)
            return*(v1->datos+posicion);
        

    return 0;
    
}

int tamano(vectorD v1){ //devuelve el tamaño del vector
    if(!EsNulo(v1)){
        return v1->tam;
    }   
    return 0;    
}

