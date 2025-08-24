/*
 * Prueba para ver si funciona array de strings con
 * memoria dinámica + structs dinámicos.
 * Se prueba si se puede cambiar el tamaño dinámicamente
 * de cada string dentro del array por separado.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
struct DynStr{
    char *data;     // Pointer to the dynamically allocated character array
    size_t length;  // Current length of the string (excluding null terminator)
    size_t capacity; // Allocated memory capacity for the string
};
*/

struct pruebaStr{
    char *arr1;
    char *arr2;
    char *arr3;
};

int main(){
    struct pruebaStr test;

    test.arr1 = calloc( 5, sizeof( char ) );
    test.arr2 = calloc( 5, sizeof( char ) );
    test.arr3 = calloc( 5, sizeof( char ) );
    
    strcpy( test.arr1, "Pepe");
    strcpy( test.arr2, "Papa");
    strcpy( test.arr3, "Rulo");
    
    printf( "String N° 1:\t%s\n", test.arr1 );
    printf( "String N° 2:\t%s\n", test.arr2 );
    printf( "String N° 3:\t%s\n", test.arr3 );

    // Array dinámico de punteros dinámicos temporales.
    char **arrTemps = calloc( 3, sizeof( void * ) );
    
    char *temp1 = calloc( 6, sizeof( char ) );     // Messi
    char *temp2 = calloc( 10, sizeof( char ) );    // Maradroga
    char *temp3 = calloc( 12, sizeof( char ) );    // Pendorchazo
    
    if( temp1 != NULL && temp2 != NULL && temp3 != NULL ){
        printf( "\n[ CAMBIO ]\n" );
        
        arrTemps[ 0 ] = temp1;
        arrTemps[ 1 ] = temp2;
        arrTemps[ 2 ] = temp3;
        
        // Libera memoria de los arrays (strings) antes de cambiarlos.
        // Caso contrario, queda inaccesible esa memoria y puede generar
        // un MEMORY LEAK.
        free( test.arr1 );
        free( test.arr2 );
        free( test.arr3 );
        // Asigna estos nuevos espacios dinámicos de memoria a los
        // arrays anteriores.
        test.arr1 = arrTemps[ 0 ];
        test.arr2 = arrTemps[ 1 ];
        test.arr3 = arrTemps[ 2 ];
    
        strcpy( test.arr1, "Messi" );
        strcpy( test.arr2, "Maradroga" );
        strcpy( test.arr3, "Pendorchazo" );
        
        printf( "String N° 1:\t%s\n", test.arr1 );
        printf( "String N° 2:\t%s\n", test.arr2 );
        printf( "String N° 3:\t%s\n", test.arr3 );
        // Libera la memoria de estos temporales utilizados.
        // No hace falta hacer un "doble free()" porque los tríos
        // de punteros apuntan a las mismas zonas de memoria.
        for( int i = 0; i < 3; i++ ){
            free( arrTemps[ i ] );
        }
    }
    
    return 0;
}

