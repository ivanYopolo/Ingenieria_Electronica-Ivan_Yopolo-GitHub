/*
 * Prueba para ver si funciona array de strings con
 * memoria dinámica.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char arr1[ 5 ] = "Pepe";
    char arr2[ 5 ] = "Papa";
    char arr3[ 5 ] = "Rulo";
    
    // Al ser asignado como double-pointer, este puede
    // ser "cambiado de lugar (a lo que apunta)" sin
    // problemas. Como array NO SE PUEDE.
    char **arrStr = malloc( sizeof( void * ) * 1 ); 
    arrStr[ 1 ] = arr1;
    printf( "String 1:\t%s\n", arrStr[ 1 ] );
    
    arrStr = realloc( arrStr, sizeof( void * ) * 2 ); 
    arrStr[ 2 ] = arr2;
    printf( "String 2:\t%s\n", arrStr[ 2 ] );
    
    arrStr = realloc( arrStr, sizeof( void * ) * 3 ); 
    arrStr[ 3 ] = arr3;
    printf( "String 3:\t%s\n", arrStr[ 3 ] );
    
    
    
    free( arrStr );
    
    return 0;
}

