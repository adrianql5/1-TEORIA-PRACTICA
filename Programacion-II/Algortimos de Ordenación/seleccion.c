// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"

void seleccion(vectorD *vector){
    unsigned long i,j,PosMenor;
    unsigned long tam=tamano(*vector);
    for(i=0; i<(tam-1); i++){
        PosMenor=i;
        for(j=i+1; j<tam;j++) if(Componentei(*vector,j)<Componentei(*vector,PosMenor))    PosMenor=j;
        swap(vector,i,PosMenor);
    }
}
