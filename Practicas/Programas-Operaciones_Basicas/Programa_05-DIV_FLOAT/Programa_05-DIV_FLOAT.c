#include <stdio.h>

int main(){
    // Declaracion de variables:
    int a;
    int b;
    float R; 

    // Ingreso de valores de variables:
    // A:
    printf("\nIngrese valor para A: ");
    scanf("%d",&a);
    // B:
    printf("\nIngrese valor para B: ");
    scanf("%d",&b);

    // Checkeo de denominador "B" distinto de 0:
    if(b != 0){
        // Operacion:
        R = (float)a/b;
        
        // Representacion de resultado:
        printf("\nEl resultado es: %2f\n", R);   // OJO el %f para las representaciones en (float).
    }else{
        printf("\n#### MATH_ERROR: No está definida la división por 0. ####\n");
    }

    // Terminacion del programa:
    return 0;
}