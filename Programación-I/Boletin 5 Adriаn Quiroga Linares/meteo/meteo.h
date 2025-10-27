// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#ifndef METEO_METEO_H
#define METEO_METEO_H

typedef struct{
    char nombre[50];
    float longitud;
    float latitud;
    int elevacion;
} Station;

typedef struct{
    int dia;
    int mes;
    int año;
} Data;

typedef struct{
    Data fecha;
    float MaxTemperature;
    float MinTemperature;
    float Precipitacion;
    float Wind;
    float RelativeHumidity;
    float Solar;
} WeatherData;

typedef struct{
    Station estacion;
    WeatherData* weatherdata;
} WeatherStation;

typedef struct{
    char MaxNombre[50];
    char MinNombre[50];
    Data fechaMaxTemperature;
    Data fechaMinTemperature;
    float MaxTemperature;
    float MinTemperature;
} TemperaturasExtremas;

typedef struct{
    float Maxmedia;
    float Minmedia;
} TemperaturasMedias;

/*Valida si una fecha está dentro del margen especificado (1/1/2000 - 31/12/2010)
 *Precondición: El parámetro fecha debe ser una estructura de tipo Data.
 * Postcondición:
 *   - Si la fecha está dentro del rango (1/1/2000 - 31/12/2010), la función no hace nada.
 *   - Si la fecha está fuera del rango, imprime un mensaje y termina el programa con un código de error.
 */
void ValidarFechaEnMargen(Data fecha);


/* Intercambia dos fechas si la primera es posterior a la segunda.
 * Precondicion: Los parámetros fecha1 y fecha2 deben ser punteros a estructuras de tipo Data.
 * Postcondicin: Si fecha1 es posterior a fecha2, las fechas se intercambian.
 */
void intercambia(Data *fecha1, Data *fecha2);

/* Devuelve el número de días en un mes específico de un año específico.
 * Precondicion: Los parámetros mes y año deben ser enteros que representen un mes (1-12) y un año.
 * Postcondicion: Devuelve el número de días en el mes especificado.
 */
int DiasDelMes(int mes, int ano);

/* Calcula la distancia en días entre dos fechas.
 * Precondición: Los parámetros d1 y d2 deben ser estructuras de tipo Data.
 * Postcondición: Devuelve la distancia en días entre las dos fechas.
 */
int CalcularDistancia(Data d1, Data d2);



/* Lee y retorna datos de una estación meteorológica desde un archivo.
 * Precondición: El parámetro camino_archivo debe ser una cadena de caracteres válida que represente la ruta de un archivo CSV.
 * Postcondición: Devuelve una estructura Station con los datos de la estación leídos desde el archivo.
 */
Station LeerDatosEstacion(const char* camino_archivo);

/* Lee y retorna datos meteorológicos desde un archivo.
 * Precondición: El parámetro camino_archivo debe ser una cadena de caracteres válida que represente la ruta de un archivo CSV.
 * Postcondición: Devuelve un puntero a un array de estructuras WeatherData con los datos meteorológicos leídos desde el archivo.
 */
WeatherData* LeerDatosWeather(const char* camino_archivo);

/* Lee y retorna datos de una estación meteorológica con sus datos meteorológicos desde un archivo.
 * Precondición: El parámetro camino_archivo debe ser una cadena de caracteres válida que represente la ruta de un archivo CSV.
 * Postcondición: Devuelve un puntero a una estructura WeatherStation con los datos de la estación y sus datos meteorológicos leídos desde el archivo.
 */
WeatherStation* LeerDatosWeatherStation(const char* camino_archivo);

/* Crea y retorna un array de estaciones meteorológicas con sus datos meteorológicos a partir de archivos.
 * Precondición: El parámetro camino_archivo debe ser un array de cadenas de caracteres válidas que representen rutas de archivos CSV, y numero_archivos debe ser el número de archivos.
 * Postcondición: Devuelve un puntero a un array de estructuras WeatherStation con los datos de las estaciones y sus datos meteorológicos leídos desde los archivos.
 */
WeatherStation* CrearArrayWeatherStation(const char* camino_archivo[], int numero_archivos);



