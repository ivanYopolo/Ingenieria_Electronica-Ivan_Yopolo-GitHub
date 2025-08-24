#include <stdio.h>
#include <stdlib.h>

/*
	Sacar el promedio de un
	array numérico.
*/

// Inicio de la memoria (pointer del array), tamaño del array.
float promedioArray(float *, int);


int main(){
	system("clear");
	
	int tamArr = 0;
	
	printf("\nIngrese el tamaño del array: ");
	scanf("%d", &tamArr);
	
	float arrNum[tamArr];
	
	printf("\n\nLlene los datos del array: \n");
	for(int i = 0; i < tamArr; i++){
		printf("\nPos:  %d", i);
		printf("\nDato: ");
		scanf("%f", &arrNum[i]);
	}
	
	float promArr = promedioArray(arrNum, tamArr);
	
	printf("\n\nEl promedio es de:  %.2f\n\n", promArr);
	
	return 0;
}


float promedioArray(float array[], int tam){
	float sum = 0;
	
	// Cálculo promedio:
	for(int h = 0; h < tam; h++){
		sum += array[h];
	}
	// División por número de elementos:
	return (sum / tam);
}