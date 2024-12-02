#include "meteo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void ValidarFechaEnMargen(Data fecha){
    //Creo esta funcion por si se de el caso de que el usuario introuzca una fehca que no se encuentra dentro del margen
    Data fechaLimiteInferior = {1, 1, 2000};//Defino las fechas limite
    Data fechaLimiteSuperior = {31, 12, 2010};
    //con este condicional le digo las conciones para que se encuentre dentro del margen
    if ((fecha.año > fechaLimiteInferior.año) ||
        (fecha.año == fechaLimiteInferior.año && fecha.mes > fechaLimiteInferior.mes) ||
        (fecha.año == fechaLimiteInferior.año && fecha.mes == fechaLimiteInferior.mes && fecha.dia >= fechaLimiteInferior.dia) &&
        (fecha.año < fechaLimiteSuperior.año ||
         (fecha.año == fechaLimiteSuperior.año && fecha.mes < fechaLimiteSuperior.mes) ||
         (fecha.año == fechaLimiteSuperior.año && fecha.mes == fechaLimiteSuperior.mes && fecha.dia <= fechaLimiteSuperior.dia))) {
    } else {
        //si no cumple la condicion, se imprime la siguiente por pantalla.
        printf("Fecha incorrecta. Por favor, introduzca una fecha entre el %d/%d/%d y el %d/%d/%d.\n",
               fechaLimiteInferior.dia, fechaLimiteInferior.mes, fechaLimiteInferior.año,
               fechaLimiteSuperior.dia, fechaLimiteSuperior.mes, fechaLimiteSuperior.año);
        exit(EXIT_FAILURE);
    }
}



void intercambia(Data *fecha1, Data *fecha2){
    //Esta fucnion la creo por si se da el caso de que la segunda fecha introducida por el usuario es anteior a la primera
    if (fecha1->año > fecha2->año || (fecha1->año == fecha2->año && fecha1->mes > fecha2->mes) ||
        (fecha1->año == fecha2->año && fecha1->mes == fecha2->mes && fecha1->dia > fecha2->dia)) {
        //establezco la condicion para que se realice el cambio
        Data temp = *fecha1;
        *fecha1 = *fecha2;
        *fecha2 = temp;
    }
}

int DiasDelMes(int mes, int ano){//Funcion que en funcion de si el año es bisiesto o no le asigna a febrero 29 dias
    int diasMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)) {
        diasMes[1]=29;
    }
    return diasMes[mes-1];
}

int CalcularDistancia(Data d1, Data d2){
    //funcion que calcula la distancia entre dos fechas
    intercambia(&d1,&d2);
    int distancia = 0;
    while (d1.dia != d2.dia || d1.mes != d2.mes || d1.año != d2.año) {
        d1.dia++;
        if (d1.dia > DiasDelMes(d1.mes, d1.año)) {
            d1.dia = 1;
            d1.mes++;
            if (d1.mes > 12) {
                d1.mes = 1;
                d1.año++;
            }
        }
        distancia++;
    }
    return distancia+1;
    //devuelvo la distancia mas uno porque al probar el resto de funciones de no hacerlo asi no me incluye la ultima fecha
}

Station LeerDatosEstacion(const char* camino_archivo){//funcion encarga de leer y almacenar los datos de la ubicacion y nombre de la estacion
    Station datos;
    char* nombre1 = camino_archivo;
    char nombre[50];
    int i = 0;
    while (*nombre1 != '.' && *nombre1 != '\0') {
        //Esto que hago aqui, sirve para que me elimine la extension del nombre del archivo, o mejor dicho, cuando detecta el putno de la extension deja de escanear los caracteres.Si no hay extension cesa cuando termina la palabra.
        nombre[i] = *nombre1++;
        i++;
    }
    nombre[i] = '\0';
    strcpy(datos.nombre, nombre);//copio el nombre en la correspondiente estructura

    FILE* archivo = fopen(camino_archivo, "r");
    if (archivo == NULL) {
        printf("ERROR al abrir el archivo: %s\n", camino_archivo);
        exit(EXIT_FAILURE);
    }

    while (fgetc(archivo) != '\n');//salto la primera linea del archivo

    fscanf(archivo, "\"%*d/%*d/%*d\",\"%f\",\"%f\",\"%d\",\"%*f\",\"%*f\",\"%*f\",\"%*f\",\"%*f\",\"%*f\",\n",
           &datos.longitud, &datos.latitud, &datos.elevacion);
            //como estos datos no varian a lo largo del archivo, una manera eficiente es solo escanearlos un vez y asi ya quedan leidos
    fclose(archivo);

    return datos;
}


