//Autor: Adrián Quiroga Linares
// Data: 1 de decemrbro de 2023
//Versión:1
//Este programa busca informacion dun arquivo bianrio, ao introudcirlle unha data devolvera os valores correspondetes a ela, e posteriormente ao introducir duas datas devolve a media das precipitacions entre elas, a diferencia do Boletin anterior os valores pasanse ás funcións por referencia.



#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct{
    //creo unha estructura para almacenar o día, mes e ano.
    int dia;
    int mes;
    int ano;
}Data;

typedef struct{
    //creo unha estructura anidada que inclúe os parámetros da data, maxima temperatura, minima temperatura, precipitacion, venta, humidade, solar
    Data data;
    float temperaturamax;
    float temperaturamin;
    float precipitacion;
    float vento;
    float humidade;
    float solar;
}WeatherData;

Data Ler() {
    //creo unha funcion de tipo Data encargada de almacenar os datos que introduce o usuario
    Data fechas;
    printf("Introduce o dia: ");
    scanf("%d", &fechas.dia);
    printf("Introduce o mes: ");
    scanf("%d", &fechas.mes);
    printf("Introduce o ano: ");
    scanf("%d", &fechas.ano);
    if( fechas.ano>2010 || fechas.ano<2000){ //uso esto por se o usuario introduce unha data fora do rango.
        printf("A data debe estar entre o rango 1/1/2000 e 12/31/2010");
    }
    if(fechas.mes>12 || fechas.dia>31){ //uso esto por se a data introducida non ten sentido
        printf("Introduce una fecha válida");
    }
    return fechas;
}

int diasDoMes(int mes, int ano) {
    //esta funcion devolve o numero de dias nun mes especifico dado un ano, se é bisiesto, febrero pasa a etr 29 días
    int diasMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //defino un vector que conten os dias correspondentes a cada mes
    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)) { //condicion para que un ano sexa bisiesto
        diasMes[1]=29;
    }
    return diasMes[mes-1];
    //emprego o -1 porque se o usuario introduce xaneiro (mes1), quero que devolva o valor correspondente ao primer elemento do vector(indice 0)
}
int CalcularDistancia(Data d1, Data d2) {
    // esta función é a encargada de calcular a distancia entre dúas datas
    int distancia = 0;
    while (d1.dia != d2.dia || d1.mes != d2.mes || d1.ano != d2.ano) {
        // bucle que se vai executar ata que as dúas datas coincidan
        d1.dia++; // Incremento os días da data 1
        if (d1.dia > diasDoMes(d1.mes, d1.ano)) {
            // se o número de días é maior á cantidade de días do mes en función do ano no que este, pasa a incrementarse o valor do mes
            d1.dia = 1;
            d1.mes++;
            if (d1.mes > 12) {
                // Seguindo a lóxica anterior, se a cantidade de meses pasa os 12, incrementase o ano e así sucesivamente
                d1.mes = 1;
                d1.ano++;
            }
        }
        distancia++; // cada vez que se executa o bucle, a distancia vai ser incrementada nun día
    }
    return distancia; // devolve a distancia total entre as dúas datas
}

WeatherData* Consulta_por_data(FILE* archivo, Data* d) {
    // nesta función de tipo WeatherData, busco a posicion da data introducida polo usuario no arquivo. Cando coinciden, devolve os datos desa fila
    WeatherData* wd;
    wd=(WeatherData*)malloc(sizeof(WeatherData));
    //creo unha variable tipo punteiro weatherdata que me devolvera ao final da funcion os valores correspondens á data.
    // Para esto é necesario realizar unha reserva de memoria empregando malloc.

    Data wd2 = {1,1,2000}; // isto é creado posto que calcula a distancia entre a primeira data de todas do arquivo e a data introducida
    int distancia;
    distancia= CalcularDistancia(wd2, *d); // Chamo a función anterior para obter a distancia entre estas dúas datas

    fseek(archivo, (long) sizeof(WeatherData)*(distancia), SEEK_SET);
    // emprego fseek para buscar no arquivo binario a data. O cursor deberá moverse o tamaño total da estrutura multiplicado pola distancia das datas. Como a primeira data está no inicio do documento emprego SEEK_SET para que o cursor se coloque ao principio.
    fread(wd, sizeof(WeatherData), 1, archivo);
    // emprego fread para simplemente ler os datos e gardalos na estrutura, indicándolle o tamaño, que será o de WeatherData, tendo que facelo unha vez, sacando a información do arquivo
    return wd;
}

