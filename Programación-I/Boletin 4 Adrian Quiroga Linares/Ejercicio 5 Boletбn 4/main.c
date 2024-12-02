#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Autor: Adrián Quiroga Linares
//Data: 2/12/2023
//Versión:1
//Este programa ten de leer un arquivo pasado pola liña de comandos e que o lea incluso se carece de extension

//C:\Users\adria\Desktop\Exercicios Boletín 4 Adrian Quiroga Linares\Ejercicio 5 Boletín 4
//main.exe "Balon de oro.txt"
//main.exe "Frases Cuñado Cena Navideña"
//main.exe "Receta.csv"


typedef struct {
    //estructura que conten o nome e a extension do arquivo
    char nombre[256];
    char extension[10];
} nombre_completo;


void mostrar_contenido(nombre_completo *infoarchivo) {
    //funcion para mostrar o contido do arquivo
    char nombre[266];  // 256 (nombre) + 1 (punto) + 9 (extensión)
    char caracter;//uso esta variable para ler os caracteres do arquivo

    // copio o nome e no caso de que exista extension a agrego
    strncpy(nombre, infoarchivo->nombre, sizeof(nombre));
    if (strlen(infoarchivo->extension) > 0) {//comproba se a extension é maior a 0
        strcat(nombre, ".");//engade un punto ao final do nome
        strcat(nombre, infoarchivo->extension);//finalmente engade a extension
    }

    // abro o arquivo en modo lectura
    FILE *archivo = fopen(nombre, "r");

    //comporbacion de que foi aberto correctamente
    if (archivo == NULL) {
        printf("Dirección del archivo incorrecta o archivo no encontrado: %s\n", nombre);
    }

    //imprimo o contido do arquivo
    printf("Contenido del archivo %s:\n", nombre);
    while ((caracter = fgetc(archivo)) != EOF) {//bucle que se vai a exectura ata o final do arquivo
        putchar(caracter);
    }

    // pecho o arquivo
    fclose(archivo);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {//se argc non é dous non se pode levar a cabo unha correcta execucion
        printf("Uso: %s nombre_archivo\n", argv[0]);
        return -1;
    }

    // Obtener el nombre del archivo desde la línea de comandos
    char *nombre;
    nombre = argv[1];//conten o nome do arquivo proporcionado na liña de comandos
    char *punto;
    punto= strrchr(nombre, '.');//busca a ultima aparicion do punto e almacena a súa posicion

    // Crear una instancia de la estructura nombre_completo
    nombre_completo infoarchivo;

    if (punto != NULL) {
        // Copiar el nombre base del archivo sin la extensión
        strncpy(infoarchivo.nombre, nombre, punto - nombre);
        //copio a parte do nome do arquivo anterior ao punto no nome
        infoarchivo.nombre[punto - nombre] = '\0';
        //con esto aseguro que a cadea remate cun caracter nulo, posto que strncpy non garantiza que agregue automaticamente

        // Copiar la extensión del archivo
        strncpy(infoarchivo.extension, punto + 1, sizeof(infoarchivo.extension) - 1);
        //copio a parte da extension a partir do punto
        infoarchivo.extension[sizeof(infoarchivo.extension) - 1] = '\0';
        //aseguro que remate en caracter nulo
    } else {
        // se non atopa o punto no nome, copio todo o nome es establezo a extension como baleira
        strncpy(infoarchivo.nombre, nombre, sizeof(infoarchivo.nombre) - 1);
        //copio todo o nome do arquivo no compo nome da estructura
        infoarchivo.nombre[sizeof(infoarchivo.nombre) - 1] = '\0';

        infoarchivo.extension[0] = '\0';
        //unha vez mais aseguro que vai a rematar en caracter nulo
    }

    // Llamar a la función para mostrar el contenido del archivo
    mostrar_contenido(&infoarchivo);//chamo a funcion pasadolle a direccion da estructura como argumento
    free(nombre);
    free(punto);
    return 0;
}
