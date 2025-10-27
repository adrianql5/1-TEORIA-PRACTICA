// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#define MAX_L 20

/** Definicion del tipo de elemento almacenado en la lista **/

typedef struct {//creo la estructua de mi impresora
    char nombre [MAX_L];
    char marca [MAX_L];
    char modelo [MAX_L];
    char ubicacion[MAX_L];
    TCOLA trabajos; //meto la cola en cada impresora
}IMPRESORA;

typedef IMPRESORA TIPOELEMENTOLISTA;//hago el typedef correspondiente
///////////////////////////////////////////////////

/** Estructura para un nodo de la lista **/
typedef struct nodoLista {
    TIPOELEMENTOLISTA elemento;
    struct nodoLista *sig;
} STNODOLISTA;
typedef STNODOLISTA *TPOSICION;

/** Estructura para la lista **/
typedef struct {
    TPOSICION inicio;
    int longitud;
    TPOSICION fin;
} STLISTA;
typedef STLISTA *TLISTA;

/**
 * Reserva memoria para una lista de datos con el tipo [TIPOELEMENTOLISTA].
 *
 * @param q puntero a la lista a crear.
 */
void crearLista(TLISTA *l) {
    *l = (TLISTA) malloc(sizeof(STLISTA));
    (*l)->inicio = (TPOSICION) malloc(sizeof(STNODOLISTA));
    (*l)->inicio->sig = NULL;
    (*l)->fin = (*l)->inicio;
    (*l)->longitud = 0;
}

/**
 * Destruye (libera la memoria reservada) la lista [l] y todos los elementos que almacena.
 *
 * @param l puntero a la lista a destruir.
 */
void destruirLista(TLISTA *l) {
    (*l)->fin = (*l)->inicio;
    while ((*l)->fin != NULL) {
        (*l)->fin = (*l)->fin->sig;

        free((*l)->inicio);
        (*l)->inicio = (*l)->fin;
    }
    free(*l);
}

/**
 * Comprueba si la lista [l] esta vacia.
 *
 * @param l lista a comprobar si esta vacia.
 * @return 1 si la lista esta vacia, 0 en otro caso.
 */
int esListaVacia(TLISTA l) {
    return (l->longitud == 0);
}

/**
 * Recupera la primera posicion de la lista.
 *
 * @param l lista de la cual recuperar la primera posicion.
 * @return la primera posicion tipo [TPOSICION] de la lista [l].
 */
TPOSICION primeroLista(TLISTA l) {
    return l->inicio;
}

/**
 * Recupera la posicion del fin de la lista.
 *
 * @param l lista de la cual recuperar su final.
 * @return la posicion del fin tipo [TPOSICION] de la lista [l].
 */
TPOSICION finLista(TLISTA l) {
    return l->fin;
}

/**
 * Devuelve la posicion siguiente a [p] en la lista [l].
 *
 * @param l lista en la cual se va a buscar la siguiente posicion.
 * @param p posicion referencia para devolver la siguiente.
 * @return la posicion siguiente a [p].
 */
TPOSICION siguienteLista(TLISTA l, TPOSICION p) {
    return p->sig;
}

/**
 * Recupera el elemento almacenado en la posicion [p] pasada por argumento.
 *
 * @param l lista de la cual recuperar el elemento.
 * @param p posicion de la cual recuperar el elemento.
 * @param e puntero a la variable en la cual almacenar el elemento recuperado.
 */
void recuperarElementoLista(TLISTA l, TPOSICION p, TIPOELEMENTOLISTA *e){
    *e = p->sig->elemento;
}

/**
 * Consulta la longitud de la lista [l].
 *
 * @param l lista de la cual consultar la longitud.
 * @return entero con el valor de la longitud de la lista.
 */
int longitudLista(TLISTA l) {
    return l->longitud;
}

/**
 * Inserta el elemento [e] en la posicion siguiente a la posicion [p] de la lista [l].
 *
 * @param l puntero a la lista en la cual se va a insertar el elemento.
 * @param p posicion despues de la cual se insertara el elemento.
 * @param e elemento a insertar.
 */
void insertarElementoLista(TLISTA *l, TPOSICION p, TIPOELEMENTOLISTA e){
    TPOSICION q = p->sig;
    p->sig = (STNODOLISTA *) malloc(sizeof(STNODOLISTA));
    p->sig->elemento = e;
    p->sig->sig = q;
    if (q == NULL) {
        (*l)->fin = p->sig;
    }
    (*l)->longitud++;
}

/**
 * Suprime el elemento en posicion [p] de la lista [l].
 *
 * @param l puntero a la lista de la que se suprimira el elemento.
 * @param p posicion del elemento a suprimir.
 */
void suprimirElementoLista(TLISTA *l, TPOSICION p){
    TPOSICION q;

    q = p->sig;
    p->sig = q->sig;
    if (p->sig == NULL) {
        (*l)->fin = p;
    }
    free(q);
    (*l)->longitud--;
}

/**
 * Modifica el valor del elemento almacenado en la posicion [p] guardando el nuevo elemento [e].
 *
 * @param l puntero a la lista de la cual se va a modificar el elemento.
 * @param p posicion del valor que se va a modificar.
 * @param e nuevo valor a guardar en la posicion [p].
 */
void modificarElementoLista(TLISTA *l, TPOSICION p, TIPOELEMENTOLISTA e){
    p->sig->elemento = e;
}