float Consulta_precip_media(FILE* archivo, Data* d1, Data* d2) {//puntero tipo data en cual toma por referencia la direccion de memoria de d1 y d2
    // o obxectivo principal é calcular a media entre os valores da precipitación de todos os días que se atopen entre dúas datas
    int i=0;
    int distancia;
    distancia=CalcularDistancia( *d1, *d2); // con isto calculo a distancia entre as dúas datas, chamando ao svalores contidos na direccion de memoria
    float media;
    float suma = 0;
    Data wd2= {1,1,2000};
    WeatherData* vector;
    vector=(WeatherData*)malloc(sizeof(WeatherData) * distancia);
    //creo un vector tipo punteiro weatehrdata, e lle reservo a memoria necesaria
    int distancia1;
    distancia1= CalcularDistancia(wd2,*d1); // emprego isto para saber en que posición colocar o cursor do fseek

    fseek(archivo, (long) sizeof(WeatherData)*(distancia1), SEEK_SET);
    // ao igual que antes uso o fseek para colocar o cursor no inicio do arquivo e que se desprace ata a posición da primeira data
    for(i; i<distancia; i++) {
        // Creo un bucle que se executará mentres o índice sexa menor que a distancia
        fread(&vector[i], sizeof(WeatherData), 1, archivo);
        // emprego o fread para que lea todos os datos entre as dúas datas do arquivo
        suma += vector[i].precipitacion;
        // a suma é o equivalente á suma do valor que ten a precipitación sucesivamente, dende a primeira data ata a última
    }
    media=suma/distancia;
    return media;
}


void imprimir(WeatherData wd){
    //O obxectivo desta función é basicamente imprimir todos os datos
    printf("Fecha: %d/%d/%d\n", wd.data.dia,wd.data.mes, wd.data.ano);
    printf("Temperatura Máxima: %f\n", wd.temperaturamax);
    printf("Temperatura Mínima: %f\n", wd.temperaturamin);
    printf("Precipitación: %f\n", wd.precipitacion);
    printf("Vento: %f\n", wd.vento);
    printf("Humidade Relativa: %f\n", wd.humidade);
    printf("Solar: %f\n", wd.solar);
}

int main(){
    WeatherData* datos;
    float media;
    Data fecha1;
    Data fecha2;
    Data fecha3;
    FILE*archivo;
    archivo=fopen("weatherdata-420-72.dat","rb");//abro o arquivo usando o modo de lectura binaria
    if(archivo==NULL){
        //fago a comprobacion de que a dirección é correcta
        printf("A dirección do arquivo é incorrecta\n");
        return -1;
    }
    printf("Intoduce a data da cal queres saber os datos :\n");
    fecha1 = Ler();
    //garda os datos da primeira data que introduce o usuario

    datos = Consulta_por_data(archivo,&fecha1);//devuleve un puntero de tipo data cuyo valor es guradado en la variable tipo datos, pongo &fecha porque es la direccion de memoria del dato
    //devolve os datos correspondentes á data introducida


    imprimir(*datos);
    //imprime todos os datos
    printf("Introduce a primeira data, despois introduce unha data posterior a esta, e obterás a precipitacion media entre elas:\n");
    fecha2=Ler();
    //garda os valores da primeira data
    printf("Introduce a segunda data\n");
    fecha3=Ler();
    //garda os valores da segunda data
    media=Consulta_precip_media(archivo, &fecha2, &fecha3);
    //Realiza o valor medio entre as precipitacions que hay entre as duas datas
    printf("A precipitación media é: %f \n",media);//imprime a media

    fclose(archivo);
    free(datos);
    return 1;

}
