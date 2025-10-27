/*
 * PROGRAMA PARA REALIZAR OPERACIONES BÁSICAS CON UNA MATRIZ DINÁMICA
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE NETBEANS. EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES
 * DOCUMENTAR LAS CORRECCIONES INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 *
 * PRUEBAS:
 * - número de filas o columnas: 0
 * - acceder a un dato con índices negativos
 * - verificar todas las operaciones, para matrices pequeñas (2,3 filas/cols)
 *      - número de filas y columnas distintos en las dos matrices
 *      - número de filas igual y de columnas distinto
 *      - número de columnas igual y de filas distinto
 */

#include "include/matriz.h"
int main(int argc, char** argv) {
    //int i, k, f, c;
    int f,c;
    float valor;
    //matriz *a = 0, *b = 0, *aux = 0;
    matriz *a=NULL, *b=NULL, *aux=NULL; //
    char opcion, resp;

    do {
        printf("---------------------Libreria matrices---------------------\n\n");
        printf("1-Crear matrices\n");
        printf("2-Asignar elementos\n");
        printf("3-Obtener elemento\n");
        printf("4-Imprimir matrices\n");
        printf("5-Sumar matrices\n");
        printf("6-Producto de matrices\n");
        printf("7-Eliminar matrices\n");
        printf("0-Salir\n");
        printf("Opcion: ");
        //scanf(" %c", opcion);
        scanf(" %c", &opcion);

        switch (opcion) {
            case '0':
                destruirMatriz(a);//faltaba liberar la memoria en caso de desear salir del programa
                destruirMatriz(b);
                destruirMatriz(aux);
                printf("Saliendo del programa\n");
                break;
            case '1':
                destruirMatriz(a);
                a=NULL;
                destruirMatriz(b);
                b=NULL;
                destruirMatriz(aux);
                aux=NULL;
                printf("Introduzca el numero de filas de la matriz 'a': ");
                //scanf("%f", &f);
                scanf("%d",&f);
                printf("Introduzca el numero de columnas de la matriz 'a': ");
                scanf("%d", &c);
                a = crearMatriz(f, c);

                printf("Introduzca el numero de filas de la matriz 'b': ");
                //scanf("%f", &f);
                scanf("%d",&f);
                printf("Introduzca el numero de columnas de la matriz 'b': ");
                scanf("%d", &c);
                b = crearMatriz(f, c);
                break;
            case '2':
                if (a!=NULL){
                    if(a->datos!=NULL) free(a->datos);
                    printf("Matriz A\n");
                    for (f = 0; f < a->filas; f++)
                        for (c = 0; c < a->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            asignarElemento(f, c, valor, a);
                        }

                }
                else{
                    printf("Debes definir la matriz a para asignarle elementos\n");
                }
                if (b!=NULL){
                    if(a->datos!=NULL) free(a->datos);
                    printf("Matriz B\n");
                    for (f = 0; f < b->filas; f++)
                        for (c = 0; c < b->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            //asignarElemento(f, c, valor, a);
                            asignarElemento(f,c,valor,b);
                        }
                }
                else{
                    //printf ("Primero debes definir las matrices\n")                   
                    printf("Debes definir la matriz b para asignarle elementos\n");
                }             
                break;
            case '3':
                do {
                    printf("De que matriz quieres ver un elemento? (a/b): ");
                    scanf(" %c", &resp);
                } while (resp != 'a' && resp != 'b');
                if ((resp=='a') & (a==NULL)){
                   printf("Debes definir la matriz a para obtener sus elementos\n"); 
                   break;
                } 
                if((resp=='b') & (b==NULL)){
                   printf("Debes definir la matriz b para obtener sus elementos\n");
                   break; 
                }
                printf("Introduce fila y columna (fila columna): ");
                scanf("%d %d", &f, &c);
                if (resp == 'a') {
                    //valor = obtenerElemento(f, c, b);
                    valor = obtenerElemento(f-1,c-1,a);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                } else if (resp == 'b') {
                    //valor = obtenerElemento(f, c, a);
                    valor = obtenerElemento(f-1,c-1 ,b);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                }
                break;
            case '4':
                printf("Matriz A\n");
                imprimirMatriz(a);
                printf("Matriz B\n");
                imprimirMatriz(b);
                break;
            case '5':
                aux = suma(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                aux=NULL;
                break;
            case '6':
                aux = producto(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                aux=NULL;
                destruirMatriz(aux);
                break;
            case '7':
                destruirMatriz(a);
                a=NULL;//lo hago para que apunte a NULL
                destruirMatriz(b);
                b=NULL;
                destruirMatriz(aux);
                aux=NULL;
                printf("Matrices eliminadas...\n");
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while (opcion != '0');
    return (EXIT_SUCCESS);
}
