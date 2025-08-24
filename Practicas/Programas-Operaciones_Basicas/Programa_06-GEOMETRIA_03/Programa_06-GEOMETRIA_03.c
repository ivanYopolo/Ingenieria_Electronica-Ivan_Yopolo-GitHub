/* 
### PROGRAMA DE GEOMETRIA ###

Programa que realice las siguientes
operaciones con datos de entrada:

3) Calcular área del triángulo.
*/

#include <stdio.h>

int main(){
    // Datos del triángulo:
        // Lados + altura:
    int b = 0; // Base.
    int h = 0; // Altura.
    float a = 0; // Área.

    // Ingreso de datos:
    printf("\nIngrese base y altura: \n");
    printf("\nBase: ");
    scanf("%d", &b);
    if(b < 0){
        printf("\n### MATH_ERROR: Base no puede ser negativa.\n");
        return 0;
    }

    printf("\nAltura: ");
    scanf("%d", &h);
    if(h < 0){
        printf("\n### MATH_ERROR: Altura no puede ser negativa.\n");
        return 0;
    }

    // Cálculo del área:
    a = 0.5*(float)(b*h);
    printf("\nEl área es de: %f\n", a);

    return 0;
}