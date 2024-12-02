#include "meteo.h"
#include <stdio.h>
#include <stdlib.h>
//EN ESTA PRUEBA INTRODUZCO LA PRIMERA FECHA SIENDO POSTERIOR A LA PRIMERA

#define MAX_NOMBRE 50

char** leer_nombres_desde_archivo(const char* ruta_archivo, int* cantidad_nombres) {
    FILE* archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s\n", ruta_archivo);
        return NULL;
    }

    char** nombres = NULL;
    char nombre[MAX_NOMBRE];
    int contador = 0;

    while (fscanf(archivo, "%s", nombre) == 1) {
        contador++;
    }

    fseek(archivo, 0, SEEK_SET);

    nombres = (char**)malloc(contador * sizeof(char*));
    if (nombres == NULL) {
        printf("Error: No se pudo asignar memoria para el array de nombres\n");
        fclose(archivo);
        return NULL;
    }

    for (int i = 0; i < contador; i++) {
        nombres[i] = (char*)malloc(MAX_NOMBRE * sizeof(char));
        if (nombres[i] == NULL) {
            printf("Error: No se pudo asignar memoria para almacenar un nombre\n");
            fclose(archivo);
            for (int j = 0; j < i; j++) {
                free(nombres[j]);
            }
            free(nombres);
            return NULL;
        }
        fscanf(archivo, "%s", nombres[i]);
    }

    fclose(archivo);
    *cantidad_nombres = contador;
    return nombres;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s archivo1.csv archivo2.csv ...\n", argv[0]);
        return 1;
    }

    int cantidad_archivos = argc - 1;
    char*** nombres_archivos = (char***)malloc(cantidad_archivos * sizeof(char**));
    int* cantidad_nombres = (int*)malloc(cantidad_archivos * sizeof(int));

    for (int i = 0; i < cantidad_archivos; i++) {
        nombres_archivos[i] = leer_nombres_desde_archivo(argv[i + 1], &cantidad_nombres[i]);

        if (nombres_archivos[i] == NULL){
            continue;
        }


        WeatherStation *array_weatherstation = CrearArrayWeatherStation((const char **)nombres_archivos[i], cantidad_nombres[i]);

        Data fechaInicio = {31, 12, 2010};
        Data fechaFin = {1, 1, 2000};
        TemperaturasExtremas extremas = ObtenerTemperaturasExtremas(array_weatherstation, cantidad_nombres[i], fechaInicio, fechaFin);
        printf("\nTemperaturas Extremas:\n");
        ImprimirTemperaturasExtremas(extremas);

        Data fechaMedia = {1, 1, 2000};
        TemperaturasMedias medias = ObtenerTemperaturasMedias(array_weatherstation, cantidad_nombres[i], fechaMedia);
        printf("\nTemperaturas Medias:\n");
        ImprimirTemperaturasMedias(medias);

        free_Array_WeatherStation(array_weatherstation, cantidad_nombres[i]);
    }

    for (int i = 0; i < cantidad_archivos; i++) {
        if (nombres_archivos[i] != NULL) {
            for (int j = 0; j < cantidad_nombres[i]; j++) {
                free(nombres_archivos[i][j]);
            }
            free(nombres_archivos[i]);
        }
    }
    free(nombres_archivos);
    free(cantidad_nombres);

    return 0;
}

