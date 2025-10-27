#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"

unsigned long choose_pivot(unsigned long i, unsigned long j){
    return ((i+j)/2);
}

void quicksort(vectorD *vector, unsigned long inicio, unsigned long final){
    if (final>inicio+1){
        TELEMENTO piv = Componentei(*vector, inicio);
        unsigned long l =inicio+1, r=final;

        while(l<r){
            if(Componentei(*vector,l)<=piv)
            l++;
            else{
                r--;
                swap(vector,l,r);
            }
        }
        l--;
        swap(vector,l,inicio);
        quicksort(vector,inicio,l);
        quicksort(vector,r,final);
    }
}
