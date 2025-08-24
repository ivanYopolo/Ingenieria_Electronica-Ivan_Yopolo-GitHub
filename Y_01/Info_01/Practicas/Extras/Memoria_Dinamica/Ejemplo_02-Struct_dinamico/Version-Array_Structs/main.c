/*
 * Recibe una cantidad X de "alumnos" (se finaliza con legajo = 0) por kernel y
 * muestra el promedio de notas y aquellos alumnos estuvieron por encima del promedio.
 *
 * Versión: array de estructuras.
 */

/*
# Con un array de notas #

printf( "\nIngrese las notas (0 o menor para terminar el ingreso de notas):\t" );
do{
    pointerStruct[ sizeStruct - 1 ].notas = realloc( pointerStruct[ sizeStruct - 1 ].notas, notaAct );
    scanf( "%d", &notaTemp );
    pointerStruct[ sizeStruct - 1 ].notas[ notaAct ] = notaTemp;
    notaAct++;
}while( notaTemp > 0 );
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

struct alumno{
    int nota;
    float legajo;
    char *nombre;
    char *apellido;
};

// Para limpiar el main.
void getUserInput();

// Dinámico.
char * writeStrD();

void copiarStruct( struct alumno *destino, struct alumno origen );

void printScreen( struct alumno *pointerStruct, int sizeStruct );


//--------------------------------------------------------------------------
//                                  main
//--------------------------------------------------------------------------
int main(){
    // Puntero a structs tipo "alumno" (array).
    int sizeStruct = 0; // N° de structs creados.
    int notaTemp = 1;
    float legajoTemp = 1;
    struct alumno *pointerStruct = calloc( sizeStruct + 1, sizeof(struct alumno) );
    
    
    printf( "Ingrese los alumnos y sus datos correspondientes.\n\n" );
    
    do{ // Cada iteración = un nuevo alumno ingresado.
        
        struct alumno alumX;
        alumX.nota = 1;
        alumX.legajo = 1;
        
        // ### Es importante crear un nuevo STRUCT dinámicamente ###
        // Caso contrario, SEGMENTATION FAULT (se accede a cualquier parte de la memoria no inicializada).
        struct alumno *tempPointer = (struct alumno *) reallocarray( pointerStruct, sizeStruct + 1, sizeof(struct alumno) );  
        
        if( tempPointer != NULL ){
            // ### IMPORTANTE ###
            // Apunta a un struct REAL. Sinó, no apunta a nada (o a cualquier cosa).
            // Aloja memoria en el HEAP.
            // Esto es IMPORTANTE porque sinó accede a zonas que están en el STACK.
            pointerStruct = tempPointer;

            pointerStruct[ sizeStruct ].nota = 0;
            pointerStruct[ sizeStruct ].legajo = 0;
            
            // Aloja memoria dinámica para los strings (arrays de chars dinámicos).
            pointerStruct[ sizeStruct ].nombre = calloc( 2, sizeof(char) );
            pointerStruct[ sizeStruct ].apellido = calloc( 2, sizeof(char) );

            // ### Copiando inputs del usuario ###
            // Legajo
            printf( "\nIngrese el legajo N° %d (para salir, poner un 0 o negativo):\t", sizeStruct + 1 );
            scanf( "%f", &legajoTemp );
            // Para evitar problemas con el fgets():
            char ch = 0;
            while( ( ch = getchar() ) != '\n' && ch != EOF );
            
            if( legajoTemp > 0 ){   // Se registró un alumno válido. 
                // Empieza en 1, incrementa por iteración.
                sizeStruct++;
                
                alumX.legajo = legajoTemp;
            
                // /* ### DINÁMICO ###
                // Nombre
                printf( "\nIngrese el/los nombre/s:\t" );
                if( ( alumX.nombre = writeStrD() ) == NULL ){
                    printf( "\n[ ERROR: SIN MEMORIA. ]\n" );
                    break;
                }else{
                    // printf( "\nLectura exitosa: \t\t%s\n", alumX.nombre );
                }
                
                /* ### NORMAL ###
                // Nombre
                printf( "\nIngrese el/los nombre/s:\t" );
                writeStr( alumX.nombre, TAM );
                
                // Apellido
                printf( "\nIngrese el/los apellido/s:\t" );
                writeStr( alumX.nombre, TAM );
                */
                
                // Apellido
                printf( "\nIngrese el/los apellido/s:\t" );
                
                if( ( alumX.apellido = writeStrD() ) == NULL ){
                    printf( "\n[ ERROR: SIN MEMORIA. ]\n" );
                    break;
                }else{
                    // printf( "\nLectura exitosa: \t\t%s\n", alumX.apellido );
                }
                // */
                
                // Nota
                do{
                    printf( "\nIngrese la nota:\t\t" );
                    scanf( "%d", &notaTemp );
                    // Para evitar problemas con el fgets();
                    char ch = 0;
                    while( ( ch = getchar() ) != '\n' && ch != EOF );
                }while( notaTemp < 1 );
                
                alumX.nota = notaTemp;
                
                // #### COPIA STRUCTS ####
                copiarStruct( pointerStruct + (sizeStruct - 1), alumX );
                // Pasa la dirección del struct mismo.
            }
        }else{
            printf( "[ ERROR: NO SE PUDO CREAR NUEVA ESTRUCTURA. ]\n" );
            free( pointerStruct );
            return 1;
        }
        
    }while( legajoTemp > 0 );    // Termina el ingreso de datos de alumnos.
    
    if( sizeStruct > 0 ){
        // Imprime en pantalla el promedio y los que estén arriba del promedio.
        printScreen( pointerStruct, sizeStruct );
        
        // #########################################
        // Libera memoria.
        // #########################################
        for( int i = sizeStruct - 1; i >= 0; i-- ){
            free( pointerStruct[ i ].nombre );
            free( pointerStruct[ i ].apellido );
        }
    }
    
    free( pointerStruct );
    
    return 0;
}

