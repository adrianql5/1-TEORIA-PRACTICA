/*
 * PROGRAMA PARA CALCULAR LA RAÍZ CUADRADA Y EL MÁXIMO COMÚN DIVISOR DE DOS NÚMEROS ENTEROS
 * PEDIDOS AL USUARIO/A POR TECLADO.
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE VS CODE. 
 * EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES. DOCUMENTAR LAS CORRECCIONES 
 * INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 * 
 * PRUEBAS: USAR LOS SIGUIENTES CASOS PASANDOLOS TANTO COMO ARGUMENTOS COMO DEJANDO QUE EL PROGRAMA PIDA LOS VALORES
 * 10 2 (sqrt=3.162278, gcd=2)
 * 2 10 (sqrt=1.414214, gcd=2)
 * 49 7 (sqrt=7., gcd=7)
 * -5 1 (sqrt no existe por ser negativo, gcd=1)
 * -5 -3 (sqrt no existe por ser negativo, gcd=1)
 * 3 0  (sqrt=1.732051, gcd=3)
 * 0 10 (sqrt=0.000977, gcd=10) // La raíz cuadrada de 0 es 0, pero el método de Newton es un método estimado. Podéis comprobarlo jugando con el parámetro margen
 * 0 0 (sqrt=0.000977, gcd=0)
 */

/* a) Corregir los errores comentando la línea incorrecta y poniendo la incorrecta a continuación
 * b) Fija un breakpoint e inicia la ejecución en modo depuración ¿Qué sucede al ejecutar paso a paso
 *    (botón “Step into” [F11]) la sentencia donde se invoca la función sqrt()?
 *    RESPy muestra pasoUESTA: Que abre el archivo sqrt.c  a paso que está realizando la función, cuando la funcion absoluto es llamada tambien muestra los valores que toman las variables, posteriormente regresa a main.c.
 * 
 * c) Al llegar a la función sqrt(), utiliza el botón “STEP OVER” [F10]  en  lugar  del  botón  “Step into” [F11]
 *   ¿Qué  diferencias observas frente a la ejecución del apartado b?
 *   RESPUESTA: La diferencia es que al realizar el step over no muestra los pasos que lleva acabo la función llamada en esa línea, porque se da por hecho que el error que busco no se encuentra ahí una vez ha sido corregido.
 * 
 * d) Repite la ejecución en modo depuración visualizando todas las variables. 
 *    Indica qué sucede con la ventana de variables cuando el flujo del programa continúa DENTRO de la función: Nos indica los valores actuales que toman las variables locales.
 *    Justifica la información que aparece en la solapa "Call Stack"
 *    RESPUESTA:Call Stack está mostrando un historial de llamadas a funciones, indicando cual es la función actual activa y las anteriores llamadas a funciones, lo que ayuda a  realizar un seguimiento del flujo del programa.
 * 
 * */


#include <stdio.h>
#include <stdlib.h>
#include "operaciones.h"

int main(int argc, char** argv) {

    int a, b;
    float s;
    float g;
    
    //if (argc == 0){
    if (argc==1){
        printf("Introduce dos números enteros: ");
        //scanf("%f%d", a, &b);
        scanf("%d %d", &a,&b);
    } else {
        //a = argv[0];
        a=atoi(argv[1]);
        //b = argv[1];
        b=atoi(argv[2]);
    }
    
    //if (a > 0){
    if (a >=0){
        s = sqrt(a);
        printf("Raíz cuadrada(%d) = %f\n", a, s);
    }else{
        printf("Error raíz: el parámetro (%d) no es un entero positivo\n", a);
    }
        
    g = gcd(a, b);
    //printf("Máximo común divisor(%f,%d) = %f\n", a, b, g);
    printf("Máximo común divisor (%d,%d) = %f\n",a,b,g);
    
    return (EXIT_SUCCESS);
}

