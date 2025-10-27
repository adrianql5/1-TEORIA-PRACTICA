#include <stdio.h>
#include <stdlib.h>

typedef int TELEMENTO;

typedef struct nodopila{
    TELEMENTO dato;
    struct nodopila* sig;    
}STPILA;

typedef STPILA* TPILA;

void crear(TPILA *p){
    *p=NULL;
}

void destruir(TPILA *p){
    free(p);
}

void push(TPILA *p, TELEMENTO e){
    TPILA aux;
    aux=(TPILA)malloc(sizeof(STPILA));
    aux->dato=e;
    aux->sig=*p;
    *p=aux;
}

void pop(TPILA *p){
    TPILA aux;
    aux=*p;
    (*p)=(*p)->sig;
    free(aux);
}

void cima(TPILA p, TELEMENTO * e){
    *e=p->dato;
}
