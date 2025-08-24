#include <stdio.h>
#include <stdlib.h>

/*
	Escribir función que reciba como parámetros un puntero a una secuencia de
	doubles y la cant. de elementos de la secuencia (ARRAY). Luego, devuelva
	el máximo valor contenido de la misma.
*/

// #define tamArray 5

// void printArrayMAX(double *arrayDouble, int capacidadDouble);
void printArrayMAX(double arrayDouble[], int capacidadDouble);

void main(){
	// Tamaño del array de Doubles.
	int tamDouble = 0;
	
	system("clear");
	
	printf("\nIngrese el tamaño del array:   ");
	
	scanf("%d", &tamDouble);
	
	// Array de Doubles X (sin inicializar).
	double arrayDouble[tamDouble];
	
	printf("\nIngrese datos del array/secuencia de doubles (tamaño %d): \n", tamDouble);
	
	// Se inicializa mediante inputs del usuario:
	for(int i = 0; i < tamDouble; i++){
		printf(
		"\nPosición: %d"
		"\nInput:    ", i);
		
		scanf("%lf", &arrayDouble[i]);
		// scanf("%lf", (arrayDouble + i));
	}
	
	// Muestra en pantalla el valor máximo almacenado:
	printArrayMAX(arrayDouble, tamDouble);
}


// void printArrayMAX(double *arrayDouble, int capacidadDouble){
void printArrayMAX(double arrayDouble[], int capacidadDouble){
	// Valor máximo a registrar siempre.
	double valorMaximo = 0;
	
	for(int i = 0; i < capacidadDouble; i++){
		if(arrayDouble[i] > valorMaximo){
			// Si se encuentra un valor mayor, se asigna como nuevo máximo.
			valorMaximo = arrayDouble[i];
		}
	}
	
	// Imprime el valor máximo registrado:
	printf("\nEl valor máximo registrado fue: %lf\n", valorMaximo);
	return;
}