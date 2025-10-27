#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"
#include <string.h>

//Funcion que recibe la cantidad a cambiar, los valores faciales a tenre en cuenta, el vector que contendra la solucion, y el vector que modificará el stock
void cambio(int x, vectorD valor,vectorD *solucion,vectorD *stock){
    for (int i=0;i<tamano(valor);i++) AsignaVector(solucion,i,0);
    int i=0, suma=0;
    vectorD aux= NULL;
    CreaVector(&aux,tamano(*stock));//creo este vector aux por si se da el caso de que no pueda devolver el cambio, y asi consigo que no me modifique el stock anterior
    for(i=0; i<tamano(*stock);i++){
        AsignaVector(&aux,i,Componentei(*stock,i));
    }

    i=0;//asi uso la misma variable

    if(!EsNulo(*stock)){//con esto consigo hacer que detecte si estoy usando el modo limitado o ilimitado
        while ((suma<x) && (i<tamano(valor)))//ejecuto el algortimo
            if (suma+Componentei(valor,i)<=x && Componentei(*stock,i)>=1){//le añado la ocndicion de que ademas el stock correspondiente a esa posicion debe de ser mayor o igual que 1.
                AsignaVector(solucion,i,Componentei(*solucion,i)+1);//con eso aumento la solucion en su correspondiente posicion
                AsignaVector(stock,i,Componentei(*stock,i)-1);//asi decremetno el stock
                suma+=Componentei(valor,i);
            }
            else
                i++;
            if (suma==x);
            else{
                printf("No se pudo devolver el cambio. Prueba a añadir más stock.\n");
                for (int i=0;i<tamano(valor);i++){//en caso de que no lo haya podido devolver, recupera esos valores anteriores del stock para que no se vea alterado.
                    AsignaVector(solucion,i,0);
                    AsignaVector(stock,i,Componentei(aux,i));
                } 
                
            }
        }
    else{
        while ((suma<x) && (i<tamano(valor)))//ejecuto lo de antes pero sabiendo que es Nulo el stock simplifica bastante el algoritmo
            if (suma+Componentei(valor,i)<=x){
                AsignaVector(solucion,i,Componentei(*solucion,i)+1);
                suma+=Componentei(valor,i);
            }
            else
                i++;
            if (suma==x);
            else{
                printf("Quizás con los valores faciales dados no es posible devolver esa cantidad\n");
                for (int i=0;i<tamano(valor);i++) AsignaVector(solucion,i,0);
            }
    }
    LiberaVector(&aux);
}


//funcion que va a permitir añadir más stock al que estaba disponible, recibe el vector del stock, y el nombre del archivo
void añadirstock(vectorD v2, char* cadena) {
    FILE *archivo = fopen(cadena, "w");//abro en modo escritura
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo stock.txt\n");
        return;
    }
    
    int i;
    for (i = 0; i < tamano(v2)-1; i++) {//escribo los elementos del vector
        fprintf(archivo,"%d\n", Componentei(v2, i));
    }
    fprintf(archivo,"%d",Componentei(v2,tamano(v2)-1));//hago esto para que no me ponga ese ultimo salto de linea porque da problemas despues apra leer

    fclose(archivo);
}

//funcion para cargar el stock del txt a mi vector de stock
void leerstock(vectorD *v1,char* cadena) {
    FILE* archivo = fopen(cadena, "r");//lo abro en modo de lectura
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo stock.txt, asegurate de que no esté vacío y tenga el mismo número de lineas que valores faciales.\n");
        return;
    }

    int valor;
    int i = 0;
    while (fscanf(archivo, "%d", &valor) != EOF && i < tamano(*v1)) {//voy asignando al vectro stock cada elemento del txt
        AsignaVector(v1, i, valor);
        i++;
    }
   fclose(archivo);
}


void imprimir(vectorD v1, vectorD v2){//funcion que imprime los valores de los vectores que le pase
    if(v1!=NULL){
        int i;
        int l =tamano(v1);

        for(i=0; i<l;i++ ){
            if(Componentei(v1,i)!=0) {//esta condicion la pongo para que no imprima tanta cosa.
                printf("Billetes / Monedas de %d: ", Componentei(v2,i));//asi me pone el valor facial
                printf("%d\n", Componentei(v1,i));//y su correspondiente cambio/stock disponible
            
            }
        }    
        printf("\n");
    }
    else printf("Error en imprimir: el vector no existe.\n");

}
