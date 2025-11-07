#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main() {
	long j = 0;
	long k = 0;
	char tabla[21] = "### Pseudo-tabla ###\n";
	srand( time( NULL ) );
	
	
	printf( "####################\n" );
	printf( "%s", tabla );
	printf( "\"%%-\"   \t pone justificación izquierda (si se pide completar con números).\n" );
	printf( "\"%%7\"   \t completa con '7' espacios las variables numéricas a izquierda (justificación derecha).\n" );
	
	for ( int i = 0; i < 5; i++ ) {
		printf( "%*ld | %-5ld\n", 7, j, k );
		j = rand() % 100000 + 1;
		k = rand() % 100000 + 1;
	}
	/* # Equivalencias #
	 * printf( "%*d", width, num );
    * printf( "%2$*1$d", width, num );
	 */
	printf( "\n[ %%2$*1$ld | %%-5ld ]\n" );
	printf( "Esto genera:\n"
				"%%2:   \t completar con 2 espacios a iz. (just. der.).\n"
				"$*1$:  \t especifica la longitud, con una variable más (puede acortar el mensaje).\n"
				"%%-5:  \t completa con 5 espacios a der. (just. iz.).\n" );
	
	printf( "####################\n" );
	
	return 0;
}