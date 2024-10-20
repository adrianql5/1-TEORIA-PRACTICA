#include <stdlib.h>
#include <stdio.h>

void secuencial(int arr[], int n, int x){
    int i=0;
    while(arr[i]!=x && i<n){
        i++;
    }
    if(arr[i]==x) printf("%d",arr[i]);
}

void centinela(int arr[], int n, int x){
    int i=0;
    arr[n-1]=x;
    while(arr[i]!=x){
       i++;
    }
    printf("%d",arr[i]);
}

void dicotomia(int arr[], int n, int x){
    int inicio, final, mitad;
    inicio=0;
    final=n-1;
    mitad=(inicio+final)/2;
    while(arr[mitad]!=x && inicio<final){
        if(arr[mitad]<x){
            final=mitad-1;
        }
        else{
            inicio=mitad+1;
        }
        mitad=(inicio+final)/2;

    }
    printf("%d",arr[mitad]);

}