WeatherData* LeerDatosWeather(const char* camino_archivo){
    //funcion que devuelve todos los datos meteorologicos de una estacion
    FILE* archivo = fopen(camino_archivo, "r");
    if (archivo == NULL) {
        perror("ERROR al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    while (fgetc(archivo) != '\n');//salot la primera linea

    WeatherData* datos = (WeatherData*)malloc(sizeof(WeatherData));//reservo la memoria
    if (datos == NULL) {
        perror("Error al reservar memoria para WeatherData");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    int elementosLeidos = 0;

    while (fscanf(archivo, "\"%d/%d/%d\",\"%*f\",\"%*f\",\"%*d\",\"%f\",\"%f\",\"%f\",\"%f\",\"%f\",\"%f\",\n",
                  &datos[i].fecha.mes, &datos[i].fecha.dia, &datos[i].fecha.año,
                  &datos[i].MaxTemperature, &datos[i].MinTemperature, &datos[i].Precipitacion,
                  &datos[i].Wind, &datos[i].RelativeHumidity, &datos[i].Solar) == 9) {
        //creo un bucle para ir escanenaod todos los datos mientras se cumpla la condicion del bucle
        i++;
        elementosLeidos++;//esta variable la creo a modo de comprobacion, poruqe desconozco el motivo pero despues al usar el realloc al ponerle i me daba problemas

        datos = (WeatherData*)realloc(datos, (elementosLeidos + 1) * sizeof(WeatherData));//aumento la memoria reservada en funciond e cuantas veces se repitaa en bucle
        if (datos == NULL) {
            perror("Error al realojar memoria");
            exit(EXIT_FAILURE);
        }
    }

    fclose(archivo);
    return datos;
}


void free_WeatherData(WeatherData* weatherdata){
    //funcion para liberar la memoria de weatherdata
    free(weatherdata);
}

WeatherStation* LeerDatosWeatherStation(const char* camino_archivo){
    //Esta funcion la uso para juntar los datos devueltos por las dos anteriores
    if (camino_archivo == NULL) {
        printf("Error: Ruta del archivo incorrecta\n");
        exit(EXIT_FAILURE);
    }

    WeatherStation* datos = (WeatherStation*)malloc(sizeof(WeatherStation));//reservo la memoria
    if (datos == NULL) {
        perror("Error al reservar memoria para WeatherStation");
        exit(EXIT_FAILURE);
    }

    datos->estacion = LeerDatosEstacion(camino_archivo);//uso las funciones anteriores para guardas los datos en sus correspondientes campos
    datos->weatherdata = LeerDatosWeather(camino_archivo);
    return datos;
}

void free_Weatherstation(WeatherStation* weatherStation){
    //funcion que libera la memoria de una weatherstation
    free_WeatherData(weatherStation->weatherdata);
    free(weatherStation);
}

WeatherStation* CrearArrayWeatherStation(const char* camino_archivo[], int numero_archivos){
    //en esta funcion uso la anterior para que me lo haga con varias estaciones, or ello recibe un array de estaciones y el numero de ellas.
    int i = 0;
    WeatherStation* array_weatherstation = (WeatherStation*)malloc(numero_archivos * sizeof(WeatherStation));
    //Realizo la reserva de memoria, que sera el tamaño de weaherstation por el numero de etaciones que se introduzcan
    if (array_weatherstation == NULL) {
        printf("Error al reservar memoria para el array de WeatherStation\n");
        exit(EXIT_FAILURE);
    }
    for (i; i < numero_archivos; i++) {
        array_weatherstation[i] = *LeerDatosWeatherStation(camino_archivo[i]);//uso la funcion anteiror para que por cada iteracion del bucle me lea todos los dato de cada archivo que le pase
    }
    return array_weatherstation;
}
void ImprimirArrayWeatherStation(WeatherStation* array_weatherstation, int numero_estaciones){
        //funcion para imprimir todos los datos
       for (int i = 0; i < numero_estaciones; i++) {
        printf("Estación %d:\n", i + 1);
        printf("Nombre de la estación: %s\n", array_weatherstation[i].estacion.nombre);
        printf("Longitud: %f, Latitud: %f, Elevación: %d\n",
               array_weatherstation[i].estacion.longitud,
               array_weatherstation[i].estacion.latitud,
               array_weatherstation[i].estacion.elevacion);

        WeatherData* datos = array_weatherstation[i].weatherdata;
        for (int j = 0; j < 4018; j++) {
            printf("Fecha: %d/%d/%d\n", datos[j].fecha.mes, datos[j].fecha.dia, datos[j].fecha.año);
            printf("Temperatura máxima: %f\n", datos[j].MaxTemperature);
            printf("Temperatura mínima: %f\n", datos[j].MinTemperature);
            printf("Precipitación: %f\n", datos[j].Precipitacion);
            printf("Viento: %f\n", datos[j].Wind);
            printf("Humedad relativa: %f\n", datos[j].RelativeHumidity);
            printf("Radiación solar: %f\n", datos[j].Solar);
            printf("\n");
        }
        printf("----------------------------------------------\n");
    }
}

void free_Array_WeatherStation(WeatherStation* array_weatherStation, int numero_archivos){
    //funcion que libera la memoria reservada para el array de weatherstation
    int i=0;
    for (int i = 0; i < numero_archivos; i++) {
        free_Weatherstation(&array_weatherStation[i]);
    }
    free(array_weatherStation);
}

TemperaturasExtremas ObtenerTemperaturasExtremas(WeatherStation* array_weatherstation, int numero_archivos, Data d1, Data d2) {
    //funcion que me dara las temperaturas extremas de todas las que vaya a leer,y me dara en que estacion la registro y que dia
    intercambia(&d1,&d2);//hago uso de la funcion intercambia por si el usuario introudce la segunda fecha anterior a la primera
    int distancia = CalcularDistancia(d1, d2);//calculo la distancia

    int distanciaInicial;
    Data d = {1, 1, 2000};//le introuzco la primera fecha de todas las del archivo
    distanciaInicial = CalcularDistancia(d, d1);//Calculo su distancia

    ValidarFechaEnMargen(d1);//valido que las fechas que intoduce el usuario sean validas
    ValidarFechaEnMargen(d2);

    TemperaturasExtremas temperaturas_extremas;
    temperaturas_extremas.MaxTemperature = -100;
    //establezco las temperaturas que contiene la estructura con el objtivo de ir comparandolas, le inttoduzo estas temperaturas puesto que es imposible que no haya una temepratura maxima mayor a -100
    temperaturas_extremas.MinTemperature = 100;//hago lo mismo con la minima

    int i, j;
    for (i = 0; i < numero_archivos; i++){
        for (j = distanciaInicial; j < distanciaInicial + distancia-1; j++) {
            //uso distanciaInicial para que me empiece a registrar temperaturas desde la rpimera fecha introducida
            //le pongo distanciaInicial+distancia-1 debido a que si no le pongo el -1 se pasaria del rango de fechas que contiene el archvio en caso de introudcirle las fechas limite
            if (array_weatherstation[i].weatherdata[j].MaxTemperature > temperaturas_extremas.MaxTemperature) {
                //Esto se va a ejecutar siempre que la fecha maxima leida en la estacion i sea mayor que la almacenada en la estructura TemperaturesExtremas
                temperaturas_extremas.fechaMaxTemperature = array_weatherstation[i].weatherdata[j].fecha;
                temperaturas_extremas.MaxTemperature = array_weatherstation[i].weatherdata[j].MaxTemperature;
                strncpy(temperaturas_extremas.MaxNombre, array_weatherstation[i].estacion.nombre, sizeof(temperaturas_extremas.MaxNombre)-1);
                temperaturas_extremas.MaxNombre[sizeof(temperaturas_extremas.MaxNombre)-1] = '\0'; //aseguro que la cadena termina
            }
            if (array_weatherstation[i].weatherdata[j].MinTemperature < temperaturas_extremas.MinTemperature) {
                //hago lo mismo pero con las minimas
                temperaturas_extremas.fechaMinTemperature = array_weatherstation[i].weatherdata[j].fecha;
                temperaturas_extremas.MinTemperature = array_weatherstation[i].weatherdata[j].MinTemperature;
                strncpy(temperaturas_extremas.MinNombre, array_weatherstation[i].estacion.nombre, sizeof(temperaturas_extremas.MinNombre)-1);
                temperaturas_extremas.MinNombre[sizeof(temperaturas_extremas.MinNombre)-1] = '\0';
            }
        }
    }
    return temperaturas_extremas;
}

void ImprimirTemperaturasExtremas(TemperaturasExtremas temperaturas_extremas){
    //funcion para escribir los datos alamcenados en la estructura Temperaturas extremas
    printf("Estación donde se registró la máxima: %s\n", temperaturas_extremas.MaxNombre);
    printf("Temperatura Máxima: %f\n", temperaturas_extremas.MaxTemperature);
    printf("Fecha Máxima Extrema: %d/%d/%d\n", temperaturas_extremas.fechaMaxTemperature.dia, temperaturas_extremas.fechaMaxTemperature.mes, temperaturas_extremas.fechaMaxTemperature.año);
    printf("\n");
    printf("Estación donde se registró la mínima: %s\n", temperaturas_extremas.MinNombre);
    printf("Temperatura Mínima Extrema: %f\n", temperaturas_extremas.MinTemperature);
    printf("Fecha Mínima Extrema: %d/%d/%d\n", temperaturas_extremas.fechaMinTemperature.dia, temperaturas_extremas.fechaMinTemperature.mes, temperaturas_extremas.fechaMinTemperature.año);
}


TemperaturasMedias ObtenerTemperaturasMedias(WeatherStation* array_weatherstation, int numero_archivos, Data d1){
    //funcion que me va a hacer la media entre las temperaturas maximas de una fecha de todas las estaciones, y otra media con la minima
    float maxSum=0.0;
    float minSum=0.0;
    Data d={1,1,2000};
    int distancia= CalcularDistancia(d,d1);//calculo la distancia entre la fecha introducida y la del incio del archivo
    ValidarFechaEnMargen(d1);//compruebo que la fecha introducida es valida
    int i=0;
    TemperaturasMedias temperaturasMedias;
    for(i; i<numero_archivos; i++){
        maxSum += array_weatherstation[i].weatherdata[distancia].MaxTemperature;//sumo todas las maximas
        minSum += array_weatherstation[i].weatherdata[distancia].MinTemperature;//sumo todas las minimas
    }
    temperaturasMedias.Maxmedia=maxSum/(float)numero_archivos;//calculo la media
    temperaturasMedias.Minmedia=minSum/(float)numero_archivos;
    return temperaturasMedias;
}

void ImprimirTemperaturasMedias(TemperaturasMedias temperaturasMedias) {
    //funcion para imprimir las medias
    printf("Temperatura Media Máxima: %f\n", temperaturasMedias.Maxmedia);
    printf("Temperatura Media Mínima: %f\n", temperaturasMedias.Minmedia);
}
