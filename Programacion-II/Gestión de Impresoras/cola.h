#ifndef COLA_H
#define COLA_H




/** Definicion del tipo de elemento almacenado en la cola **/
typedef int TIPOELEMENTOCOLA;


/** Estructura para la cola **/
typedef void *TCOLA;

/**
 * Reserva memoria para una cola de datos con el tipo [TIPOELEMENTOCOLA].
 *
 * @param q puntero a la cola a crear.
 */
void crearCola(TCOLA *q);

/**
 * Destruye (libera la memoria reservada) la cola [q] y todos los elementos que almacena.
 *
 * @param q cola a destruir.
 */
void destruirCola(TCOLA *q);

/**
 * Comprueba si la cola [q] esta vacia.
 *
 * @param q cola a comprobar si esta vacia.
 * @return 1 si la cola esta vacia, 0 si no.
 */
int esColaVacia(TCOLA q);

/**
 * Consulta el primer elemento de la cola [q], de haberlo, y lo almacena en [e], sin eliminarlo de la cola.
 *
 * @param q cola de la cual extraer el primer elemento.
 * @param e variable donde almacenar el primer elemento de la cola.
 */
void consultarPrimerElementoCola(TCOLA q, TIPOELEMENTOCOLA *e);

/**
 * Destruye (libera la memoria reservada) del primer elemento de la cola.
 *
 * @param q cola de la cual destruir el primer elemento.
 */
void suprimirElementoCola(TCOLA *q);

/**
 * Anhade el elemento [e] a la cola [q].
 *
 * @param q cola a la cual anhadirle el elemento.
 * @param e elemento a anhadir.
 */
void anadirElementoCola(TCOLA *q, TIPOELEMENTOCOLA e);

/**
 * Consulta la longitud de la cola [q].
 * 
 * @param q cola de la cual consultar la longitud.
 * @return entero con el valor de la longitud de la lista.
*/
int longitud_Cola(TCOLA q);

#endif    // COLA_H

