/* 
### PROGRAMA DE GEOMETRIA ###

Programa que realice las siguientes
operaciones con datos de entrada:

1) Calcular perímetro.
*/

#include <stdio.h>

int main(){
    printf("\n### TRIANGLE_PROGRAM-PERIMETRE ###\n");

    // Datos del triángulo (lados):
    int ladoA = 0;
    int ladoB = 0;
    int ladoC = 0;
    unsigned int perimetro = 0;

    // Ingreso de datos:
    printf("\nIngrese longitud de los 3 lados en secuencia: \n");

    // LADO_A:
    printf("\nLado A: ");
    scanf("%d", &ladoA);

    // Checkeo de datos correctos:
    if(ladoA < 0){
        printf("\n### MATH_ERROR: Longitud no puede ser negativa ###\n");
        return 0;
    }
    
    // LADO_B:
    printf("\nLado B: ");
    scanf("%d", &ladoB);

    // Checkeo de datos correctos:
    if(ladoB < 0){
        printf("\n### MATH_ERROR: Longitud no puede ser negativa ###\n");
        return 0;
    }
    
    // LADO_C:
    printf("\nLado C: ");
    scanf("%d", &ladoC);

    // Checkeo de datos correctos:
    if(ladoC < 0){
        printf("\n### MATH_ERROR: Longitud no puede ser negativa ###\n");
        return 0;
    }
    

    // Cálculo perímetro:
    perimetro = ladoA + ladoB + ladoC;
    printf("\nEl perímetro es de: %d\n", perimetro);
    
    return 1;
}