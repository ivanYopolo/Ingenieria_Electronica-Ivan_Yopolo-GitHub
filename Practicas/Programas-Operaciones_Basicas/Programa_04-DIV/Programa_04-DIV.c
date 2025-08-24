#include <stdio.h>

int main(){
// Declaracion de variables:
int a;
int b;

// Ingreso de valores de variables:
// A:
printf("\nIngrese valor para A:");
scanf(" %d",&a);
// B:
printf("\nIngrese valor para B:");
scanf(" %d",&b);

// Resultado.
int R; 

// Operacion:
R = a/b;

// Representacion de resultado:
printf("\nEl resultado es: %d\n", R);

// Terminacion del programa:
return 0;
}