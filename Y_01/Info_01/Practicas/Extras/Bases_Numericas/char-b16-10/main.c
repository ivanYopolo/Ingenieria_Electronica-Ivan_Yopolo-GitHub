/*
	Realizar una función que reciba un numero positivo en base 16 en formato string y devuelva 
	la cantidad en base 10 o -1 en caso de error. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamString 5

int hexaDecimal( char *string );


int main(){
	// char string[ tamString ] = "071G";
	// char string[ tamString ] = "071P";
	char string[ tamString ] = "071F";
	int numDec = 0;		// Acá se guarda la conversión en decimal.

	system( "clear" );
	
	printf( "El número en hexa es:\t\t%s\n", string );

	numDec = hexaDecimal( string ); // Guarda la conversión.
	
	if( numDec == -1 )
		printf( "\n### ERROR: el número no está en base hexa ###\n" );
	else
		printf( "\nEl número en decimal es:\t\t%d\n", numDec );
	
	return 1;
}


// Convierte el número de binario (en string) a decimal (en entero).
int hexaDecimal( char *string ){
	int conversion = 0;	// El número convertido en decimal y entero.
	int temp = 0;		// Donde se guarda cada dígito ya potenciado.
	int tam = 0;	// Para calcular el tamaño del string numérico.
	
	
	while( ( string[ tam ] >= '0' && string[ tam ] <= '9' ) || ( string[ tam ] >= 'A' && string[ tam ] <= 'F' ) ){
		tam++;	// Recorre el string hasta encontrar algo no hexa en char.
		
		// Checkear por errores (fuera del rango hexa y distinto del nulo).
		if( string[ tam ] < '0' || string[ tam ] > '9' ){
			if( string[ tam ] < 'A' || string[ tam ] > 'F' ){
				if( string[ tam ] != '\0' )
					return -1;
			}
		}
	}
	
	// Si en la pos. X está el último dígito, tam = X + 1 en el final de la secuencia.
	
	printf( "Dígitos del número hexa:\t\t%d\n\n", tam );
	
	
	// Pasada externa para recorrer cada posición/dígito (der - iz).
	for( int i = tam - 1; i >= 0; i-- ){
		
		
		if( string[ i ] >= '0' && string[ i ] <= '9' )
			temp = string[ i ] - '0';	// Guarda en temporal el dígito actual pasado a ENTERO.
		else
			temp = string[ i ] - 'A' + 10;	// Guarda en temporal el dígito actual pasado a ENTERO.
		// A(hex) = 10(dec).
		
		printf( "Posición %d del número en hexa:\t%c\n", i, string[ i ] );
		
		
		// Pasada interna para sumar potencias de 2 en cada dígito (sin contar el 0).
		for( int j = ( tam - 1 - i ); j > 0; j-- ){	
			// "j" se iguala a el complemento de "i", yendo en orden inverso;
			// última posición = exponente 0 (no entra al for);
			// posición 0 = exponente máximo.
			
			temp *= 16;
		}
		
		conversion += temp;	// Guarda la sumatoria en entero (dígito * 8^posición_der_iz).
		
		
		printf( "Temporal (hex):\t\t\t%d\n", temp );
		printf( "Numero (hex):\t\t\t%d\n\n", conversion );
		
		temp = 0;
	}
	
	
	
	
	return conversion;
}

