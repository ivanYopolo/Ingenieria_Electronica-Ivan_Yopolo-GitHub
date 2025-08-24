#include <stdio.h>
#include <stdlib.h>

/*
Escribir una función que determine si una secuencia (array) de bytes (chars) recibida
como parámetro está vacía o no. A tal fin, la asumirá como una secuencia en
ASCII terminada en '\0' (NULL). El tipo de retorno debe ser bool, conforme al
siguiente prototipo:
bool emptyString(const char *);

Array de chars -> STRING.
*/

// Como el C no reconoce "bool", hay que poner esta línea:
typedef char bool;

bool emptyString(char *);

int main(){
	system("clear");
	
	// Tamaño de la secuencia/array.
	int tamSec = 1;
	
	printf("\nIngrese el tamaño: ");
	scanf("%d", &tamSec);
	
	// String (array de char/bytes).
	char secuencia[tamSec];
	
	printf("\nIngrese la secuencia: ");
	// Obtener STRING.
	int c; while ((c = getchar()) != EOF && c != '\n');// Función para "flush buffer" y que "fgets" funcione bien.
	fgets(secuencia, tamSec, stdin);
	
	// Valor NULL:
	if(!emptyString(secuencia)){
		printf("\n\nLa secuencia ESTÁ VACÍA.\n");
		return 0;
	}
	
	printf("\n\nLa secuencia NO está vacía.\n");
	return 1;
}

bool emptyString(char secuencia[]){
	if(secuencia[0] == '\0' || secuencia[0] == '\n'){
		// Vacío.
		return 0;
	}
	
	return 1;
}