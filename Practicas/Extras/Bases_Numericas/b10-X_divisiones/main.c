/*
	Realizar una función que imprima un número en bases octal, decimal y hexadecimal. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printNumBases( int numDec );
void revArrChar( char arrResto[], int tam );
void converBase( int numDec, char conversion[], int base );


int main(){
	int num = 0;	// Numero a convertir en bases 2, 8 y 16.
	
	system( "clear" );
	
	printf( "Ingrese el número a convertir en distintas bases:\t\t" );
	scanf( "%d", &num );	
	int c; while( ( c = getchar() ) != '\n' && c != EOF );
	
	printNumBases( num );
	
	return 1;
}



// Imprime el mismo número en bases 2, 8 y 16.
void printNumBases( int numDec ){
	
	char numBin[ 50 ];
	char numOct[ 50 ];
	char numHex[ 50 ];
	
	converBase( numDec, numBin, 2 );
	converBase( numDec, numOct, 8 );
	converBase( numDec, numHex, 16 );


	printf( "Número en binario (base 2):     \t\t\t\t%s\n", numBin );
	printf( "Número en octal (base 8):       \t\t\t\t%s\n", numOct );
	printf( "Número en hexadecimal (base 16):\t\t\t\t%s\n", numHex );
}

// Hacer DIVISIONES.


// Devuelve número convertido a base elegida. 
void converBase( int numDec, char result[], int base ){
	int i = 0;			// Para ir por posiciones en el array "result[]".
	int cociente = 0;	// División sucesiva de cocientes.
	// Posibles restos; posición en array concuerda con resto obtenido.
	char restos[ 17 ] = "0123456789ABCDEF";	

	cociente = numDec;	// 1° iteración, se divide el número inicial.

	if( !cociente ){	// Si el N° es 0 inicialmente:
		result[ 0 ] = '0';
		result[ 1 ] = '\0';
		return;
	}
	
	// Guarda los restos en el array de restos, pero en ORDEN INVERSO.
	while( cociente > 0 ){		// Si divide por 0, termina.

		int resto = cociente % base;	// Guarda el resto de la división.
	
		result[ i ] = restos[ resto ];	// Ej.: si el resto es 10: da 'A'.

		cociente = cociente / base;		// Divide para la próxima iteración.
		
		i++;	// Pasa a la siguiente posición.
	}

	result[ i ] = '\0';

	// Para poner el array resto en el orden correcto:
	revArrChar( result, i );
} 


// Invierte el orden del array "resto", lo pone en su orden correcto.
void revArrChar( char arrResto[], int tam ){
	
	for( int j = 0, i = tam - 1; j < i; j++, i-- ){

		char temp = arrResto[ j ];
		arrResto[ j ] = arrResto[ i ];
		arrResto[ i ] = temp;
	}
	
}
