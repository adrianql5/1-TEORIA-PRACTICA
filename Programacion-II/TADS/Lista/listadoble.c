#include <stdio.h>
#include <stdlib.h>
typedef int TELEMENTO;

typedef struct nodolista{
    TELEMENTO dato;
    struct nodolista* pos;
    struct nodolista* ant;    
}TNODO;

typedef TNODO* TPOSICION;

typedef struct{
    TPOSICION inicio;
    TPOSICION fin;
    TPOSICION longitud;
}STLISTA;

typedef STLISTA* TLISTA;

void crear(TLISTA *l){
    *l=(TLISTA)malloc(sizeof(STLISTA));
    (*l)->inicio=(TPOSICION)malloc(sizeof(TNODO));
    (*l)->inicio->pos=NULL;
    (*l)->inicio->ant=NULL;
    (*l)->fin=(*l)->inicio;
}

void insertar(TLISTA *l, TPOSICION p, TELEMENTO e){
    TPOSICION aux;
    aux=(TPOSICION)malloc(sizeof(TNODO));
    aux->dato=e;
    TPOSICION anterior;
    TPOSICION posterior;

    anterior=p->ant;
    posterior=p->pos;

    aux->ant=anterior->pos;
    aux->pos=posterior->ant;

    anterior->pos=aux->ant;
    posterior->ant=aux->pos;

    if(aux->pos==NULL){
        (*l)->fin=aux;
    }

    else if(aux->ant==NULL){
        (*l)->inicio=aux;
    }

    (*l)->longitud++;
}

void suprimir(TLISTA* l, TPOSICION p,TELEMENTO e ){
    TPOSICION anterior= p->ant;
    TPOSICION posterior= p->pos;


    anterior->pos=posterior;
    posterior->ant=anterior;

    free(p);

    if(anterior->pos==NULL){
        (*l)->fin=anterior;
    }

    if(posterior->ant==NULL){
        (*l)->inicio=posterior;
    }

    (*l)->longitud--;
}
