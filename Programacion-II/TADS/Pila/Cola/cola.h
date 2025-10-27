// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#ifndef COLA_H
#define COLA_H

typedef int TELEMENTO;

typedef void* TCOLA;

void crear(TCOLA* c);

void destruir(TCOLA* c);

void encolar(TCOLA*c, TELEMENTO e);

void desencolar(TCOLA* c);

void primerocola(TCOLA c, TELEMENTO* e);

int EsVacia(TCOLA c);

#endif //COLA_H//
