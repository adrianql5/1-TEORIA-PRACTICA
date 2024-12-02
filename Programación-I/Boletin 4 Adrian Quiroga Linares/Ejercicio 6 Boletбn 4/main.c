#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Autor: Adrián Quiroga Linares
//Data: 4/12/2023
//Versión:1
//Este programa ten como obxectivo ler e almacenar datos dunha estacion correspondente nunha structura chamada station

typedef struct {
    // Defino a estructura para almacenar información sobre a estación meteorolóxica
    char nome[256];
    float lonxitude;
    float latitude;
    int elevacion;
} Station;


typedef struct {
    // Defino a estructura  para almacenar información sobre a data
    int dia;
    int mes;
    int ano;
} Data;


typedef struct {
    // Definimos a estrutura anidada que conten información sobre a estación, data e datos meteorolóxicos
    Station nome_y_ubicacion;
    Data fecha;
    float max_temperature;
    float min_temperature;
    float precipitacion;
    float viento;
    float humedad;
    float solar;
} Weatherdata;


Weatherdata* leer_datos(const char* camino_archivo, int* numero_datos) {// Función para ler datos desde un arquivo CSV
    FILE* archivo;
    int i = 0;
    Weatherdata* datos;

    archivo = fopen(camino_archivo, "rt");//Abro o arquivo
    if (archivo == NULL) {//Fago a comprobacion de que o fixera correctamente
        perror("Dirección de arquivo incorrecta");
        exit(EXIT_FAILURE);
    }


    char nome_estacion[256];
    strncpy(nome_estacion, camino_archivo, sizeof(nome_estacion));
    //con esto copio no nome da estacion o nome do arquivo
    char* extension = strstr(nome_estacion, ".csv");//elimino a extension
    if (extension != NULL) {
        *extension = '\0';//Aseguro que remate nun caracter nulo
    }


    datos = (Weatherdata*)malloc(sizeof(Weatherdata));//fago a reserva de memoria para almacenar os datos
    if (datos == NULL) {
        perror("Erro ao reservar memoria");
        exit(EXIT_FAILURE);
    }


    strncpy(datos[i].nome_y_ubicacion.nome, nome_estacion, sizeof(datos[i].nome_y_ubicacion.nome));
    //pasolle o nome da estacion á estructura

    fseek(archivo, 0, SEEK_SET);//movo o cursor ao inicio do arquivo
    while (fgetc(archivo) != '\n');//salto a primeira liña


    while (fscanf(archivo, "\"%d/%d/%d\",\"%f\",\"%f\",\"%d\",\"%f\",\"%f\",\"%f\",\"%f\",\"%f\",\"%f\",\n",
                  &datos[i].fecha.mes, &datos[i].fecha.dia, &datos[i].fecha.ano, &datos[i].nome_y_ubicacion.lonxitude,
                  &datos[i].nome_y_ubicacion.latitude, &datos[i].nome_y_ubicacion.elevacion,
                  &datos[i].max_temperature, &datos[i].min_temperature, &datos[i].precipitacion, &datos[i].viento,
                  &datos[i].humedad, &datos[i].solar) == 12) {
        //bucle para ler os datos do arquivo
        i++;

        datos = realloc(datos, (i + 1) * sizeof(Weatherdata));
        //incremento o tamaño do array de datos en cada iteracion porque o tmaaño de memroia necesitada vai aumentando
        if (datos == NULL) {
            perror("Erro ao realoxar memoria");
            exit(EXIT_FAILURE);
        }
    }

    *numero_datos = i;//actualizo o numero total de datos leidos

    fclose(archivo);
    return datos;
}


int main() {

    const char* camino_archivo = "weatherdata-420-72.csv";//ruta do arquivo csv
    int numero_datos;
    int i;


    Weatherdata* datos_estacion = leer_datos(camino_archivo, &numero_datos);//chamo á funcion leer e lle paso a ruta ao arquivo e a direccion dos datos


    printf("Nome: %s, Latitude: %f, Lonxitude: %f, Elevación: %d\n",
           datos_estacion[0].nome_y_ubicacion.nome,
           datos_estacion[0].nome_y_ubicacion.latitude,
           datos_estacion[0].nome_y_ubicacion.lonxitude,
           datos_estacion[0].nome_y_ubicacion.elevacion);//imprimo os datos da primeira liña, posto que non varían


    for (i = 0; i < numero_datos; i++) {
        printf("Fecha: %d/%d/%d, MaxTemperature: %f, MinTemperature: %f, Precipitacion: %f, Viento: %f, Humedad: %f, Solar: %f\n",
               datos_estacion[i].fecha.dia, datos_estacion[i].fecha.mes, datos_estacion[i].fecha.ano,
               datos_estacion[i].max_temperature, datos_estacion[i].min_temperature,
               datos_estacion[i].precipitacion, datos_estacion[i].viento,
               datos_estacion[i].humedad, datos_estacion[i].solar);
    }//imprimo o resto de datos almacenados


    free(datos_estacion);
    return 0;
}
