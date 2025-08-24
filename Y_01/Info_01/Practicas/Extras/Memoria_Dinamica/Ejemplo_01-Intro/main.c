/*
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 5

char *copiaS( char *strI );

int main(){
    char strI[ TAM ] = "Pepe";
    // char *strI;
    
    char *msg = copiaS( strI );
    
    if( msg != NULL ){
        printf( "El string input es:     \t%s\n", strI );
        printf( "El string se copió como:\t%s\n", msg );
        
        free( msg );
    }
    
    return 0;
}


char *copiaS( char *strI ){
    char *copia;
    
    if( ( strI != NULL ) && ( strI[ 0 ] != '\0' ) ){
        int len = strlen( strI );
        
        // MAL: char copia[ len + 1 ];
        copia = (char *) malloc( len + 1 );
        
        if( copia != NULL ){
            strcpy( copia, strI );
        }
    }
    
    return copia;   // Retornar por memoria dinámica una variable NO local.
}


