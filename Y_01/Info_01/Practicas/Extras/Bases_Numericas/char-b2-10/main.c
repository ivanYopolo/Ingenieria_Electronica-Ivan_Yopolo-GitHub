/*
	Realizar una función que reciba un numero positivo en base 2 en formato string y devuelva 
	la cantidad en base 10 o -1 en caso de error. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamString 5

int binarioDecimal( char *string );


int main(){
	// char string[ tamString ] = "0112";
	// char string[ tamString ] = "011a";
	char string[ tamString ] = "0111";
	int numDec = 0;		// Acá se guarda la conversión en decimal.

	system( "clear" );
	
	printf( "El número en binario es:\t\t%s\n", string );

	numDec = binarioDecimal( string ); // Guarda la conversión.
	
	if( numDec != -1 )
		printf( "\nEl número en decimal es:\t\t%d\n", numDec );
	else
		printf( "\n### ERROR: el número no está en base binaria ###\n" );
	
	return 1;
}


// Convierte el número de binario (en string) a decimal (en entero).
int binarioDecimal( char *string ){
	int conversion = 0;	// El número convertido en decimal y entero.
	int temp = 0;		// Donde se guarda cada dígito ya potenciado.
	int tam = 0;	// Para calcular el tamaño del string numérico.
	
	
	while( string[ tam ] == '0' || string[ tam ] == '1' ){
		tam++;	// Recorre el string hasta encontrar algo no binario en char.
		
		// Checkear por errores (distinto de 0, 1 y el nulo).
		if( string[ tam ] != '0' && string[ tam ] != '1' && string[ tam ] != '\0' )
			return -1;
	}
	
	// Si en la pos. X está el último dígito, tam = X + 1 en el final de la secuencia.
	
	printf( "Dígitos del número binario:\t\t%d\n\n", tam );
	
	
	// Pasada externa para recorrer cada posición/dígito (der - iz).
	for( int i = tam - 1; i >= 0; i-- ){
		
		temp = string[ i ] - '0';	// Guarda en temporal el dígito actual pasado a ENTERO.
		
		printf( "Posición %d del número en binario:\t%d\n", i, temp );
		
		// Pasada interna para sumar potencias de 2 en cada dígito (sin contar el 0).
		for( int j = ( tam - 1 - i ); j > 0; j-- ){	
			// "j" se iguala a el complemento de "i", yendo en orden inverso;
			// última posición = exponente 0 (no entra al for);
			// posición 0 = exponente máximo.
			
			temp *= 2;
		}
		
		conversion += temp;	// Guarda la sumatoria en entero.
		
		
		printf( "Temporal (bin):\t\t\t%d\n", temp );
		printf( "Numero (bin):\t\t\t%d\n", conversion );
		
		temp = 0;
	}
	
	
	
	
	return conversion;
}

