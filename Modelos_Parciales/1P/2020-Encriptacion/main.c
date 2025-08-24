// clear; gcc -Wall main.c encriptar.c -o main

#include "encriptar.h"

int main(){
	char mensaje[ tamStr ];
	char mensajeDesp[ tamStr ];
	char mensajeDesE[ tamStr ];
	char mensajeEncrNum[ tamStr ];
	int desplazamiento = 0;
	// char mensajeDesENum[ tamStr ];
	
	
	system( "clear" );
	
	
	printf( "Ingrese el mensaje:\t\t\t\t" );
	
	// Por si es vacío o tira error (buffer suficiente):
	if(fgets(mensaje, tamStr, stdin) == NULL){
		
		printf( "\n# ERROR #\n" );
		// Error.
	}
	if( mensaje[ tamStr - 1 ] != '\n' ){
		
		// Buffer chico, fgets() falló en leer la línea entera.
		int ch = 0;
		while( ( ch = getchar() ) != '\n' && ch != EOF ); // Flush the input buffer
		// now print an error message or something, 
		// and ask the user to try again with shorter input 
	}
	if( mensaje[ tamStr - 1 ] == '\n' )
		mensaje[ tamStr - 1 ] = '\0';
	
	
	desplazamiento = desplazar_letras( mensaje, mensajeDesp );
	printf(
	"\nEl mensaje encriptado es:\t\t\t%s\
	\nDesplazamiento:\t\t%d\n", mensajeDesp, desplazamiento );
	
	desencriptar_texto( mensajeDesp, mensajeDesE, desplazamiento );
	printf(
	"\nEl mensaje DESencriptado es:\t\t\t%s\
	\nDesplazamiento:\t\t%d\n", mensajeDesE, desplazamiento );
	
	encriptar_numeros( mensajeDesp, mensajeEncrNum );
	printf(
	"\nEl mensaje encriptado (por numeros) es:\t\t%s\n", mensajeEncrNum );
	
	// desencriptar_numero( mensajeEncrNum, mensajeDesENum );
	// printf(
	// "\nEl mensaje DESencriptado (por numeros) es:\t%s\n", mensajeDesENum );
	
	// es_encriptable( mensaje );
	
	// Imprimir el mensaje encriptado.
	// printf( "\nEl mensaje encriptado es: \t\t%s\n\n", mensajeEncrNum );
}

