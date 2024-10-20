#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"
#include "lista.h"
#define MAX_L 20
/**
 * Función por si se da el caso de que el usuario introduzca un nombre que sobrepase la memoria que tengo asignada de antemano.
 * 
 * @param nombre puntero al string a verificar
 * @param marca puntero al string a verificar
 * @param modelo puntero al string a verificar
 * @param ubicacion puntero al string a verificar
 * 
 * @return 1 en caso de que sobrepase la memoria asignada
*/
int verificar_longitud(char *nombre, char* marca, char *modelo, char *ubicacion) {
    if (nombre == NULL || marca == NULL || modelo == NULL || ubicacion == NULL) { 
        return 1; //Devuelvo 1 si es nulo
    }

    // Con string length verifico que no sobrepase ese maximo
    if (strlen(nombre) > MAX_L || strlen(marca) > MAX_L || strlen(modelo) > MAX_L || strlen(ubicacion) > MAX_L) {
        return 1; // Devuelvo 1 si alguna cadena lo sobrepasa.
    } else {
        return 0; // En caso de ser valido devuelve un 0
    }
}


/**
 * Funcion para verificar la existencia de la impresora que introduce el usuario.
 * 
 * @param lista puntero a la lista de la cual quiero verificar la existencia de la impresora.
 * @param nombre puntero al string del cual quiero comprobar su existencia.
 * 
 * @return 1 si encuentra el nombre.
*/
int verificar_existencia(TLISTA*  lista, char* nombre) {
    if (lista == NULL || nombre == NULL) { // Verifico si la lista o el nombre son nulos
        return 0;
    }

    TPOSICION actual;
    TPOSICION final = finLista(*lista);
    TIPOELEMENTOLISTA elemento_actual;
    //bucle que va a recorrer lal lista de impresoras de arriba a abajo
    for (actual = primeroLista(*lista); actual != final; actual = siguienteLista(*lista, actual)) {
        recuperarElementoLista(*lista, actual, &elemento_actual);//cupero cada elemento de cada impresora en cada iteracion para comprobar si existe el nombre
        if (strcmp(elemento_actual.nombre, nombre) == 0) {
            return 1; //si encuentra el nombre devuelve 1
        }
    }
    
    return 0; // En caso contrario devuelve un 0
}


/**
 * Funcion que va a obtener los datos de la impresora
 * 
 * @param lista puntero a la lsita de la que deseamosobtener los datos.
 * @param nombre puntero al string de la impresora que desamos obtener los datos
 * @param impresora puntero a la impresora de la que quiero obtener los datos
 * 
 * @return 1 si la lista es vacia o los nombres son iguales.
*/
int obtener_datos_impresora(TLISTA *lista, char* nombre, IMPRESORA* impresora){
    //el objetivo de esta funcion es que no se introduzcan impresoras con el mismo nombre
    TPOSICION actual ;
    TPOSICION final = finLista(*lista);
    if (esListaVacia(*lista)) {//si la ilsta es vacia devuelve 1
        return 1;
    }
    //recorro la lista de impresoras
    for (actual=primeroLista(*lista); actual != final; actual = siguienteLista(*lista, actual)) {
        recuperarElementoLista(*lista, actual, impresora);
        if (!strcmp(impresora->nombre, nombre)) {//comparo que los nombres no sean iguales
            return 0;//si no son iguales devuelvo 0
        }
    }
    return 1;
}

/**
 * Funcion para destruir la lista de impresoras.
 * 
 * @param lista puntero a lista a destruir
*/
void destruir_lista(TLISTA *lista){
    //hago esta funcion porque no se podian modificar las de la libreria, y de no hacerlo no libera la cola
    TPOSICION actual;
    IMPRESORA elemento_actual;
    TPOSICION final = finLista(*lista);
    if(!esListaVacia(*lista)){
        //recorro las impresoras
        for(actual=primeroLista(*lista); actual != final; actual = siguienteLista(*lista,actual)){
            recuperarElementoLista(*lista, actual, &elemento_actual);//Recupero el elemento y posteriormente destruyo la cola
            destruirCola(&(elemento_actual.trabajos));
        }
    }
    destruirLista(lista);//destruyo la lista
}

