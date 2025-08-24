/*
 * Recibe una cantidad X de "alumnos" (se finaliza con legajo = 0) por kernel y
 * muestra el promedio de notas y aquellos alumnos estuvieron por encima del promedio.
 *
 * Versión: array de punteros a estructuras.
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

int initStructs( struct alumno ***pointerStruct, const int sizeStruct );

// Para limpiar el main.
float getUserInput( struct alumno **pointerStruct, int *sizeStruct );

void freeData( struct alumno **pointerStruct, const int sizeStruct );

// Dinámico.
char * writeStrD();

void copiarStruct( struct alumno *destino, struct alumno origen );

void printScreen( struct alumno **pointerStruct, int sizeStruct );


//--------------------------------------------------------------------------
//                                  main
//--------------------------------------------------------------------------
int main(){
    int sizeCurso = 0; // N° de structs creados.
    float running = 1;
    // Puntero a punteros a structs tipo "alumno" (array).
    struct alumno **curso = (struct alumno **) calloc( sizeCurso + 1, sizeof(void *) );
    
    printf( "Ingrese las/os alumnas/os y sus datos correspondientes.\n\n" );
    
    do{ // Cada iteración = un nuevo alumno ingresado.
        
        if( initStructs( &curso, sizeCurso ) > 0 ){
            // Si no falla la inicialización, carga datos del usuario.
            running = getUserInput( curso, &sizeCurso );
        }else{
            // Faltó memoria.
            running = -1;
        }
        
        
    }while( running > 0 );    // Termina el ingreso de datos de alumnos.
    
    if( running >= 0 ){
        
        if( sizeCurso > 0 ){
            // Imprime en pantalla el promedio y los que estén arriba del promedio.
            printScreen( curso, sizeCurso );
        }
    }else{
        printf( "\n[ ERROR FATAL. ]\n" );
    }
    
    // Libera memoria (array de pointers).
    freeData( curso, sizeCurso );
    
    return 0;
}



// --------------------------------------------------------------------------
//                           initStructs
// --------------------------------------------------------------------------
// Inicializa (y declara) las estructuras y el array para que apunten a algo no nulo.
// Recibe el puntero por REFERENCIA, así modifica al PUNTERO MISMO.
int initStructs( struct alumno ***pointerStruct, const int sizeStruct ){
    int running = 1;
    
    // ### Se expande el tamaño del array de punteros a struct "alumno" ###
    struct alumno **tempPointerDouble = (struct alumno **) reallocarray( *pointerStruct, sizeStruct + 1, sizeof(void *) );  
    
    // ### Es importante crear un nuevo STRUCT dinámicamente ###
    // Caso contrario, SEGMENTATION FAULT (se accede a cualquier parte de la memoria no inicializada).
    struct alumno *tempPointer = (struct alumno *) calloc( 1, sizeof(struct alumno) );  
    
    if( tempPointer != NULL && tempPointerDouble != NULL ){
        
        // Aloja memoria en el HEAP.
        // Esto es IMPORTANTE porque sinó accede a zonas que están en el STACK.
        *pointerStruct = tempPointerDouble;
        
        // ### IMPORTANTE ###
        // Apunta a un struct REAL. Sinó, no apunta a nada (o a cualquier cosa).
        (*pointerStruct)[ sizeStruct ] = tempPointer;
        
        (*pointerStruct)[ sizeStruct ]->nota = 0;
        (*pointerStruct)[ sizeStruct ]->legajo = 0;
        
        // Aloja memoria dinámica para los strings (arrays de chars dinámicos).
        (*pointerStruct)[ sizeStruct ]->nombre = calloc( 2, sizeof(char) );
        (*pointerStruct)[ sizeStruct ]->apellido = calloc( 2, sizeof(char) );

    }else{
        printf( "\n[ ERROR: NO SE PUDO CREAR NUEVO PUNTERO A ESTRUCTURA. ]\n" );
        running = -1;
    }
    
    return running;
}


// --------------------------------------------------------------------------
//                           getUserInput
// --------------------------------------------------------------------------
// Recibe input del usuario.
float getUserInput( struct alumno **pointerStruct, int *sizeStruct ){
    float legajoTemp = 0;
    int notaTemp = 0;
    int ch = 0;
    char correctInput = 1;
    float running = 1;
    /* 
     * running > 0: sigue ejecución.
     * running = 0: deja de recibir datos.
     * running = -1: ERROR.
     */

    
    // Legajo
    do{
        correctInput = 1;
        
        printf( "\nIngrese el legajo N° %d con punto (para salir, poner un 0 o negativo):\t", (*sizeStruct) + 1 );
        scanf( "%f", &legajoTemp );
        // Para evitar problemas con el fgets():
        ch = 0;
        while( ( ch = getchar() ) != '\n' && ch != EOF );
        
        if( legajoTemp >= 1000 ){
            
            printf( "\n[ ERROR: DATO INVÁLIDO. INGRESE NUEVAMENTE EL DATO. ]" );
            correctInput = 0;
        }else{
            
            for( int i = 0; (i < (*sizeStruct)) && (correctInput == 1); i++ ){  // Checkea por legajos repetidos.
            
                if( legajoTemp == pointerStruct[ i ]->legajo ){
                    
                    printf( "\n[ PRECAUCIÓN: SE REPITIERON LEGAJOS. ]\n" );
                    correctInput = 0;
                }else{
                    // Limpio, no se repite ninguno.
                    correctInput = 1;
                }      
            }
        }        
    }while( !correctInput );
    
    if( legajoTemp > 0 ){    
        
        running = legajoTemp;
        
        struct alumno alumX;
        
        // Empieza en 1, incrementa por iteración.
        (*sizeStruct)++;
        
        alumX.legajo = legajoTemp;
    
        // Nombre
        printf( "\nIngrese el/los nombre/s:\t" );
        if( ( alumX.nombre = writeStrD() ) == NULL ){
            printf( "\n[ ERROR: SIN MEMORIA. ]\n" );
            running = -1;
        }
        
        // Apellido
        printf( "\nIngrese el/los apellido/s:\t" );
        
        if( ( alumX.apellido = writeStrD() ) == NULL ){
            printf( "\n[ ERROR: SIN MEMORIA. ]\n" );
            running = -1;
        }
        
        // Nota
        do{
            printf( "\nIngrese la nota:\t\t" );
            scanf( "%d", &notaTemp );
            // Para evitar problemas con el fgets();
            ch = 0;
            while( ( ch = getchar() ) != '\n' && ch != EOF );
            
            if( notaTemp < 1 || notaTemp > 10 )
                printf( "\n[ ERROR: DATO INVÁLIDO. INGRESE NUEVAMENTE EL DATO. ]" );
        }while( notaTemp < 1 || notaTemp > 10 );
        
        alumX.nota = notaTemp;
        
        // #### COPIA STRUCTS ####
        copiarStruct( pointerStruct[ (*sizeStruct) - 1 ], alumX );
        // Pasa la dirección del struct mismo.
    }else{
        // Ingresó dato inválido => terminó.
        running = 0;
    }
    
    return running;
}


