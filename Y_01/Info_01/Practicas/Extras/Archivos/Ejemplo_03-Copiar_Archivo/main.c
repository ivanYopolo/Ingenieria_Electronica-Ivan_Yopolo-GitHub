/*
    Guardar en un archivo las variables de entorno de entorno.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define TAMLN 2

int main( int argc, char *argv[], char *envp[] ){
    int out = 1;
    int fdO = open( "Copia-Variables-de-entorno.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666 );
    char lineNew[ TAMLN ] = "\n\n";
    int cursorEnvp = 0;
    int tamEnvp = 1;    // Tamaño del string dentro de una posición en "envp".
    
    if( fdO < 0 ){
        printf( "[ ERROR: FALLÓ LECTURA DEL ARCHIVO. ]\n" );
    }else{
        do{ // Leer variables de entorno.
            tamEnvp = strlen( envp[ cursorEnvp ] );
            
            if( tamEnvp > 0 ){
                out = write( fdO, envp[ cursorEnvp ], tamEnvp );  // Escribe variables de entorno.
                cursorEnvp++;
                out = write( fdO, lineNew, TAMLN );
            }else{                        
                printf( "Llegó al final.\n" );
            }
        }while( ( out > 0 ) && ( envp[ cursorEnvp ] != NULL ) );
        close( fdO );
    }
    
    return 0;
}

