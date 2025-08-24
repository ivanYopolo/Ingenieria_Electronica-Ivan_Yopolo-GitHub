/* 
### PROGRAMA DE GEOMETRIA ###

Programa que realice las siguientes
operaciones con datos de entrada:

2) Identificar tipo de triángulo.
*/

#include <stdio.h>

int main(){
    printf("\n### TRIANGLE_PROGRAM-TRIANGLE_TYPE ###\n");
    // Datos del triángulo:
    int ladoA = 0;
    int ladoB = 0;
    int ladoC = 0;

    // Ingresado de lados:
    printf("\nIntroduzca los 3 lados en secuencia: \n");

    // Lado A:
    printf("\nLado A: ");
    scanf("%d", &ladoA);

    if(ladoA < 0){
        printf("\n### MATH_ERROR: Longitud no puede ser negativa ###\n");
        return 0;
    }

    // Lado B:
    printf("\nLado B: ");
    scanf("%d", &ladoB);

    if(ladoB < 0){
        printf("\n### MATH_ERROR: Longitud no puede ser negativa ###\n");
        return 0;
    }
    
    // Lado C:
    printf("\nLado C: ");
    scanf("%d", &ladoC);

    if(ladoC < 0){
        printf("\n### MATH_ERROR: Longitud no puede ser negativa ###\n");
        return 0;
    }

    
    // Identificación del triángulo:

    // Escaleno:
    if(ladoA != ladoB){
        if(ladoB != ladoC){
            printf("\nTriángulo Escaleno.\n");
        }
    }

    // Isóceles:
    if(ladoA == ladoB){
        if(ladoA != ladoC){
            printf("\nTriángulo Isóceles.\n");
        }
    }
    if(ladoC == ladoB){
        if(ladoA != ladoB){
            printf("\nTriángulo Isóceles.\n");
        }
    }
    if(ladoA == ladoC){
        if(ladoA != ladoB){
            printf("\nTriángulo Isóceles.\n");
        }
    }

    // Equilátero:
    if(ladoA == ladoB){
       if(ladoB == ladoC){
        printf("\nTriángulo Equilátero\n");
       } 
    }

    // Rectángulo:
    int a2 = ladoA * ladoA;
    int b2 = ladoB * ladoB;
    int c2 = ladoC * ladoC;
    if(a2 == (b2 + c2)){
        printf("\nTriángulo rectángulo\n");
    }
    if(b2 == (a2 + c2)){
        printf("\nTriángulo rectángulo\n");
    }
    if(c2 == (b2 + a2)){
        printf("\nTriángulo rectángulo\n");
    }

    return 0;
}