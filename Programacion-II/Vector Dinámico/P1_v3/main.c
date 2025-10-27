// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "vectordinamico.h"
#include <math.h>

void imprimir(vectorD v1){
    if(v1!=NULL){
        short i;
        short l =tamano(v1);
        printf("Los elementos del vector son: [");

        for(i=0; i<l;i++ ){
            printf("%f ", Componentei(v1,i));
        }    
        printf("]\n");
    }
    else printf("Error en imprimir: el vector no existe.\n");

}

float mediaGeometrica(vectorD v1){
    if(v1!=NULL){
        float producto=1.0;
        short l=tamano(v1);
        short i;
        for(i=0; i<l; i++){
            
            producto=producto*Componentei(v1,i);
        }
        return pow(producto,1.0/l);
    }
    else printf("Error, para obtener la media geométrica primero debes crear un vector\n");
    return 0.0;
}

float media(vectorD v1){
    if(v1!=NULL){
        float suma=0.0;
        short l=tamano(v1);
        short i;
        for(i=0; i<l; i++){
            suma=suma+Componentei(v1,i);
        }
        return suma/l;
    }
    else printf("Error, para obtener la media primero debes crear el vector.\n");
    return 0.0;
}


int main(int argc, char** argv){
    vectorD vector = NULL;
    short longitud, i;
    TELEMENTO valor;
    char opcion;
  
    if (argc < 2) {
        printf("Error: Se necesitan al menos dos argumentos (nombre del programa y al menos un valor para el vector).\n");
        return EXIT_FAILURE;
    }

    longitud = argc-1;

    if (longitud <= 0) {
        printf("Error: La longitud del vector debe ser un número entero positivo.\n");
        return EXIT_FAILURE;
    }

    CreaVector(&vector, longitud);

    for (i = 0; i < longitud; i++) {
        valor = atof(argv[i + 1]);
        AsignaVector(&vector, i, valor);
    }
    
    do{
        printf("a) Crear vector\n");
        printf("b) Liberar vector\n");
        printf("c) Imprimir vector\n");
        printf("d) Media Geométrica\n");
        printf("e) Media\n");
        printf("s) Salir\n");
        printf("Opcion: ");
        scanf(" %c", &opcion);

        switch (opcion){
            case 'a':
                LiberaVector(&vector);
                vector=NULL;
                longitud=0;
                printf ("Introduce el tamaño del vector:\n");
                scanf("%hd",&longitud);

                if(longitud <= 0) {
                    printf("Introduce una logitud válida.\n") ;
                    break;
                }

                CreaVector(&vector, longitud);

                for(i=0; i<longitud; i++){
                    printf("Elemento (%hd) del vector:\n", i);
                    scanf("%f",&valor);
                    AsignaVector(&vector,i,valor);
                }
                break;

            case 'b':
                LiberaVector(&vector);
                vector=NULL;
                printf("Vector liberado.\n");
                break;

            case 'c':
                imprimir(vector);
                break;

            case 'd':
                printf("La media geométrica del vector es:%f\n",mediaGeometrica(vector));
                break;
            case 'e':
                printf("La media del vector es:%f\n",media(vector));
                break;
            
            case 's':
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción incorrecta\n");
                break;
        }


    } while (opcion!='s');
    LiberaVector(vector);
    vector=NULL;
    return (EXIT_SUCCESS);   
}
