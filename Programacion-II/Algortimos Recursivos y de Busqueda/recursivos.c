#include <stdio.h>

int palindromo(char* arr, int n){
    if(n>=2){
        if(arr[0]==arr[n-1]) palindromo(arr+1,n-2);
        else return 0;
    }
    return 1;
}

int exponente(int b, int e){
    if(b==0 && e==0){
        printf("Error");
        return -1;
    }
    else if(b==0) return 0;
    else if(b==1) return 1;
    else if(e==0) return 0;
    else if(e==1) return b;

    else return b*exponente(b,e-1);
}

int planeta( int n){
    if(n==1) return 0.5;
    else if(n==2) return 0.7;
    else return 2*planeta(n-1)-0.4;
}

int mcd(int x, int y){
    if(x%y==0) return y;
    else return mcd(y, x%y);
}

int sum(int x){
    if(x<10) return x;
    else return x%10+sum(x/10);
}

int raiz(int x){
    if(x<10) return x;
    else return raiz(x%10 +raiz(x/10));
}

int pascal(int n, int k){
    if(k==0) return 1;
    else if(k==n) return 1;
    else return (pascal(n-1, k-1)+ pascal(n-1,k));
}

char inverso(char arr[], int inicio, int final){
    
    if(inicio>=final){
        return arr;
    }
    char temp=arr[final-1];
    arr[final-1]=arr[inicio];
    arr[inicio]=temp;
    
    return inverso(arr,inicio+1,final-1);
}

int main(){
    char cadena[]="HOHA";
    inverso(cadena,0,4);
    printf("%s",cadena);
}
