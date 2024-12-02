//Autor: Adrián Quiroga Linares
//Data: 28/11/2023
//Versión:1
//Este programa ten como proposito observar que pasa cando


#include <stdio.h>

int main() {

    int ne = 10;
    float nf = 3.14;

    int *pe;
    float *pf;

    // Asigno a direccion de memoria dos punteiros
    pe = &ne;
    pf = &nf;

    // Escribo os valores dos punteiross
    printf("Valor do punteiro int*: %d\n", *pe);
    printf("Valor do punteiro float*: %f\n", *pf);

    // Asigno  o valor oposto a como o fixen antes
    pe = (int*)&nf;
    pf = (float*)&ne;

    // Volvo a imprimir os resultados
    printf("Novo valor do punteiro int*: %d\n", *pe);
    printf("Novo valor do punteiro float*: %f\n", *pf);

    return 0;
}
//Cambian porque estan interpretando os bits en memoria de maneira diferente