/**
 * Funcion para añadir una impresora a la lista
 * 
 * @param lista puntero a lista a la que quiero añadir una impresora.
 * @param impresora impresora que se desea añadir
*/
void añadir_impresora(TLISTA* lista, IMPRESORA impresora){
    IMPRESORA nueva;
    if (obtener_datos_impresora(lista, impresora.nombre, &nueva)){//hago la comprobacion por si se da el acso de que meta la misma impresora dos veces
        insertarElementoLista(lista, primeroLista(*lista), impresora);//inserto esta nueva impresora en la lista
    }
    else {
        printf("Esa impresora ya existe\n");//en caso de que ya exista sale el aviso y no es insertada en la lista
        destruirCola(&(impresora.trabajos));
    }
}

/**
 * Funcion que elemina una impresora dada.
 * 
 * @param lista puntero a la lista de la que quiero eliminar su impresora.
 * @param nombre puntero al string del nombre de la impresora a eliminar.
*/
void eliminar_impresora(TLISTA *lista, char* nombre){
    //funcion que recibe un nombre y elimina una impresora de la lista
    TPOSICION actual;
    IMPRESORA elemento_actual;
    TPOSICION final = finLista(*lista);
    if(!esListaVacia(*lista)){
        for(actual=primeroLista(*lista); actual != final; actual = siguienteLista(*lista,actual)){
            //recorro la lista reuperando cada impresora en cada iteración
            recuperarElementoLista(*lista, actual, &elemento_actual);
            if(strcmp(elemento_actual.nombre, nombre) == 0){
                //en caso de que el nombre de la impresora coincida con el que introduce el usuario
                destruirCola(&(elemento_actual.trabajos));//libero la memoria reservada anteriormente
                suprimirElementoLista(lista, actual);//suprimo ese elemento de la lista
                break;//hago que pare el bucle
            }
        }
        printf("Impresora %s eliminada\n", nombre);
    }
}

/**
 * Funcion que muestra las impresoras disponibles.
 * 
 * @param lista lista de la que quiero obtener los datos de todas las impresoras
*/
void impresoras_disponibles(TLISTA lista){
    //funcion que lee el contenido de la lista e imprime los nombres d los valores
    TPOSICION actual;
    IMPRESORA elemento_actual;
    TPOSICION final = finLista(lista);
    printf("Impresoras disponibles:\n");
    for(actual=primeroLista(lista); actual != final; actual = siguienteLista(lista,actual)){//recorro la lista
        recuperarElementoLista(lista, actual, &elemento_actual);//recupero cada elemento e imprimo en cada iteracion los valores
        printf("Impresora: %s %s %s %s\n", elemento_actual.nombre, elemento_actual.marca, elemento_actual.modelo,
        elemento_actual.ubicacion);//En cada iteracion del bucle escribo los datos de cada impresora      
        
    }
}

