// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#include <stdlib.h>
#include <stdio.h>


/** Definicion del tipo de elemento almacenado en la cola **/
typedef  int TIPOELEMENTOCOLA;


/** Estructura  para cada nodo de la cola **/
typedef struct nodoCola {
    TIPOELEMENTOCOLA dato;
    struct nodoCola *sig;
} STNODOCOLA;

/** Estructura para la cola **/
typedef struct {
    STNODOCOLA *principio;
    STNODOCOLA *final;
} STCOLA;
typedef STCOLA *TCOLA;


/**
 * Reserva memoria para una cola de datos con el tipo [TIPOELEMENTOCOLA].
 *
 * @param q puntero a la cola a crear.
 */
void crearCola(TCOLA *q) {
    *q = (TCOLA) malloc(sizeof(STCOLA));
    (*q)->final = NULL;
    (*q)->principio = NULL;
}

/**
 * Comprueba si la cola [q] esta vacia.
 *
 * @param q cola a comprobar si esta vacia.
 * @return 1 si la cola esta vacia, 0 si no.
 */
int esColaVacia(TCOLA q) {
    return (q->final == NULL) && (q->principio == NULL);
}

/**
 * Consulta el primer elemento de la cola [q], de haberlo, y lo almacena en [e], sin eliminarlo de la cola.
 *
 * @param q cola de la cual extraer el primer elemento.
 * @param e variable donde almacenar el primer elemento de la cola.
 */
void consultarPrimerElementoCola(TCOLA q, TIPOELEMENTOCOLA *e) {
    if (esColaVacia(q)) {
        printf("\nERROR, la cola no tiene elementos\n");
    } else {
        *e = (q->principio)->dato;
    }
}

/**
 * Destruye (libera la memoria reservada) del primer elemento de la cola.
 *
 * @param q cola de la cual destruir el primer elemento.
 */
void suprimirElementoCola(TCOLA *q) {
    STNODOCOLA *aux;

    if (esColaVacia(*q)) {
        printf("\nERROR, la cola no tiene elementos\n");
    } else {
        aux = (*q)->principio;
        (*q)->principio = aux->sig;
        if ((*q)->principio == NULL) {
            (*q)->final = NULL;
        }
        free(aux);
    }
}

/**
 * Anhade el elemento [e] a la cola [q].
 *
 * @param q cola a la cual anhadirle el elemento.
 * @param e elemento a anhadir.
 */
void anadirElementoCola(TCOLA *q, TIPOELEMENTOCOLA e) {
    STNODOCOLA *aux;

    aux = (STNODOCOLA *) malloc(sizeof(STNODOCOLA));
    aux->dato = e;
    aux->sig = NULL;

    if (esColaVacia(*q)) {
        (*q)->principio = aux;
    } else {
        (*q)->final->sig = aux;
    }
    (*q)->final = aux;
}

/**
 * Destruye (libera la memoria reservada) la cola [q] y todos los elementos que almacena.
 *
 * @param q cola a destruir.
 */
void destruirCola(TCOLA *q) {
    while (!esColaVacia(*q)) { //mientras que no esta vacia
        suprimirElementoCola(q); //elimino el primer elemento de la cola
    }
    free(*q); //libero la variable TCOLA
}


/**
 * Modifica el valor del elemento almacenado en la posicion [p] guardando el nuevo elemento [e].
 *
 * @param l puntero a la lista de la cual se va a modificar el elemento.
 * @param p posicion del valor que se va a modificar.
 * @param e nuevo valor a guardar en la posicion [p].
 */
int longitud_Cola(TCOLA q) {//se trata de una opracion de lectura
    int longitud = 0;
    STNODOCOLA *actual = q->principio;//voy al elemento inical de la lista

    while (actual != NULL) {
        longitud++;//recorro la cola hasta llegar al final
        actual = actual->sig;
    }

    return longitud;//devuelve la longitud
}