// --------------------------------------------------------------------------
//                           copiarStruct
// --------------------------------------------------------------------------
// Copia datos de un struct a otro.
void copiarStruct( struct alumno *destino, const struct alumno origen ){
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
        
		int ch = 0;
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
void printScreen( struct alumno **pointerStruct, int sizeStruct ){
    int posStruct = 0;
    float promedio = 0;
    float *mejoresPromedios = calloc( sizeStruct, sizeof(float) );    // Array de posiciones del pointerStruct de los mejores promedios.
    int posMejProm = 0;
    
    printf( "\n\n### DATOS REGISTRADOS ###\n" );
    
    posStruct = sizeStruct - 1;
    while( posStruct >= 0 ){
        // Notas + Promedio
        promedio += pointerStruct[ posStruct ]->nota;
        posStruct--;
    }
    
    promedio /= sizeStruct;
    
    printf( "# El promedio registrado fue de [ %.2f ] #\n\n", promedio );
    
    // Quienes estuvieron por encima de este.
    for( posStruct = sizeStruct - 1; posStruct >= 0; posStruct-- ){
        
        if( pointerStruct[ posStruct ]->nota >= promedio ){
            
            mejoresPromedios[ posMejProm ] = posStruct;
            posMejProm++;
        } 
    }
    
    // posMejProm--;   // Se pasa 1 posición.
    printf( "# Las/os siguientes alumnas/os superaron el promedio: #\n" );
    for( posMejProm--; posMejProm >= 0; posMejProm-- ){
        int tempPos = mejoresPromedios[ posMejProm ];
        
        printf( "* %3.3f: %s %s tiene una nota de [ %d ].\n", pointerStruct[ tempPos ]->legajo, \
                                                              pointerStruct[ tempPos ]->nombre, \
                                                              pointerStruct[ tempPos ]->apellido, \
                                                              pointerStruct[ tempPos ]->nota );
    }
    
    free( mejoresPromedios );
}


// --------------------------------------------------------------------------
//                           freeData
// --------------------------------------------------------------------------
// #########################################
// Libera memoria (de cada pointer).
// #########################################
void freeData( struct alumno **pointerStruct, const int sizeStruct ){

    if( sizeStruct > 0 ){
        for( int i = sizeStruct - 1; i >= 0; i-- ){ 
            free( pointerStruct[ i ]->nombre );
            free( pointerStruct[ i ]->apellido );
            
            free( pointerStruct[ i ] );
        }
    }
    
    free( pointerStruct );
}


