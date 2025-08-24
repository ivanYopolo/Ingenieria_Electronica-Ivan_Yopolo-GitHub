#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define TAM 100

int main(){
	char buf[ TAM ];	// A mayor tamaño el bufer, mayor lectura por iteración.
	int cant;
	int fd = open( "mi_text.txt", O_RONLY );
	
	// Lee un byte (caracter) en cada iteración:
	do{
		cant = read( fd, (void *) buf, 1 ); // A mayor número (el último argumento), más Bytes de lectura por iteración.
		if( cant != 0 ){
			printf( "%c", buf[ 0 ] );
		}
	}while( cant != 0 );
}