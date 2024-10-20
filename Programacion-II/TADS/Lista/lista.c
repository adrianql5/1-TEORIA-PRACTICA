#include <stdio.h>
#include <stdlib.h>

typedef int Telemento;

typedef struct nodo{
    Telemento elemento;
    struct nodo* siguiente;
}STnodo;

typedef STnodo* Tposicion;

typedef struct{
    Tposicion inicio;
    int longitud;
    Tposicion final;
}STlista;

typedef STlista * Tlista;

void crearlisa(Tlista* l){
    *l=(Tlista)malloc(sizeof(STlista));
    (*l)->inicio=(Tposicion)malloc(sizeof(STnodo));
    (*l)->inicio->siguiente=NULL;
    (*l)->final=(*l)->inicio;
    (*l)->longitud=0;
}

void insertar(Tlista *l, Tposicion p, Telemento e){
    Tposicion aux;
    aux=(Tposicion)malloc(sizeof(STnodo));
    aux->elemento=e;
    aux->siguiente=p->siguiente;
    p->siguiente=aux;
    if(aux->siguiente==NULL){
        (*l)->final=aux;
    }
    (*l)->longitud++;

}

void suprimir(Tlista *l, Tposicion p){
    Tposicion aux;
    p->siguiente=aux->siguiente;
    p->siguiente=p->siguiente->siguiente;
    if(p->siguiente==NULL){
        (*l)->final=p;
    }
    free(aux);
    (*l)->longitud--;
}

void recuperar(Tlista l, Tposicion p, Telemento* e){
    *e=p->elemento;
}

Tposicion primero(Tlista l){
    return l->inicio;
}
Tposicion final(Tlista l){
    return l->final;
}
Tposicion siguiente(Tlista l, Tposicion p){
    return p->siguiente;
}

int Esvacia(Tlista l){
    if(l->inicio==NULL && l->final==NULL) return 1;
    else return 0;
}


