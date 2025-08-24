/*
	Realizar una función que reciba un número y un string vacío, donde luego coloque
	en este string el número convertido en binario por el método de restas.
*/

#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#define tamString 50

void decBin( int numDec, char numBin[] );

int main(){
	char numeroBinario[ tamString ];
	int numeroDecimal = 0;
	
	numeroBinario[ tamString - 1 ] = '\0';
	
	system( "clear" );
	
	printf( "Ingrese el número a convertir en binario:\t\t" );
	scanf( "%d", &numeroDecimal );
	
	decBin( numeroDecimal, numeroBinario );
	
	printf( "\nEl número en binario es:               \t\t\t%s\n\n", numeroBinario );
	
	return 1;
}


// Recibe un número y lo convierte en un string binario (restas).
void decBin( int numDec, char numBin[] ){
	int numero = 0;		// N° a ser restado.
	int potencia = 0;	// Cuenta las potencias utilizadas.
	int resta = 1;		// Al multiplicarse por una potencia de 2, resta al N° tomado.
	char cero = 0;		// Verifica si se colocó el nulo '\0' o no.
	// int tam = 0;		// Tamaño del string.
	
	
	// Buscar el N° más grande, pero menor al input, que sea potencia de 2.
	// Restar este N° al input.
	// Repetir hasta llegar a 0 como resultado de la resta.
	// Guardar, de los N°s utilizados para la resta, la potencia de 2 utilizada, de mayor a menor.
	// Los exponentes utilizados van con 1; el resto, 0.
	
	if( !numDec ){	// Caso de un 0.
		numBin[ 0 ] = '0';
		numBin[ 1 ] = '\0';
		return;
	}
	
	numero = numDec;	// Número a ser restado iterativamente.
	
	while( numero > 0 ){ // Repetir hasta llegar a 0.
		
		// Buscar potencias de 2.
		// Verificar que sean menores que "numero".
		while( resta <= numero ){
			resta *= 2;		// 1° iteración: 2^1 = 2.
			potencia++;		// 2° iteración: 2^2 = 4.
		}
		
		if( resta > numero ){
			resta /= 2; // Última iteración se pasa.
		}
		
		// Restar al "numero".
		numero = numero - resta;
		
		numBin[ potencia ] = '1'; // Guarda la potencia utilizada como 1 (orden directo).
		
		if( !cero ){
			numBin[ potencia + 1 ] = '\0';	// Pone el nulo solamente cuando registra el exponente más alto.
			cero = 1;	
		}
		
		resta = 0;		// Reset Resta.
		potencia = 0;	// Reset Potencia.
	}
	
	// Completar array con 0s.
	for( int j = 0; numBin[ j ] != '\0'; j++ ){
		if( numBin[ j ] != '1' ){
			numBin[ j ] = '0';	// Escribe un 0 cuando no encuentra un 1.
		}
	}	
	
	return;
}

