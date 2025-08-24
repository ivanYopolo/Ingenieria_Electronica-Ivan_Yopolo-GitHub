/*
Escribir un programa que lea el archivo de texto que recibe por línea de
comandos y determine:
* Cantidad total de palabras
* Cantidad de veces que aparece la palabra “diodo”
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countWords( int fd, int *cant );
int findWord( int fd, char msg[], int *cant );

int main( int argc, char *argv[] ){
	int fd = 0, cant = 0;
	// char msg[ 6 ] = "diodo";
	
	if( argc < 2 ){
		printf( "[ ERROR: CANTIDAD DE ARGUMENTOS INSUFICIENTE. ]\n" );
	}else{
		if( strstr( argv[ 1 ], ".txt" ) == NULL ){
			printf( "[ ERROR: ARCHIVO CON EXTENSIÓN INVÁLIDA. ]\n" );
		}else{
			fd = open( argv[ 1 ], O_RDONLY );
			
			if( fd == -1 ){	// Error opening file.
				printf( "[ ERROR: ARCHIVO NO EXISTENTE. ]\n" );
			}else{
				do{
					int palabras = countWords( fd, &cant );
                    printf( "Se detectaron [ %d ] palabras.\n", palabras );
                    
					// int aparicionesPalabra = findWord( fd, msg, &cant );
					// printf( "Se detectaron [ %d ] apariciones de \"%s\".\n", aparicionesPalabra, msg );
				}while( cant != 0 );
                
                close( fd );
			}
			
		}
	}
	
	return 1;
}

/*
# Objetivo #
Retorna en entero la cantidad de palabras contadas 
(salto de línea separa palabras).
	
# Pseudo-código #
MIENTRAS no se llegó al final del archivo:
	Lee el 1 Byte del archivo y lo guarda en un temporal "buf".
    MIENTRAS se detecte que "buf" sea caracter por "isalpha()":
        Lee 1 Byte del archivo y lo guarda en "buf".
    Incrementa un contador "words" en 1 (cuenta las palabras).
*/
int countWords( int fd, int *cant ){
	int words = 0;	// Contador de palabras.
	char buf[ 2 ];
    
    *cant = read( fd, (void *) buf, 1 );
    
	do{
        // if( isalpha( *buf ) != 0 ){            
            while( isalpha( *buf ) != 0 ){    // 0: no es letra; (!= 0): es letra.
                *cant = read( fd, (void *) buf, 1 );
            }
            words++;
        // }
    }while( *cant != 0 );

    return words;
}

/*
# Objetivo #
Encontrar y contar la cantidad de veces que
aparece una palabra  determinada (dada por "msg").

# Pseudo-código #
A
*/
int findWord( int fd, char msg[], int *cant ){
	int wordsFound = 0;	// Contador de coincidencias encontradas.
	
	
	
	return wordsFound;
}

