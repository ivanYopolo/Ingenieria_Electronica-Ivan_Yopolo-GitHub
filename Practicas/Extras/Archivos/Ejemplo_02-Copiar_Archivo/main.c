/*
    Leer un archivo y copiarlo en otro.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define TAM 500
#define B_READ 1    // Bytes a leer por ciclo.

int main(){
    int cant = 1, out = 1;
    char buf[ TAM ];
    int fdI = open( "textoInput.txt", O_RDONLY, 0666 );
    int fdO = open( "textoOutput.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666 );
    
    if( ( fdI < 0 ) || ( fdO < 0 ) ){
        
        printf( "[ ERROR: FALLÓ LECTURA DEL ARCHIVO. ]\n" );
    }else{
        
        cant = read( fdI, buf, TAM );
        
        do{
            out = write( fdO, buf, cant );  // Escribe cantidad de bytes leídos.
            cant = read( fdI, buf, TAM );
        }while( ( cant > 0 ) && ( out > 0 ) );
        
        close( fdI );
        close( fdO );
    }
    return 0;
}
