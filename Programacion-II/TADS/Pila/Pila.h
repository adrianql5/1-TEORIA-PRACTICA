#ifndef PILA_H
#define PILA_H

typedef int TELEMENTO;

typedef void* TPILA;

void crear(TPILA *p);

void destruir(TPILA* p);

void cima(TPILA p, TELEMENTO* e);

void push(TPILA* p, TELEMENTO e);

void pop(TPILA* p);

#endif //PILA_H//