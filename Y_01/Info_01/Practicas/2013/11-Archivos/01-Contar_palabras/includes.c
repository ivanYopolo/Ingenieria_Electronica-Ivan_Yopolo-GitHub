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
// Cuenta la cantidad de palabras en el archivo (Byte a Byte).
// Devuelve NULL.
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
//                           contarPalabraClave2
//--------------------------------------------------------------------------
// Cuenta la cantidad de palabras CLAVE en el archivo 
// (varios Bytes/lectura).
// Dicha palabra la obtiene como input del usuario.
// Devuelve la palabra clave dinámicamente.
/* SOLUCIONAR:
 * Cuando el string se corta al final de "buf".
 */
char * contarPalabraClave2( int fdi, int *cantidadPalabras ){
    int cant = 1;
    int cursorClave = 0;    // Guarda la última posición comparada en palabraClave.
    char tempChar = 0;  // Guarda el caracter si se corta el string.
    char corte = 0; // 0: lectura normal;   1: se cortó el string y se le
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
//                           contarPalabraClave
//--------------------------------------------------------------------------
// Cuenta la cantidad de palabras CLAVE en el archivo 
// (varios Bytes/lectura).
// Dicha palabra la obtiene como input del usuario.
// Devuelve la palabra clave dinámicamente.
/* SOLUCIONAR:
 * Cuando el string se corta al final de "buf".
 */
char * contarPalabraClave( int fdi, int *cantidadPalabras ){
    int cant = 1;
    char leyendo = 1;
    int cursorBuf = 0;      // Para escanear el buf.
    int cursorClave = 0;    // Guarda la última posición comparada en palabraClave.
    char corte = 1;         // 0: lectura normal;   1: se cortó el string.
    char buf[ TAM_STR ];
    char *palabraClave = NULL;  // Palabra clave a buscar.
    
    printf( "Ingrese la palabra clave a buscar:\t\t" );
    palabraClave = writeStrD();
    
    cant = read( fdi, buf, TAM_STR );   // cant = Bytes leídos.
    
    // Cuenta la cantidad de palabras CLAVE encontradas.
    while( ( cant > 0 ) && ( palabraClave != NULL ) ){
        
        cursorBuf = 0;  // Para escanear el buf.
        printf( "\nbuf = %s\n", buf );

        do{ // Repite hasta llegar al final de buf.
            
            // if( leyendo ){
                if( !corte ){   // Lectura normal por espacios.
                    
                    while( !isspace( buf[ cursorBuf ] ) && \
                    !isblank( buf[ cursorBuf ] ) && \
                    ( cursorBuf < cant ) ){  // Busca letras.
                        printf( "Buscando letras...\n" );
                        cursorBuf++;
                    }   // Sale del while, detectó una letra.
                }  // Caso contrario, busca directamente espacio (cuándo termina la palabra).
                
                while( ( buf[ cursorBuf ] == palabraClave[ cursorClave ] ) && \
                ( cursorBuf < cant ) && \
                ( cursorClave < strlen( palabraClave ) ) ){  // Busca espacios.
                    printf( "Buscando espacios...\n" );
                    cursorBuf++;
                    cursorClave++;
                }   // Sale del while, o detectó una coincidencia exacta, o era un falso positivo, o se cortó el string.
                
                // leyendo = 0;
                
                if( ( buf[ cursorBuf - 1 ] == palabraClave[ cursorClave - 1 ] ) && \
                ( palabraClave[ cursorClave ] == '\0' ) ){   // Checkea por coincidencia exacta.
                    printf( "[ COINCIDENCIA ]\n" );
                    (*cantidadPalabras)++;  // Suma el contador.
                    cursorClave = 0;
                    corte = 0;
                    // cursorBuf = 0;
                }else{
                    leyendo = 0;
                }
                
            }else{

                
                if( ( buf[ cursorBuf - 1 ] == palabraClave[ cursorClave - 1 ] ) && \
                ( palabraClave[ cursorClave ] != '\0' ) ){   // Checkea si se cortó el string.
                    printf( "[ SE CORTÓ EL MENSAJE ]\n" );
                    corte = 1;
                }   // Guarda datos para continuar escaneo cortado.
                
                // printf( "Tumama\n" );
                leyendo = 1;
            }
            
            // printf( "Tupapa\n" );
        }while( cursorBuf < cant );  // Llego al final de buf.
        
        cant = read( fdi, buf, TAM_STR );   // cant = Bytes leídos.
    }   // Llegó al final del archivo.
    
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
