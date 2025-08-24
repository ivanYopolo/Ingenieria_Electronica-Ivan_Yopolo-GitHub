/*
 * Prueba para ver si funciona array de strings con
 * memoria dinámica + structs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pruebaStr{
    char arr1[ 5 ];
    char arr2[ 5 ];
    char arr3[ 5 ];
};

int main(){
    struct pruebaStr test;
    
    strcpy( test.arr1, "Pepe");
    strcpy( test.arr2, "Papa");
    strcpy( test.arr3, "Rulo");
    
    // Asigna un pointer a char-pointers, o pointer a strings.
    // Su tamaño es de lo que ocupa un pointer veces X elementos (array).
    char **arrStr = malloc( sizeof( void * ) * 1 ); 
    // Cada elemento es igualado al array de la estructura.
    arrStr[ 1 ] = test.arr1;
    printf( "String 1:\t%s\n", arrStr[ 1 ] );
    
    arrStr = realloc( arrStr, sizeof( void * ) * 2 ); 
    arrStr[ 2 ] = test.arr2;
    printf( "String 2:\t%s\n", arrStr[ 2 ] );
    
    arrStr = realloc( arrStr, sizeof( void * ) * 3 ); 
    arrStr[ 3 ] = test.arr3;
    printf( "String 3:\t%s\n", arrStr[ 3 ] );
    
    
    free( arrStr );
    
    return 0;
}

