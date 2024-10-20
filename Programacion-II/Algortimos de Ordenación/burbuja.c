#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"


void burbuja(vectorD *vector){
    unsigned long  i,j,intercambio;
    unsigned long  tam=tamano(*vector);
 	for(i=0; i<(tam-1); i++){
        intercambio=0;
 		for(j=0; j<(tam-i-1); j++)
 		    if(Componentei(*vector,j) > Componentei(*vector,j+1)){
                swap(vector,j,j+1);
            intercambio=1;
            }
    if(intercambio==0) break;
        
    }   
}