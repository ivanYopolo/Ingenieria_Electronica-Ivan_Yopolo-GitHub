#include "burbuja.h"

void burbujeo( char string[], int (*comparacion)( char a, char b ) ){
	// Pasada Macroscópica para recorrer todo el array. Número de pasadas igual a
	// número de elementos ordenados.
	for( int i = 0; i < strlen( string ) - 1; i++ ){

		/* 
		Pasada Microscópica para ir ordenando un elemento en particular.
		Se pone "j < strlen ( string ) - i" porque, cuando se terminen de ordenar
		un número de elementos igual al número de pasadas macroscópicas, no será
		necesario reordenarlos.
		*/
		for( int j = 0; j < strlen( string ) - 1 - i; j++ ){

			// Comparación verdadera = se cambian de posición.
			if( (*comparacion)( string[ j ], string[ j + 1 ] ) ){
				char temp = string[ j ];
				string[ j ] = string[ j + 1 ];
				string[ j + 1 ] = temp;
			}
		}
	} 

}
