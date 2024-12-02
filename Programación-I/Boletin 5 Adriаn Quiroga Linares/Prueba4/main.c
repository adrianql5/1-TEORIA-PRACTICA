#include "meteo.h"
#include <stdio.h>
//HAGO ESTA PRUEBA PARA COMPORBAR QUE HA LEIDO TODO CORRECTAMENTE, SOLO LE PASO DOS ARCHIVOS PORQUE DE PASARLE MAS ESTARIA ESCRIBIENDO RESULTADOS POR PANTALLA DEMSAIDO TIEMPO
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s archivo1.csv archivo2.csv ...\n", argv[0]);
        return 1;
    }
    WeatherStation *array_weatherstation = CrearArrayWeatherStation((const char **)argv + 1, argc - 1);
    ImprimirArrayWeatherStation(array_weatherstation,argc-1);
    free_Array_WeatherStation(array_weatherstation, argc - 1);

    return 0;
}
