// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vectordinamico.h"
#include "quicksort.h"
#include "burbuja.h"
#include "seleccion.h"

void imprimir(vectorD v1){//cogí esta fucnion del anterior trabajo para poder comprobar el correcto funcionamiento de los algortimos de ordencion
    if(v1!=NULL){
        unsigned long i;
        unsigned long l =tamano(v1);
        printf("Los elementos del vector son: [");

        for(i=0; i<l;i++ ){
            printf("%d ", Componentei(v1,i));
        }    
        printf("]\n");
    }
    else printf("Error en imprimir: el vector no existe.\n");

}

int main(int argc, char **argv) {
    vectorD vector = NULL;
    unsigned long principio;
    unsigned long final;
    unsigned long paso;
    char opcion;
    FILE *fp1, *fp2, *fp3;//esto será usado para escribir los datos recogidos
    if (argc == 5) {
        principio= strtoul(argv[2],NULL,10);//tamaño incial
        final = strtoul(argv[3],NULL,10);//tamaño final
        paso = strtoul(argv[4],NULL,10);//paso que dará en cada iteración del bucle
        opcion = *argv[1];//parametro del siwtch case que permite escoger uno u otro algortimo que se desee probar

    } else {
        printf("Debes introducir los campos: archivo,opcion, inicio, final, paso.\n");
        printf("Las opciones son:\n");
        printf("a: quicksort\n");
        printf("b: bublesort\n");
        printf("c: seleccion\n");

        return 1;
    }

    switch(opcion){
        case 'a':
            fp1 = fopen("Quicksort.txt", "w");//abro el archivo de escritura de los datos del quicksort
            fprintf(fp1, "Datos de quicksort:\n");
            for (; principio< final; principio = principio*paso) {//declaro el bucle
                CreaVector(&vector, principio);//creo mi vector
                inicializaVectorRand(&vector);//le asigno valores aleatorios en cada posicion
                //imprimir(vector);
                clock_t inicio = -1, fin = -1;

                inicio = clock();//incio el clock

                quicksort(&vector, 0, principio);//pongo el algoritmo

                fin = clock();//finalizo el clock
                //imprimir(vector);
                fprintf(fp1, "Tamaño del vector:%lu\tInicio:%lu\tFinal:%lu\tTiempo de ordenación:%lf\n", principio, inicio, fin, ((fin - inicio)/(double)CLOCKS_PER_SEC));//printeo los resultados en el txt
                LiberaVector(&vector);//libero cada vector creado
            }
            fclose(fp1);//cierro el archivo
        
        case 'b':
            fp2=fopen("Burbuja.txt","w");
            fprintf(fp2, "Datos de burbuja:\n");
            for (; principio < final; principio = principio + paso) {
                CreaVector(&vector, principio);
                inicializaVectorRand(&vector);
                //imprimir(vector);
                clock_t inicio = -1, fin = -1;

                inicio = clock();

                burbuja(&vector);

                fin = clock();
                //imprimir(vector);

                fprintf(fp2, "Tamaño del vector:%lu\tInicio:%lu\tFinal:%lu\tTiempo de ordenación:%lf\n", principio, inicio, fin, ((fin - inicio) /(double) CLOCKS_PER_SEC));
                LiberaVector(&vector);
            }
            fclose(fp2);

        case 'c':
            fp3 = fopen("Seleccion.txt", "w");
            fprintf(fp3, "Datos de seleccion:\n");
            for (; principio < final; principio = principio + paso) {
                CreaVector(&vector, principio);
                inicializaVectorRand(&vector);
                //imprimir(vector);
                clock_t inicio = -1, fin = -1;

                inicio = clock();

                seleccion(&vector);

                fin = clock();

                //imprimir(vector);

                fprintf(fp3, "Tamaño del vector:%lu\tInicio:%lu\tFinal:%lu\tTiempo de ordenación:%lf\n", principio, inicio, fin, ((fin - inicio) / (double) CLOCKS_PER_SEC));
                LiberaVector(&vector);
            }
            fclose(fp3);
    
    }

    return 0;
}
