/*
	Realizar una función que reciba un número y un string vacío, donde luego coloque
	en este string el número convertido en binario por el método de divisiones.
*/

#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#define tamString 50

void decBin( int numDec, char numBin[] );

int main(){
	char numeroBinario[ tamString ];
	int numeroDecimal = 0;
	
	system( "clear" );
	
	printf( "Ingrese el número a convertir en binario:\t\t" );
	// scanf( "%d", &numeroDecimal );
	scanf( "%d", &numeroDecimal );
	
	decBin( numeroDecimal, numeroBinario );
	
	printf( "\nEl número en binario es:               \t\t\t%s\n\n", numeroBinario );
	
	return 1;
}


// Recibe un número y lo convierte en un string binario (divisiones).
void decBin( int numDec, char numBin[] ){
	int cociente = numDec;	// N° a dividir por iteración.
	int i = 0;	// Índice parar recorrer "numBin".
	
	// Divide por base 2.
	// Guarda el resto en un string.
	// Invierte el string.
	
	if( !numDec ){
		numBin[ 0 ] = '0';
		numBin[ 1 ] = '\0';
		return;
	}
	
	while( cociente > 0 ){
		numBin[ i ] = cociente % 2 + '0';	// Guarda el resto de la división.
		cociente = cociente / 2;	// Divide por 2 para la siguiente iteración.
		i++;
	}
	
	numBin[ i ] = '\0';
	
	// Invierte el string (se guarda invertido inicialmente).
	for( int j = 0, k = i - 1; j < k; j++, k-- ){
		char temp = numBin[ j ];
		numBin[ j ] = numBin[ k ];
		numBin[ k ] = temp;
	}
	
	return;
}

