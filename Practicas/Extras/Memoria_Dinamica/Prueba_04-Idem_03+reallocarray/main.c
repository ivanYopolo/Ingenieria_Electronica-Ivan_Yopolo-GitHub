/*
 * Prueba para ver si funciona array de strings con
 * memoria dinámica + structs dinámicos + reallocarray().
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

    // Array de punteros dinámicos.
    char *arrStr[ 3 ];
    
    arrStr[ 0 ] = test.arr1;
    arrStr[ 1 ] = test.arr2;
    arrStr[ 2 ] = test.arr3;
    
    // ############################
    printf( "\n[ CAMBIO ]\n" );
    // ############################
    // Cambia el tamaño de cada bloque de memoria apuntado por cada puntero
    // dentro del array. La cantidad de elementos es la longitud del string.
    arrStr[ 0 ] = reallocarray( arrStr[ 0 ], strlen( arrStr[ 0 ] ), 6 );
    arrStr[ 1 ] = reallocarray( arrStr[ 1 ], strlen( arrStr[ 1 ] ), 10 );
    arrStr[ 2 ] = reallocarray( arrStr[ 2 ], strlen( arrStr[ 2 ] ), 12 );
    
    strcpy( arrStr[ 0 ], "Messi" );
    strcpy( arrStr[ 1 ], "Maradroga" );
    strcpy( arrStr[ 2 ], "Pendorchazo" );
    
    printf( "String N° 1:\t%s\n", arrStr[ 0 ] );
    printf( "String N° 2:\t%s\n", arrStr[ 1 ] );
    printf( "String N° 3:\t%s\n", arrStr[ 2 ] );

    // Libera memoria de cada puntero.
    for( int i = 0; i < 3; i++ ){
        free( arrStr[ i ] );
    }
    
    return 0;
}

