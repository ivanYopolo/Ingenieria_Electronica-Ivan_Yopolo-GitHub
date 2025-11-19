#include "../inc/includes.h"


// ------------------------------------------------------
// main
// ------------------------------------------------------
int main( int argc, char *argv[] ) {
	
	if ( argc != 4 ) {
		printf( "\n[ USO: prog.bin 10.10.1.5 3255 015-025 ]\n\n" );
		exit(1);
	} else {
		conexion_tcp( argv[1], atoi( argv[2] ), argv[3] );
	}
	
	return 0;
}


// ------------------------------------------------------
// conexion_tcp
// ------------------------------------------------------
/* Pide datos de manera DAT076, DAT100 (ej), donde el
 * servidor devuelve los datos correspondientes a los IDs
 * del 76 al 100.
 * El servidor envía los datos de manera secuencial.
 * Cada DATnnn es un string de 256 B y se repite hasta el
 * fin.
 */
void conexion_tcp( char *ipStr, int port, char *sequence ) {
	int		sockFd = 0;
	
	
	sockFd = conectar( ipStr, port );
	
}
