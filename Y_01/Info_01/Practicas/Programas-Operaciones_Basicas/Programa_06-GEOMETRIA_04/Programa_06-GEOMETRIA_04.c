/* 
### PROGRAMA DE GEOMETRIA ###

Programa que realice las siguientes
operaciones con datos de entrada:

4) Verificar que sea un triángulo.
ladoA + ladoB > ladoC
*/

#include <stdio.h>

int main(){
    // Datos del triángulo:
        // Lados + altura:
    int a = 0;
    int b = 0;
    int c = 0;
    int ver1 = 0;
    int ver2 = 0;
    int ver3 = 0;


    // Ingreso de datos:

    // A:
    printf("\nIngresar lado A: ");
    scanf("%d", &a);

    if(a < 0){
        printf("\n### MATH_ERROR: Longitud no puede ser negativa ###\n");
        return 0;
    }

    // B:
    printf("\nIngresar lado B: ");
    scanf("%d", &b);

    if(b < 0){
        printf("\n### MATH_ERROR: Longitud no puede ser negativa ###\n");
        return 0;
    }

    // C:
    printf("\nIngresar lado C: ");
    scanf("%d", &c);

    if(c < 0){
        printf("\n### MATH_ERROR: Longitud no puede ser negativa ###\n");
        return 0;
    }

    // Verificación del triángulo:
    ver1 = a+b;
    ver2 = a+c;
    ver3 = c+b;
    
    if(ver1 > c){
        printf("\nEs un triángulo.\n");
        return 0;
    }
    if(ver2 > b){
        printf("\nEs un triángulo.\n");
        return 0;
    }
    if(ver3 > a){
        printf("\nEs un triángulo.\n");
        return 0;
    }
    
    printf("\nNo es un triángulo.\n");
    return 0;
}