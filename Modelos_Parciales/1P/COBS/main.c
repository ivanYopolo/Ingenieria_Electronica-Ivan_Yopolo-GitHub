/*
Implementar encoding COBS y decoding.
*/

#include <stdio.h>
#include <string.h>

#define arrLEN 197
#define arrCOBS_LEN 200

int encode_COBS( unsigned char *arrInp, unsigned int lenInp, unsigned char *arrCOBS );
int decode_COBS( unsigned char *arrCOBS, unsigned char *arrDeCOBS );


int main(  ){
	unsigned char arrInp[ arrLEN ] = { 7, 0, 0, 9, 3, 4, 5 };
	unsigned char arrCOBS[ arrCOBS_LEN ];
	unsigned char arrDeCOBS[ arrCOBS_LEN ];
	
	printf( "\nArray input:  \t\t" );
	
	for( int i = 0; i < 7; i++ ){
		
		printf( "%d", arrInp[ i ] );
	}
	
	encode_COBS( arrInp, 7, arrCOBS );
	
	printf( "\nArray COBS:\t\t" );
	
	for( int i = 0; i < 10; i++ ){
		
		printf( "%d", arrCOBS[ i ] );
	}
	
	printf( "\n\n" );
	
	// DECODE COBS.
	decode_COBS( arrCOBS, arrDeCOBS );
	
	printf( "\nArray DeCOBS:\t\t" );
	
	for( int i = 0; i < 7; i++ ){
		
		printf( "%d", arrDeCOBS[ i ] );
	}
	
	printf( "\n\n" );
	
	return 0;
}



int encode_COBS( unsigned char *arrInp, unsigned int lenInp, unsigned char *arrCOBS ){
	
	unsigned int lenCOBS = 0;	// Longitud del nuevo mensaje encodeado por COBS.
	
	
	arrCOBS[ 0 ] = 0;	// Primer 0 por COBS.
	
	// strncpy( arrCOBS + 2, arrInp, lenInp );	// Copia array en temporal.
	for( int h = 0; h < lenInp; h++ ){
		arrCOBS[ h + 2 ] = arrInp[ h ];
	}
	
	arrCOBS[ 2 + lenInp ] = 0;	// Último 0 por COBS.
	
	// printf( "\nlenInp:\t%d", lenInp );
	
	lenCOBS = lenInp + 3;	// Longitud del array original + 3 Bytes extra (n elementos, última posición n-1).
	
	
	int i = 0, j = 0;	// Variables para recorrer el array y contar distancia entre 0s.
	while( i < lenCOBS - 1 ){	// -1 así no se come el último 0.
		
		if( arrCOBS[ i ] == 0 ){
			
			printf( "\nSe encontró un 0 en: %d", i );
			
			if( i == 0 ){	// Caso del primer 0: lo pasa de largo.
				
				i++;
			}
			
			// Cuenta distancia hasta el siguiente 0, lo guarda en "j".
			for( j = 1; ( i + j < lenCOBS ) && ( arrCOBS[ i + j ] != 0 ); j++ ){}
			
			printf( "\nJ = %d", j );
			printf( "\nI = %d", i );
			
			arrCOBS[ i ] = j;	// Escribe la distancia hasta el siguiente 0.
			
			i += j;	// Escanea a partir del nuevo 0 encontrado.
		}else{
		
			i++;	// Va a la siguiente pos. del array, por más de que no escanea nada.
		}
	}
	
	printf( "\nValor final J = %d", j );
	printf( "\nValor final I = %d", i );
	
	
	return lenCOBS;
}



int decode_COBS( unsigned char *arrCOBS, unsigned char *arrDeCOBS ){
	
	unsigned int lenDeCOBS = 1;	// Cuenta la longitud del array original.
	unsigned int tempPos = 0;	// Para guardar el desplazamiento con los 0s.
	int i = 0;	// Variable para recorrer "arrDeCOBS". 
	
	
	for( lenDeCOBS = 1; !arrCOBS[ lenDeCOBS ]; lenDeCOBS++ );	
	// Cuenta longitud del array original en base al COBS.
	// Usa "1" así saltea el primer 0 de COBS.
	lenDeCOBS++;	// Suma 1 porque no cuenta cuando llega a 0.
	

	for( int h = 2; arrCOBS[ h ] != 0; h++ ){	// Copia un array en otro, "arrCOBS" en "arrDeCOBS".
		arrDeCOBS[ h - 2 ] = arrCOBS[ h ];	// -2 porque no se toman los 2 primeros (COBS).
	}
	
	
	// Caso primer 0:
	tempPos = arrCOBS[ 1 ];	// Guarda primer desplazamiento hasta el siguiente 0 (primero dentro del array original).
	
	i = tempPos - 1;	// Pone -1 porque cuenta desde el 0; guarda el desplazamiento.
	
	while( ( arrCOBS[ i + 2 ] != 0 ) || ( i + 2 < lenDeCOBS ) ){
		
		tempPos = arrDeCOBS[ i ];	// Guarda cuanto se tiene que desplazar hasta el siguiente 0.
		arrDeCOBS[ i ] = 0; // Pone un 0 en dicha posición.
		i += tempPos;	// Salta al siguiente 0 en posición; repite.
	}
	
	
	return lenDeCOBS;
}

