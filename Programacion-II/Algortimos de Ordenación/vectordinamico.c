#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

typedef int TELEMENTO; //telemento es ahora un float

typedef struct {
    TELEMENTO *datos;//puntero que apunta a datos del tipo telemento(floats)
    unsigned long tam;
} STVECTOR;

typedef STVECTOR *vectorD;//vectorD que antes apuntaba a un tipo desconcido ahora apunta a la estructura STVECTOR

/*Función CreaVector: asigna memoria y devuelve la asignación al vector*/
void CreaVector(vectorD *v1, unsigned long tam1) {
    //LiberaVector(v1);
    *v1 = (vectorD) malloc(sizeof (STVECTOR));//cast vectorD y reservo el tamaño de la estructura
    (*v1)->datos = (TELEMENTO*) malloc(tam1 * sizeof (TELEMENTO)); //como tengo un puntero en la estructura necesito reservar la memoria, por lo que multiplico el tamaño que introduce el ususario por lo que ocupa TELEMENTO(float)
    (**v1).tam = tam1;
    
}

/*Función AsignaVector: Llena una posición del vector con un valor*/
void AsignaVector(vectorD *v1, unsigned long posicion, TELEMENTO valor) {
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

TELEMENTO Componentei(vectorD v1,unsigned long posicion){//devuelvo el valor de la posicion
    if (!EsNulo(v1))
        if (posicion < v1->tam && posicion>=0)
            return*(v1->datos+posicion);
        

    return 0;
    
}

unsigned long tamano(vectorD v1){ //devuelve el tamaño del vector
    if(!EsNulo(v1)){
        return v1->tam;
    }   
    return 0;    
}

void swap(vectorD *v, unsigned long indice1, unsigned long indice2) {//fiucnion que intercambia los valores de la posicon del indicie 1 e indice 2 del vector
    TELEMENTO temp = (*v)->datos[indice1];//creo un elemento auxiliar para hacer el swap que guarda el dato del primer indice
    (*v)->datos[indice1] = (*v)->datos[indice2];//igualo el dato del primer indice al del segundo
    (*v)->datos[indice2] = temp;//igualo el dato del segundo al auxiliar que contenía al primero
}


void inicializaVectorRand(vectorD *v1) {//funcion que asigna valores ramdom al vector
    if (EsNulo(*v1)) return;

    srand(time(NULL)); 

    for (unsigned long i = 0; i < (*v1)->tam; i++) {//creo el bucle para recorrer el vector
        (*v1)->datos[i] = (TELEMENTO)rand(); 
    }
}