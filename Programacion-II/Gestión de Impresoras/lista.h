#ifndef LISTA_H
#define LISTA_H
#include "cola.h"
#define MAX_L 20

/** Definicion del tipo de elemento almacenado en la lista **/
typedef struct{
    char nombre[MAX_L];
    char marca[MAX_L];
    char modelo[MAX_L];
    char ubicacion[MAX_L];
    TCOLA trabajos;
} IMPRESORA;

typedef IMPRESORA TIPOELEMENTOLISTA;

/** Estructura para una posicion de la lista **/
typedef void *TPOSICION;
/** Estructura para la lista **/
typedef void *TLISTA;

/**
 * Reserva memoria para una lista de datos con el tipo [TIPOELEMENTOLISTA].
 * 
 * @param q puntero a la lista a crear.
*/
void crearLista(TLISTA *l);

/**
 * Destruye (libera la memoria reservada) la lista [l] y todos los elementos que almacena.
 * 
 * @param l puntero a la lsita a destruir
*/
void destruirLista(TLISTA *l);

/**
 *  Comprueba si la lista [l] es vacia.
 * 
 * @param l lista a comprobar si esta vacia.
 * @retrun 1 si la lista esta vacia, 0 en otro caso.
*/
int esListaVacia(TLISTA l);

/**
 * Recupera la primera posicion de la lista.
 * 
 * @param l lista de la cual recuperar la primera posicion
 * @return la primera posicion tipo [TPOSCION] de la lista [l].
*/
TPOSICION primeroLista(TLISTA l);

/**
 * Recupera la posicion del fin de la lista.
 * 
 * @param l lista de la cual recuperar su final.
 * @return la posicion del fin tipo [TPSOCION] de la lista [l].
*/
TPOSICION finLista(TLISTA l);

/**
 * Devuelve la poscion siguiente a [p] en la lista [l].
 * 
 * @param l lista en la cual se va a buscar la siguiente posicion.
 * @param p posicion referencia para devolver la siguiente.
 * @return la posicion siguiente a [p]
*/
TPOSICION siguienteLista(TLISTA l, TPOSICION p);

/**
 * Recupera el elemento almacenado en la poscion [p] pasada por argumento.
 * 
 * @param l lista de la cual recuperar ele elemento.
 * @param p posicion de la cual recuperar el elemento.
 * @param e puntero a la variable en la cual alamanear el elemento recuperado.
*/
void recuperarElementoLista(TLISTA l, TPOSICION p, TIPOELEMENTOLISTA *e);

/**
 * Consulta la longitud de la lista [l].
 * 
 * @param l lista de la cual se consultar la longitud.
 * @return entero con el valor de la longitud de la lista.
*/
int longitudLista(TLISTA l);

/**
 * INserta el elemento [e] en la psocion siguiente a la psocion [p] de la lista [l].
 * 
 * @param l puntero a la lista en la cual se va a insertar el elemento.
 * @param p posicion despues de la cual se insertara el elemento.
 * @param e elemento a insertar
*/
void insertarElementoLista(TLISTA *l, TPOSICION p, TIPOELEMENTOLISTA e);

/**
 * Suprimer el elemento en posicion [p] de la lista [l].
 * 
 * @param l puntero a la lista de la que se suprimira el elemento.
 * @param p posicion del elemento a suprimir.
*/
void suprimirElementoLista(TLISTA *l, TPOSICION p);

/**
 * Modifica el valor del elemento almacenado en la posicion [p] guardando el nuevo elemento [e].
 * 
 * @param l puntero a la lista de la cual se va amodificar el elemento.
 * @param p posicion del valor que se va a modificar.
 * @param e nuevo valor a guardar en la poscion [p].
*/
void modificarElementoLista(TLISTA *l, TPOSICION p, TIPOELEMENTOLISTA e);

#endif    // LISTA_H
