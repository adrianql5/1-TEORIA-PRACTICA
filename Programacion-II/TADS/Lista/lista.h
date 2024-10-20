#ifndef LISTA_H
#define LISTA_H

typedef int Telemento;
typedef void* Tlista;
typedef void* Tposicion;

void crearlista(Tlista* l);
void destruirLista(Tlista *l);
void insertar(Tlista* l, Tposicion p, Telemento e);
void suprimir(Tlista* l, Tposicion p);
int esvacia(Tlista l);
Tposicion principio(Tlista l);
Tposicion siguiente(Tlista l);
Tposicion final(Tlista l);
void recuperar(Tlista l, Tposicion p, Telemento *e);

#endif