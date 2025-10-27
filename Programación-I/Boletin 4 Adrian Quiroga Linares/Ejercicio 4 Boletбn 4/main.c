// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

//Autor: Adrián Quiroga Linares
//Data: 1/12/2023
//Versión:1
//Este programa ten como obxectivo motrar todos os datos dun arquivo entre dúas datas introducidas polo usuario
#include <stdio.h>
#include <stdlib.h>

typedef struct {//estructura que alamcenará a data
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {//estructura anidada que conten todos os datos do arquivo
    Data data;
    float temperaturamax;
    float temperaturamin;
    float precipitacion;
    float vento;
    float humidade;
    float solar;
} WeatherData;

Data Ler() {//funcion para ler as datas introducidas polo usuario
    Data fecha;
    printf("Introduce o día:\n");
    scanf("%d", &fecha.dia);
    printf("Introduce o mes:\n");
    scanf("%d", &fecha.mes);
    printf("Introduce o ano:\n");
    scanf("%d", &fecha.ano);

    if( fecha.ano>2010 || fecha.ano<2000){ //uso esto por se o usuario introduce unha data fora do rango.
        printf("A data debe estar entre o rango 1/1/2000 e 12/31/2010");
    }
    if(fecha.mes>12 || fecha.dia>31){ //uso esto por se a data introducida non ten sentido
        printf("Introduce una fecha válida");
    }
    return fecha;
}


int Dias_por_mes(int mes, int ano) {//funcion para determinar os dias por mes en funcion de se o ano é bisiesto ou non
    int diasMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)) {//condicion para que sexa bisiesto
        diasMes[1] = 29;
    }
    return diasMes[mes - 1];
}

int Calcular_distancia(Data d1, Data d2) {//funcion que calcula a distancia entre as dúas datas
    int distancia = 0;
    while (d1.dia != d2.dia || d1.mes != d2.mes || d1.ano != d2.ano) {
        d1.dia++;
        if (d1.dia > Dias_por_mes(d1.mes, d1.ano)) {
            d1.dia = 1;
            d1.mes++;

            if (d1.mes > 12) {
                d1.mes = 1;
                d1.ano++;
            }
        }
        distancia++;
    }
    return distancia;
}

WeatherData* lectura(FILE* archivo, Data* d1, Data* d2, int* totalDatos) {//funcion que devolve un punteiro ao vector de estructuras
    int i = 0;
    int distancia1;//distacnia empregada para colocar o cursor
    int distancia2;//distancia entre as dúas datas
    Data wd = {1, 1, 2000};//primeira data do arquivo
    distancia1 = Calcular_distancia(wd, *d1);
    //Calcula a distancia entre a primeira data do arquivo e o valor almcenado na direccion de memoria correspondente á primeira data
    distancia2 = Calcular_distancia(*d1, *d2);
    //calcula a distancia entre as datas
    *totalDatos = distancia2;//establezco a cantidade total de datos que debe devolver
    WeatherData* datos = (WeatherData*)malloc(sizeof(WeatherData) * distancia2);//Fago a reserva de memoria
    fseek(archivo, sizeof(WeatherData) * distancia1, SEEK_SET);//coloco a cursor na primeira data introducida polo usuario

    for (i; i < distancia2; i++) {//bucle para ler os datos
        fread(&datos[i], sizeof(WeatherData), 1, archivo);
    }
    return datos;
}

void imprimirDatos(WeatherData* datos, int totalDatos) {//funcion para imprimir todos os datos
    printf("Datos entre las fechas:\n");
    for (int i = 0; i < totalDatos; i++) {
        printf("Fecha: %d/%d/%d\n", datos[i].data.dia, datos[i].data.mes, datos[i].data.ano);
        printf("Temperatura Máxima: %f\n", datos[i].temperaturamax);
        printf("Temperatura Mínima: %f\n", datos[i].temperaturamin);
        printf("Precipitación: %f\n", datos[i].precipitacion);
        printf("Viento: %f\n", datos[i].vento);
        printf("Humedad Relativa: %f\n", datos[i].humidade);
        printf("Solar: %f\n", datos[i].solar);
        printf("\n");
    }
}

int main() {
    FILE* archivo;
    Data d1;
    Data d2;
    WeatherData* datos;
    int totalDatos;
    archivo = fopen("weatherdata-420-72.dat", "rb");//abro o arquivo en modo lectura binaria
    if (archivo == NULL) {//Fago a comprobacion de que a direccion é correcta
        printf("A dirección do arquivo é incorrecta");
        return -1;
    }
    printf("Introduce a primeira data:\n");
    d1 = Ler();
    printf("Introduce a segunda data:\n");
    d2 = Ler();

    datos = lectura(archivo, &d1, &d2, &totalDatos);//chamo á funcion e pasolle as direccions correspondentes
    imprimirDatos(datos, totalDatos);//chamo á funcion imprimir
    
    free(datos);//libero a memoria
    fclose(archivo);
    return 0;
}