/**
 * Funcion para leer los datos del archivo,txt
 * 
 * @param archivo puntero al archivo que se desear abrir
 * @param lista puntero a la lista que se desea modoficar
 * 
 * @return 1 si tuvo algun problema al leer los datos
*/
int leer_datos_de_archivo(FILE *archivo, TLISTA* lista){
    //funcion para leer los datos del archivo
    char linea[1000];
    IMPRESORA impresora;
    if(archivo == NULL) {//hago la tipica comprobacion de si lo abre bien
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    while(fgets(linea, sizeof(linea), archivo)) {//ejecuto el bucle para leer 
        crearCola(&(impresora.trabajos));//creo mi impresora
        if(sscanf(linea, "%s %s %s %s", impresora.nombre, impresora.marca, impresora.modelo, impresora.ubicacion) < 4) {
            if(verificar_longitud(impresora.nombre, impresora.marca, impresora.modelo, impresora.ubicacion)){
                printf("El tamaño máximo que pueden tener los nombres introducidos es de 20 caracteres.\n");
                return(EXIT_FAILURE);
            }
            //en caso de que el usurio no complete algun campo de los requeridos, saltará un mensaje de error
            printf("Error al leer los datos de la impresora. Debes introducir nombre, marca, modelo y ubicacion.\n");
            destruirCola(&(impresora.trabajos));
            return 1;
        } else{//en caso contrario inserto la impresora en la lista
            insertarElementoLista(lista, finLista(*lista), impresora);
        }
    }
    return 0;
}

/**
 * Funcion para cargar los datos del archivo.
 * 
 * @param nombre_archivo puntero al string del nombre del archivo.
 * @param lista puntero la lsita que se desea modificar.
 * 
 * @return 1 si tuvo algun problema para abrilos
*/
int cargar_Datos(char* nombre_archivo, TLISTA* lista){
    //para cargar los datos de la impresora
    FILE* archivo;
    archivo = fopen(nombre_archivo, "r");//lo abro
    if(*lista!=NULL){//lo hago por si se da el improbable caso de que la lista no esté vacía
        printf("No puedes cargar datos en una lista que no sea vacía\n");
        fclose(archivo);
        return 1;
    }
    crearLista(lista);//creo mi lista
    
    if(archivo == NULL){//compruebo que el archivo se abra correctamente
        printf("Error al abrir el archivo\n");
        destruir_lista(lista);
        fclose(archivo);
        return 1;
    }
    
    if(leer_datos_de_archivo(archivo, lista)){//si detecta un error al leer los datos destruye la impresora
        destruir_lista(lista);
        fclose(archivo);
        return 1;
    }

    fclose(archivo);
    return 0;
}

/**
 * Funcion que añade un nuevo trabajo a la cola de trabajos de impresion de una impresora dada
 * 
 * @param lista puntero a la lista que se va a modificar
 * @param nombre puntero al string del nombre de la impresora
 * @param trabajo entero que representa el identificador de cada trabajo
*/
void nuevo_trabajo(TLISTA* lista, char* nombre, int trabajo){
    //funcion a la que le paso lista nombre de impresora y un entero que se corresponde con el identificador de un trabajo a imprimir
    IMPRESORA impresora;
    if(!obtener_datos_impresora(lista, nombre, &impresora)){//compruebo que el nombre introducido este en la lista
        anadirElementoCola(&(impresora.trabajos), trabajo);//inserto en la cola de esa impresora el elemento
        printf("Se ha añadido el trabajo %d a la impresora %s\n", trabajo, nombre);
    }
    else printf("Esa impresora no ha sido declarada anteriormente.\n");
}

/**
 * Funcion que muestra los trabajos pendientes de una impresora dada.
 * 
 * @param lista puntero a la lsita de la que se desean leer los trabajos
 * @param nombre puntero al string de la impresora de la cual deseo obtener los trabajos pendientes
*/
void trabajos_pendientes(TLISTA *lista, char *nombre){
    //funcion a la que le paso una lista y el nombre de una impresora
    IMPRESORA impresora;
    TIPOELEMENTOCOLA trabajo;
    int longitud;
    int i;
    if (!obtener_datos_impresora(lista, nombre, &impresora)){//compruebo que exista la impresora con el nombre que me pasa
        longitud = longitud_Cola(impresora.trabajos);
        printf("Trabajos pendientes de %s: %d\n", nombre, longitud);//Escribo el numero de trabajos que le quedan
        for (i = 0; i < longitud; i++){
            consultarPrimerElementoCola(impresora.trabajos, &trabajo);//consulto el elemento de la cola
            anadirElementoCola(&(impresora.trabajos), trabajo);
            suprimirElementoCola(&(impresora.trabajos));
            printf("Trabajo pendiente %d: Trabajo %d\n", i + 1, trabajo);//imprimo el elemento de la cola
        }
    } else {
        printf("No hay tareas pendientes.\n");
    }
}

/**
 * Funcion que imprime los trabajos de una impresora dada.
 * @param lista puntero a la lsita de la que se desean leer los trabajos
 * @param nombre puntero al string de la impresora de la cual deseo obtener los trabajos pendientes
*/
void imprimir_trabajos(TLISTA *lista, char *nombre){
    //funcion que va a imprimir el primer trabajo que se introdujo de una impresora dada
    IMPRESORA impresora;
    TIPOELEMENTOCOLA trabajo;
    if(!obtener_datos_impresora(lista, nombre, &impresora)){
        if(!esColaVacia(impresora.trabajos)){//la cola debe tenre algun elemento
            consultarPrimerElementoCola(impresora.trabajos, &trabajo);//consulta el primero
            suprimirElementoCola(&(impresora.trabajos));
            printf("Imprimendo la tarea %d de la impresora %s\n", trabajo, nombre);
        }
        else{
            printf("No tienes ninguna trabajo para imprimir\n");
        }
    }
}

/**
 * Funcion que imprime la impresora con menos trabajos pendientes
 * 
 * @param lista puntero a la lista de la que voy a leer los datos
*/
void impresora_menos_trabajos(TLISTA lista){
    //función que me va a imprimir por pantalla la impresora con menos trabajos pendientes
    TPOSICION actual;
    IMPRESORA impresora;
    TPOSICION final = finLista(lista);

    int min_trabajos = 1000; // Establezo un mínimo inicial 
    char nombre_min_trabajos[MAX_L]; // uso esto para guardar el nombre de la impresora con menos trabajos pendientes

    if (!esListaVacia(lista)){
        for (actual = primeroLista(lista); actual != final; actual = siguienteLista(lista, actual)){ // recorro la lista
            recuperarElementoLista(lista, actual, &impresora);
            int num_trabajos = longitud_Cola(impresora.trabajos); // obtengo la longitud de la cola de cada impresora
            if (num_trabajos < min_trabajos) { 
                min_trabajos = num_trabajos; // actualizo el mínimo
                strncpy(nombre_min_trabajos, impresora.nombre, MAX_L); // gurado el nombre de la impresora con menos trabajos
            }       
        }
        printf("Impresora con menos trabajos pendientes: %s, Trabajos pendientes: %d\n", nombre_min_trabajos, min_trabajos);
    }
    else {
        printf("La lista de impresoras está vacía.\n");
    }
}

/**
 * Funcion que se encarga de modificar el txt
 * 
 * @param nombre_archivo puntero al nombre del archivo que se desea modificar
 * @param lista lista de la cual se desea obtener los nombres de las impresoras
*/
void modificar_txt(char* nombre_archivo, TLISTA lista){
    //función cuyo objetivo es sobreescribir el txt para que al cerrar el programa la lista de impresoras se actualizada
    TPOSICION actual;
    TPOSICION final=finLista(lista);
    IMPRESORA impresora_actual;
    FILE* archivo;
    archivo=fopen(nombre_archivo,"w");
    if (archivo == NULL) {//compruebo que el archivo se abra correctamente
        printf("Error al abrir el archivo\n");
        fclose(archivo);
    }

    for(actual=primeroLista(lista); actual!=final; actual=siguienteLista(lista, actual)){
        recuperarElementoLista(lista,actual,&impresora_actual);//recupero el elemento y uso el fprintf porque sobreescribe el archivo
        fprintf(archivo,"%s %s %s %s\n",impresora_actual.nombre, impresora_actual.marca, impresora_actual.modelo, impresora_actual.ubicacion);

    }
}


int main(int argc, char** argv){
    TLISTA lista=NULL;
    if(argc<2){
        printf("Necistas al menos dos argumentos\n");
        return 1;
    }
    else if (cargar_Datos(argv[1], &lista)){
        printf("No se han podido cargar los datos.\n");
        return 1;
    }
    char opcion;
    char nombre[20];
    do{
        printf("------------------------\n");
        printf("a) Eliminar impresora\n");
        printf("b) Añadir impresora\n");
        printf("c) Enviar trabajo\n");
        printf("d) Escribir listado de trabajos pendientes de impresión\n");
        printf("e) Imprimir trabajo\n");
        printf("f) Buscar impresora con poca carga\n");
        printf("s) Salir del programa\n");
        scanf(" %c", &opcion); 

        switch (opcion){
        case 'a':
            if(esListaVacia(lista)){
                printf("No tienes ninguna impresora en la lista, así que no la puedes eliminar.\n");
                break;
            }
            printf("Introduce el nombre de la impresora:\n");
            scanf(" %s",nombre);
            if(verificar_longitud(nombre, nombre, nombre, nombre)){
                printf("El tamaño máximo que pueden tener los nombres introducidos es de 20 caracteres.\n");
                break;
            }
            if(verificar_existencia(&lista,nombre)==0){
                printf("Esa impresora no ha sido declarada, por lo que no puedes eliminarla.\n");
                break;
            }
            eliminar_impresora(&lista, nombre);
            impresoras_disponibles(lista);
            
            break;
        case 'b': 

            IMPRESORA impresora;
            crearCola(&(impresora.trabajos));//creo esta impresora
            printf("Introduce el nombre:\n");//guardo los datos en cada campo
            scanf("%s", impresora.nombre);
            printf("Introduce la marca:\n");
            scanf("%s", impresora.marca);
            printf("Introduce el modelo:\n");
            scanf("%s", impresora.modelo);
            printf("Introduce la ubicación:\n");
            scanf("%s", impresora.ubicacion);
            if(verificar_longitud(impresora.nombre, impresora.marca, impresora.modelo, impresora.ubicacion)==1){
                printf("El tamaño máximo que pueden tener los nombres introducidos es de 20 caracteres.\n");
                break;
            }
            //añado la impresora a la lista
            añadir_impresora(&lista,impresora);
            
            impresoras_disponibles(lista);
            
            break;
        case 'c':
            char nombre[20];
            int trabajo;
            printf("Introduce el nombre de la impresora en la que deseas añadir la tarea:\n");
            scanf(" %s", nombre);
            if(verificar_longitud(nombre, nombre, nombre, nombre)){
                printf("El tamaño máximo que pueden tener los nombres introducidos es de 20 caracteres.\n");
                break;
            }
            if( verificar_existencia(&lista,nombre)==0){
                printf("Esa impresora no ha sido declarada, por lo que no puedes enviarle un trabajo.\n");
                break;
            }
            printf("Introduce el identificador de la tarea:\n");
            scanf(" %d",&trabajo);
            nuevo_trabajo(&lista, nombre, trabajo);
            break;
        
        case 'd':
            printf("Introduce el nombre de la impresora:\n");
            scanf(" %s",nombre);
            if(verificar_longitud(nombre, nombre, nombre, nombre)){
                printf("El tamaño máximo que pueden tener los nombres introducidos es de 20 caracteres.\n");
                break;
            }
            if(verificar_existencia(&lista,nombre)==0){
                printf("Esa impresora no ha sido declarada, por lo que no tienes trabajos pendientes.\n");
                break;
            }
            trabajos_pendientes(&lista, nombre);
            break;
        case 'e':
            printf("Introduce el nombre de la impresora:\n");
            scanf(" %s",nombre);
            if(verificar_longitud(nombre, nombre, nombre, nombre)){
                printf("El tamaño máximo que pueden tener los nombres introducidos es de 20 caracteres.\n");
                break;
            }

            if(verificar_existencia(&lista,nombre)==0){
                printf("Esa impresora no ha sido declarada, por lo que no tienes trabajos pendientes para poder imprimirlos.\n");
                break;
            }

            imprimir_trabajos(&lista, nombre);
            break;
        
        case 'f':
            impresora_menos_trabajos(lista);
            break;

        case 's':
            modificar_txt(argv[1],lista);
            destruir_lista(&lista);
            printf("Saliendo...\n");
            break;
        
        default:
            printf("Opcion incorrecta");
            break;
        }
    }
    while(opcion!='s');
    return 0;
}