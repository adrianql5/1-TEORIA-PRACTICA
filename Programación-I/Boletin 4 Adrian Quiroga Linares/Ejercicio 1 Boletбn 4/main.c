//Autor: Adrián Quiroga Linares
//Data: 28/11/2023
//Versión:1
//Este programa ten o obxectivo de amosar as direccion de memoria dos diferentes tipos, amosando tamen que sucede cando se icnrementa en 1 a súa dirección de memoria



#include <stdio.h>

int main() {
    int x=10;
    float y=6.987498764;
    char z='a';
    printf("Dirección de memoria do enteiro é: %p\n",&x);
    printf("Dirección de memoria do enteiro incrementada en 1 é: %p\n",&x+1);//Ao sumarlle 1 a direccion de memoria aumenta en 4 bytes
    printf("Dirección de memoria do float é: %p\n",&y);
    printf("Dirección de memoria do float incrementada en 1 é: %p\n",&y+1);//Ao sumarlle 1 a direccion de memoria aumenta en 4 bytes
    printf("Dirección de memoria do char é: %p\n",&z);
    printf("Dirección de memoria do char incrementada en 1 é: %p\n",&z+1);//Ao sumarlle 1 a direccion de memoria aumenta nun byte
    //Non é posible distinguir o tipo de dato segundo o enderezo
    return 0;
}
