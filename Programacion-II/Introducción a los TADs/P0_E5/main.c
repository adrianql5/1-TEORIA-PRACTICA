//a)&a[0]: 0x7fffffffd8a0. &a[1]: 0x7fffffffd8a4 &a[0]: 0x7fffffffd8a8 &a[3]: 0x7fffffffd8ac
//b)La mayor es &a[3]: 0x7fffffffd8ac y la menor es  La diferencia es de 4 bytes, debido a que cada posicion de un array va incrementando su valor en 4 bytes. AL ser posiciones consecutivas de un array se puede apreciar fácilmente gracias al panel de Watch.

#include <stdio.h>

double absoluto( double n){
    return (n<0) ? -n :n;
}

double sqrt(double numero){
    double margen = 0.000001;
    double estimacion = 1.0;
    while(absoluto((estimacion*estimacion)-numero)>=margen){
        double cociente = numero/estimacion;
        double promedio=(cociente+estimacion)/2.0;
        estimacion=promedio;
    }
    return estimacion;
}

int main(int argc, char ** argv){
    int a[4]={1,2,3,4};
    float L[4];
    int i=0;
    for(i; i<4; i++){
        L[i]=sqrt(a[i]);
    }
    return 0;
}