/* Calcula y retorna las temperaturas extremas y sus fechas asociadas a partir de un array de estaciones meteorológicas.
 * Precondición: El parámetro array_weatherstation debe ser un puntero a un array de estructuras WeatherStation con datos válidos, numero_archivos debe ser el número de estaciones, y d1 y d2 deben ser estructuras de tipo Data.
 * Postcondición: Devuelve una estructura TemperaturasExtremas con las temperaturas extremas y sus fechas asociadas.
 */
TemperaturasExtremas ObtenerTemperaturasExtremas(WeatherStation* array_weatherstation, int numero_archivos, Data d1, Data d2);

/* Calcula y retorna las temperaturas medias a partir de un array de estaciones meteorológicas en una fecha específica.
 * Precondición: El parámetro array_weatherstation debe ser un puntero a un array de estructuras WeatherStation con datos válidos, numero_archivos debe ser el número de estaciones, y d1 debe ser una estructura de tipo Data.
 * Postcondición: Devuelve una estructura TemperaturasMedias con las temperaturas medias calculadas.
 */
TemperaturasMedias ObtenerTemperaturasMedias(WeatherStation* array_weatherstation, int numero_archivos, Data d1);



/* Imprime los datos de una estación meteorológica.
 * Precondición: El parámetro estacion debe ser una estructura de tipo Station con datos válidos.
 * Postcondición: Imprime los datos de la estación en la consola.
 */
void ImprimirDatosEstacion(Station estacion);

/* Imprime los datos meteorológicos.
 * Precondición: El parámetro datos debe ser un puntero a un array de estructuras WeatherData con datos válidos, y numero_datos debe ser el número de datos meteorológicos.
 * Postcondición: Imprime los datos meteorológicos en la consola.
 */
void ImprimirDatosWeather(WeatherData *datos, int numero_datos);

/* Imprime los datos de una estación meteorológica con sus datos meteorológicos.
 * Precondición: El parámetro datos debe ser una estructura de tipo WeatherStation con datos válidos.
 * Postcondición: Imprime los datos de la estación y sus datos meteorológicos en la consola.
 */
void ImprimirDatosWeatherStation(WeatherStation *datos);

/* Imprime un array de estaciones meteorológicas con sus datos meteorológicos.
 * Precondición: El parámetro array_datos debe ser un puntero a un array de estructuras WeatherStation con datos válidos, y numero_estaciones debe ser el número de estaciones.
 * Postcondición: Imprime el array de estaciones meteorológicas y sus datos meteorológicos en la consola.
 */
void ImprimirArrayWeatherStation(WeatherStation *array_datos, int numero_estaciones);

/* Imprime las temperaturas extremas.
 * Precondición: El parámetro temperaturas_extremas debe ser una estructura de tipo TemperaturasExtremas con datos válidos.
 * Postcondición: Imprime las temperaturas extremas y sus fechas asociadas en la consola.
 */
void ImprimirTemperaturasExtremas(TemperaturasExtremas temperaturas_extremas);

/* Imprime las temperaturas medias.
 * Precondición: El parámetro temperaturasMedias debe ser una estructura de tipo TemperaturasMedias con datos válidos.
 * Postcondición: Imprime las temperaturas medias en la consola.
 */
void ImprimirTemperaturasMedias(TemperaturasMedias temperaturasMedias);



/* Libera la memoria asignada a un array de datos meteorológicos.
 * Precondición: El parámetro weatherdata debe ser un puntero a un array de estructuras WeatherData con datos válidos.
 * Postcondición: Libera la memoria asignada al array de datos meteorológicos.
 */
void free_WeatherData(WeatherData* weatherdata);

/* Libera la memoria asignada a una estación meteorológica con sus datos meteorológicos.
 * Precondición: El parámetro weatherStation debe ser una estructura de tipo WeatherStation con datos válidos.
 * Postcondición: Libera la memoria asignada a la estación meteorológica y sus datos meteorológicos.
 */
void free_Weatherstation(WeatherStation* weatherStation);

/* Libera la memoria asignada a un array de estaciones meteorológicas con sus datos meteorológicos.
 * Precondición: El parámetro array_weatherStation debe ser un puntero a un array de estructuras WeatherStation con datos válidos, y numero_archivos debe ser el número de estaciones.
 * Postcondición: Libera la memoria asignada al array de estaciones meteorológicas y sus datos meteorológicos.
 */
void free_Array_WeatherStation(WeatherStation* array_weatherStation, int numero_archivos);

#endif //METEO_METEO_H
