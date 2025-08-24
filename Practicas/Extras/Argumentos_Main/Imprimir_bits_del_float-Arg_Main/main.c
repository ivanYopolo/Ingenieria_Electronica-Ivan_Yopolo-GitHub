/*
	Realizar un programa que recibe del usuario un número mediante el 
	kernel y muestre en pantalla la composición de bits del float 
	(signo, exponente, mantisa).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decBin( const unsigned int numDec, unsigned char numBin[] );


// Campo de bits ( struct de bits del float + [union con struct + float] ).
struct CorazonFloat{
	unsigned int mantisa:23;
	unsigned int exponente:8;
	unsigned int signo:1;
};

union EstructuraFloat{
	float numeroFloat;
	struct CorazonFloat campoFloat;
};


int main( int argc, char *argv[] ){
	union EstructuraFloat numF;	// Union entre el número y una estructura con sus bits correspondientes.
	unsigned char bitsExponente[ 9 ];
	unsigned char bitsMantisa[ 24 ];
	
	if( argc > 1 ){	// 2° argumento es el número float.
		printf( "El número tipo flotante es:\t\t%s\n", argv[ 1 ] );
		
		// Pasar de string a float.
		numF.numeroFloat = atof( argv[ 1 ] );
		
		decBin( numF.campoFloat.exponente, bitsExponente );
		decBin( numF.campoFloat.mantisa, bitsMantisa );
		
		printf( "Bit de signo:              \t\t%d\n", numF.campoFloat.signo );
		printf( "Bits de exponente:         \t\t%s\n", bitsExponente );
		printf( "Bits de mantisa:           \t\t%s\n", bitsMantisa );
	}
	else{
		printf( "### ERROR: Falta número tipo flotante (decimal) como argumento. ###\n" );
	}
}



// Pasa de decimal a binario (string).
void decBin( const unsigned int numDec, unsigned char numBin[] ){
	int cociente = numDec;	// Cociente de la división.
	int i = 0;				// Recorre array resto.
	// int potencia = 0;		// Para pasar de string a entero.
	// int intTemp = 0;		// Temporal para pasar por potencias.
	
	
	if( cociente == 0 ){
		// resto[ 0 ] = '0';
		// resto[ 1 ] = '\0';
		numBin[ 0 ] = '0';
		numBin[ 1 ] = '\0';
	}
	else{
	
		while( cociente > 0 ){
			// resto[ i ] = cociente % 2;
			numBin[ i ] = cociente % 2 + '0';
			
			cociente = cociente / 2;
			
			i++;
		}
		
		// resto[ i ] = '\0';
		numBin[ i ] = '\0';
		// i--;	// Para que no se pase del límite.
		// potencia = i;	// Guarda el "tamaño" hasta la última potencia.
		
		// Dar vuelta el string resto.
		for( int j = 0, h = i - 1; j < h; j++, h-- ){
			// char temp = resto[ j ];
			// resto[ j ] = resto[ h ];
			// resto[ h ] = temp;
			char temp = numBin[ j ];
			numBin[ j ] = numBin[ h ];
			numBin[ h ] = temp;
		}
		
	}
	
	return;
}