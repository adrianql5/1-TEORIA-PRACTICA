// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"
#include "monedas.h"

int main(int argc, char**argv) {
    vectorD valor = NULL;
    vectorD solucion = NULL;
    vectorD stock = NULL;
    char opcion1;
    char opcion2;
    FILE* archivo1;
    int i = 0; 
    int tamañotxt=0;
    
    char linea[100];
    int x;
    int dato;

    if(argc!=3){//por si lo que introduce es incorrecto
        printf("Debes introducir:\n");
        printf("Nombre del ejecutable.\n");
        printf("Nombre del archivo que contiene los valores faciales.\n");
        printf("Nombre del archivo que contiene el stock de esa moneda.\n");
    }    

    archivo1 = fopen(argv[1], "r");//cojo el primer archivo que se corresponde a los valores faciales de esa moneda
    if (archivo1 == NULL) {
        printf("No se pudo abrir el archivo, asegurate de que no esté vacío.\n");
        return 1;
    }
    while (fgets(linea, sizeof(linea), archivo1) != NULL) {//cuento el tamaño
        tamañotxt++;
    }

    CreaVector(&valor, tamañotxt-1);//creo los vectores
    CreaVector(&solucion, tamañotxt-1);//les resto uno porque los txt contienen una primera linea que pone el tipo de divisa que se va a usar
    
    rewind(archivo1);//vuelvo al inicio del archivo
    fgets(linea, sizeof(linea), archivo1);
    printf("Divisa a usar: %s\n",linea);//salto la primera linea

    while (fgets(linea, sizeof(linea), archivo1) != NULL) {
        dato = atoi(linea);
        AsignaVector(&valor, i, dato);//Asigno los datos al vector de valores faciales
        i++;
    }

    fclose(archivo1);//cierro mi archivo



    do{
        printf("Introduce el modo:\n");
        printf("a) Monedas Ilimitadas\n");
        printf("b) Monedas Limitadas\n");
        printf("s) Salir\n");
        scanf(" %c", &opcion1);
    
        switch (opcion1) {
            case 'a'://modo stock ilimitado
                printf("Introduce la cantidad que deseas cambiar:\n");
                scanf("%d", &x);
                printf("Cambio: \n");
                cambio(x, valor, &solucion,&stock);//llamo a mi funcion qeu devuelve el cambio
                imprimir(solucion, valor);//imprimo la solucion en base a los valores faciales
                break;
            
            case 'b':
                CreaVector(&stock, tamañotxt-1);//creo mi vector de stock
                leerstock(&stock,argv[2]);//leo la informacion
                printf("Stock disponible:\n");
                imprimir(stock,valor);//imprimo los datos que acabo de leer
                do{
                    printf("¿Qué deseas hacer?\n");
                    printf("a)Dar cambio\n");
                    printf("b)Introducir Stock\n");
                    printf("c)Cambiar al menú anterior\n");
                    scanf(" %c",&opcion2);
                    switch (opcion2){
                        case 'b':
                            printf("Se han añaidido 10 monedas de cada tipo.\n");
                            for(i = 0; i < tamano(stock); i++){ //voy asignando el stock que voy a añadir al vector 
                                AsignaVector(&stock, i,Componentei(stock, i)+10);
                            }
                            añadirstock(stock,argv[2]);
                            leerstock(&stock,argv[2]);
                            printf("Stock disponible:\n");
                            imprimir(stock,valor);
                            break;

                        
                        case 'a':
                            printf("Introduce la cantidad que deseas cambiar:\n");
                            scanf("%d",&x);
                            printf("Cambio: \n");
                            cambio(x,valor,&solucion,&stock);//llamo a la funcion cambio
                            imprimir(solucion,valor);//imprimo el cambio correspondiente
                            imprimir(stock,valor);
                            añadirstock(stock,argv[2]);//añado el nuevo stock al txt
                            
                            break;
                        
                        case 'c':
                            printf("Cambiando de modo...\n");
                            LiberaVector(&stock);
                        
                        default:
                            printf("Opcion incorrecta.\n");
                            break;
                        }

                }while(opcion2!='c');
                
                    
            case 's':
                printf("Saliendo del programa\n");            

            default:
                break;
        }

    }while (opcion1!='s');
    

    LiberaVector(&valor);
    LiberaVector(&solucion);
    LiberaVector(&stock);

    return 0;
}
