#include <stdlib.h>
#include <stdio.h>

typedef int TELEMENTO;

typedef struct nodocola{
    TELEMENTO elemento;
    struct nodocola* siguiente;
}STNODO;



typedef struct{
    STNODO* inicio;
    STNODO* final;
}STCOLA;

typedef STCOLA* TCOLA;

void crear(TCOLA *c){
    *c=(TCOLA)malloc(sizeof(STCOLA));
    (*c)->final=NULL;
    (*c)->inicio=NULL;
}

void encolar(TCOLA* c, TELEMENTO e){
    STNODO* aux;
    aux=(STNODO*)malloc(sizeof(STNODO));

    aux->elemento=e;
    aux->siguiente=NULL;

    if((*c)->inicio==NULL &&(*c)->final==NULL){
        (*c)->inicio=aux;
    }
    else{
        (*c)->final->siguiente=aux;
        (*c)->final=aux;
    }
}

void desencolar(TCOLA* c){
    STNODO* aux;
    aux=(*c)->inicio;
    (*c)->inicio=(*c)->inicio->siguiente;

    if((*c)->inicio==NULL){
        (*c)->final=NULL;
    }
    free(aux);
}

int EsVacia(TCOLA c){
    if(c->final==NULL && c->inicio==NULL) return 0;
    else return 1;
}

void primerocola(TCOLA c, TELEMENTO* e){
    *e=c->inicio->elemento;
}
