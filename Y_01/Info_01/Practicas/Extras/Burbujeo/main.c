// Practicar burbujeo (ordenamiento burbuja).

#include "burbuja.h"
#define tamMensj 50

int ascendente( char c1, char c2 );
int descendente( char c1, char c2 );

int main(){
	char mensj[ tamMensj ];	
	int seleccion = 0;

	system( "clear" );

	printf( "Ingrese el mensaje a ordenar:\t\t" );

	fgets( mensj, tamMensj, stdin );
	int c = 0; while( ( c = getchar() ) != '\n' && c != EOF );
	if( mensj[ strlen( mensj ) - 1 ] == '\n' )
		mensj[ strlen( mensj ) - 1 ] = '\0';

	printf( 
	"\nSeleccione el método de ordenamiento:\n\
	   1) Ascendente.\n\
	   2) Descendente.\n\t\t\t" );
	scanf("%d", &seleccion);
	while( ( c = getchar() ) != '\n' && c != EOF );	

	switch(seleccion){
		case 1:
			burbujeo( mensj, ascendente );
			break;
		case 2:
			burbujeo( mensj, descendente );
			break;
	}

	printf("\nEl mensaje ordenado es:\t\t%s\n", mensj);

	return 1;
}



int ascendente( char c1, char c2 ){

	return c1 < c2;
}


int descendente( char c1, char c2 ){

	return c1 > c2;
}

