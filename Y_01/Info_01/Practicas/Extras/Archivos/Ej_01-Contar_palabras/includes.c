/* Archivos_01:
 * 
 * Contar palabras y la cantidad de veces que aparece "diodo".
 *
 * Comando: gcc -Wall --pedantic-errors includes.c main.c 
 */

#include "includes.h"


//--------------------------------------------------------------------------
//                           writeStrD
//--------------------------------------------------------------------------
// Agarra un string del Kernel y lo guarda en un string.
// ### DINÁMICO ###
char * writeStrD(){
    char strI[ TAM_STR ];
    
    // No poner strlen() porque toma el salto de línea.
	while( fgets( strI, TAM_STR, stdin ) == NULL ){
        printf( "[ ERROR: POR FAVOR, ESCRIBA DE VUELTA. ]\n" );
    }	// ERROR
	
	if( strI[ strlen( strI ) - 1 ] != '\n' ){
        // Flushea el buffer:
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
//                           contarPalabras
//--------------------------------------------------------------------------
// Cuenta la cantidad de palabras en el archivo.
// Devuelve NULL.
/* SOLUCIONAR:
 * Cuando el string se corta al final de "buf".
 */
char * contarPalabras( int fdi, int *cantidadPalabras ){
    int cant = 1;
    char buf[ 1 ];
    char espacioBlanco = 0;

    cant = read( fdi, buf, 1 );   // cant = Bytes leídos.
    
    if( !isspace( *buf ) )
        (*cantidadPalabras)++;
    
    while( ( cant > 0 ) ){ // Cuenta la cantidad de palabras encontradas.
        printf( "%c", *buf );
        
        // Se detecta un espacio en blanco.
        if( ( !espacioBlanco ) && ( isspace( *buf ) ) ){
            espacioBlanco = 1;
        }

        // Se dejó de detectar espacio en blanco: comienza una palabra.
        if( ( espacioBlanco ) && ( !isspace( *buf ) ) ){
            espacioBlanco = 0;
            (*cantidadPalabras)++;
        }
            
        // printf( "cantidadPalabras = %d\n", *cantidadPalabras );
        
        cant = read( fdi, buf, 1 );   // cant = Bytes leídos.
    } // Llegó al final del archivo.
    
    return NULL;
}


//--------------------------------------------------------------------------
//                           contarPalabraClave
//--------------------------------------------------------------------------
// Cuenta la cantidad de palabras CLAVE en el archivo.
// Dicha palabra la obtiene como input del usuario.
// Devuelve la palabra clave dinámicamente.
/* SOLUCIONAR:
 * Cuando el string se corta al final de "buf".
 */
char * contarPalabraClave( int fdi, int *cantidadPalabras ){
    int cant = 1;
    int cursorClave = 0;
    char buf[ TAM_STR ];
    char *palabraClave = NULL;
    
    printf( "Ingrese la palabra clave a buscar:\t\t" );
    palabraClave = writeStrD();
    
    cant = read( fdi, buf, TAM_STR );   // cant = Bytes leídos.
    // Cuenta la cantidad de palabras CLAVE encontradas.
    while( ( cant > 0 ) && ( palabraClave != NULL ) ){
        int i = 0;
        // printf( "\nbuf = %s\n", buf );

        do{ // Repite hasta llegar al final de buf.
            cursorClave = 0;
        
            // Detecta LA primera letra para empezar a contar.
            while( ( buf[ i ] != palabraClave[ 0 ] ) && ( i < cant ) ){
                i++;
            }   // Detectó LA letra: sale.
            
            if( i < cant ){ // Empieza a escanear si hay espacio en buf.
                // Cuenta mientras detecte las mismas letras.
                while( ( buf[ i ] == palabraClave[ cursorClave ] ) && ( i < cant ) ){
                    cursorClave++;
                    i++;
                }   // Sale del bucle: detectó una palabra.
                
                // Checkea por coincidencias EXACTAS.
                if( ( i <= cant ) && ( palabraClave[ cursorClave ] == '\0' ) && ( !isalpha( buf [ i ] ) ) )
                    (*cantidadPalabras)++;    // Cuenta una palabra.
                
                // printf( "cantidadPalabras = %d\n", *cantidadPalabras );
            }
        }while( i < cant );  // Llego al final de buf.
        
        cant = read( fdi, buf, TAM_STR );   // cant = Bytes leídos.
    }
    
    return palabraClave;
}



//--------------------------------------------------------------------------
//                           mostrarResultados
//--------------------------------------------------------------------------
// Muestra los resultados por pantalla.
// Si el puntero es NULL, no imprime los datos de palabraClave.
void mostrarResultados( int cantidadPalabras, char *palabraClave ){
    
    if( palabraClave != NULL ){ 
        // Modo palabra clave.
        printf( "\nSe detectaron [ %d ] coincidencias de %s.\n", cantidadPalabras, palabraClave );
    }else{  
        // Modo palabras totales.
        printf( "\nSe detectaron [ %d ] palabras.\n", cantidadPalabras );
    }
}