//--------------------------------------------------------------------------
//                           copiarStruct
//--------------------------------------------------------------------------
// Copia datos de un struct a otro.
void copiarStruct( struct alumno *destino, struct alumno origen ){
    // printf( "[ Copiando structs... ]\n" );
    
    /* ### Datos del struct inicial ###
    printf( "\n[ Datos de origen ]\n" );
    
    printf( "Legajo origen:  \t\t%.3f\n", origen.legajo );
    printf( "Nota origen:    \t\t%d\n", origen.nota );
    printf( "Nombre origen:  \t\t%s\n", origen.nombre );
    printf( "Apellido origen:\t\t%s\n", origen.apellido );
    */
    
    destino->legajo = origen.legajo;
    destino->nota   = origen.nota;
    strncpy( destino->nombre,    origen.nombre,     strlen( origen.nombre ) ); 
    strncpy( destino->apellido,  origen.apellido,   strlen( origen.apellido ) );
    
    /* ### Datos copiados en el struct dinámico ###
    printf( "\n[ Datos de destino ]\n" );
    
    printf( "Legajo:         \t\t%.3f\n", destino->legajo );
    printf( "Nota:           \t\t%d\n", destino->nota );
    printf( "Nombre:         \t\t%s\n",  destino->nombre );
    printf( "Apellido:       \t\t%s\n", destino->apellido );
    */
    // printf( "[ Copiado exitosamente ]\n" );
}

//--------------------------------------------------------------------------
//                           writeStrD
//--------------------------------------------------------------------------
// Agarra un string del Kernel y lo guarda en un string.
// ### DINÁMICO ###
char * writeStrD(){
    char strI[ TAM ];
    
    // No poner strlen() porque toma el salto de línea.
	while( fgets( strI, TAM, stdin ) == NULL ){
        printf( "[ ERROR: POR FAVOR, ESCRIBA DE VUELTA. ]\n" );
    }	// ERROR
	
	// Flushea el buffer:
	if( strI[ strlen( strI ) - 1 ] != '\n' ){
        
		char ch = 0;
		while( ( ch = getchar() ) != '\n' && ch != EOF );
	}
    
	// Si se detecta un salto de línea:
	if( strI[ strlen( strI ) - 1 ] == '\n' ){
        strI[ strlen( strI ) - 1 ] = '\0';
    }
    
    // Aloja memoria en el HEAP para el string.
    char *strO = (char *) calloc( strlen( strI ), sizeof(char) );
    
    strcpy( strO, strI );
    
    return strO;
}

//--------------------------------------------------------------------------
//                            printScreen
//--------------------------------------------------------------------------
// Imprime los datos de TODAS las estructuras en pantalla.
// Imprime los promedios y quienes estuvieron por encima de este.
void printScreen( struct alumno *pointerStruct, int sizeStruct ){
    int posStruct = 0;
    float promedio = 0;
    float *mejoresPromedios = calloc( sizeStruct, sizeof(float) );    // Array de posiciones del pointerStruct de los mejores promedios.
    int posMejProm = 0;
    
    printf( "\n\n### DATOS REGISTRADOS ###\n" );
    
    posStruct = sizeStruct;
    while( posStruct >= 0 ){
        // Notas + Promedio
        promedio += pointerStruct[ posStruct - 1 ].nota;
        posStruct--;
    }
    
    promedio /= sizeStruct;
    
    printf( "# El promedio registrado fue de [ %.2f ] #\n\n", promedio );
    
    // Quienes estuvieron por encima de este.
    for( posStruct = sizeStruct; posStruct >= 0; posStruct-- ){
        
        if( pointerStruct[ posStruct - 1 ].nota >= promedio ){
            
            mejoresPromedios[ posMejProm ] = posStruct - 1;
            posMejProm++;
        } 
    }
    
    // posMejProm--;   // Se pasa 1 posición.
    printf( "# Los/as siguientes alumnos/as superaron el promedio: #\n" );
    for( posMejProm--; posMejProm >= 0; posMejProm-- ){
        int tempPos = mejoresPromedios[ posMejProm ];
        
        printf( "* %s %s tiene una nota de [ %d ]\n", pointerStruct[ tempPos ].nombre, \
               pointerStruct[ tempPos ].apellido, \
               pointerStruct[ tempPos ].nota );   // Nombre + apellido + nota.
    }
    
    free( mejoresPromedios );
}

