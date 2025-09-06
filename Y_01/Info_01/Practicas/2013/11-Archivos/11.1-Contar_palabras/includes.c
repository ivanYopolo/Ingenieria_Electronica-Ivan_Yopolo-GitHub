/* Archivos_01:
 * 
 * Contar palabras y la cantidad de veces que aparece
 * una palabra clave (como "diodo").
 *
 * Comando: gcc -Wall --pedantic-errors includes.c main.c -o prog.bin
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
/* # PROBLEMA #
 * Cuando el string se corta al final de "buf".
 *
 * # SOLUCIÓN #
 * Hacer el tamaño de buffer una longitud X más el tamaño del string clave a comparar
 * Ej.: char *buf = calloc( TAM_BUF + strlen( mensajeClave ) + 1, sizeof(char) );
 * Después, al final de cada lectura se guardan los últimos bytes equivalentes al tamaño de mensajeClave en un temporal.
 * Al inicio de una nueva lectura, se comienza a leer antes de esos bytes temporales de tamaño mensajeClave.
 */
 
/* # PSEUDOCÓDIGO #
 * Leer una cantidad de Bytes de TAM_STR más lo que ocupe la palabra clave; guardar en "buf".
 * Mientras no se termine el archivo:
 *    Mientras no se termine el array "buf":
 *       Comparar strings entre "buf" y "palabraClave", hasta la longitud de "palabraClave".
 *       Si se encuentra una coincidencia exacta:
 *          Incrementar contador de "cantidadPalabras" en 1.
 *    Guardar los últimos Bytes de "buf" al inicio del mismo, correspondientes a la longitud de "palabraClave".
 *    Hacer una lectura después de estos últimos Bytes.
 */
char * contarPalabraClave2( int fdi, int *cantidadPalabras ){
   int  cant = 1;
   char letra = 0;
   int  cursorTemp = 0;
   int  cursorBuf = 0;         // Para escanear el buf.
   int  cursorClave = 0;       // Guarda la última posición comparada en palabraClave.
   char *buf = NULL;
   char *palabraClave = NULL;  // Palabra clave a buscar.
   long longitudClave = 0;     // Longitud de la palabra clave.

   printf( "Ingrese la palabra clave a buscar:\t\t" );
   palabraClave = writeStrD();

   longitudClave = strlen( palabraClave );   // Longitud del string + '\0'.
   buf = calloc( longitudClave + TAM_STR, sizeof(char) );
   cant = read( fdi, buf, longitudClave + TAM_STR );   // cant = Bytes leídos.

   // Cuenta la cantidad de palabras CLAVE encontradas.
   while ( cant != 0 && palabraClave != NULL ){
     
     // printf( "\n[ letra = %d ]\n", letra );
     
      do{ // Repite hasta llegar al final de buf.
         
         if ( !letra ){  // Busca 1° letra de palabraClave.
         
            if( buf[ cursorBuf ] == palabraClave[ cursorClave ] ){   // Detectó una letra.
             
               letra = 1;
            }else{
                 
               // printf( "Buscando primera letra...\n" );
               cursorBuf++;
            }
         }else{  // Se detectó primera coincidencia.
             
            if ( buf[ cursorBuf ] == palabraClave[ cursorClave ] && \
                  cursorClave < strlen( palabraClave ) ){  // Busca espacios.
             
               // printf( "Buscando espacios...\n" );
               // printf( "\n[ buf[ cursorBuf ] = %c ]\n", buf[ cursorBuf ] );
               cursorBuf++;
               cursorClave++;
            }else{   // Sale, o detectó una coincidencia exacta, o un falso positivo, o se cortó el string.
             
               if ( buf[ cursorBuf - 1 ] == palabraClave[ cursorClave - 1 ] && \
                     palabraClave[ cursorClave ] == '\0' ){   // Checkea por coincidencia exacta.
                     
                  // printf( "\n[ COINCIDENCIA ]\n" );
                  (*cantidadPalabras)++;  // Suma el contador.
               }
                 
               cursorClave = 0;
               letra = 0;
            }
         }
         
         printf( "%c", buf[ cursorBuf ] );
      }while ( cursorBuf + cursorTemp < cant );  // Llego al final de buf.
        
      printf( "\n# Llegó al final del buf #\n" );
        
      // cursorBuf--;
        
      // Guarda los últimos bytes correspondientes a longitudClave en las primeras posiciones.
      for ( cursorTemp = 0; cursorTemp < longitudClave; cursorTemp++ ){
            
         buf[ cursorTemp ] = buf[ cursorBuf - longitudClave + cursorTemp ];
         printf( "\n[ buf[ cursorTemp ] = %c ]\n", buf[ cursorTemp ] );
      }
        
      // printf( "\n[ cant             = %d ]\n", cant );
      // printf( "\n[ cursorBuf        = %d ]\n", cursorBuf );
        
      // Se saltea los primeros Bytes (anteriores/antiguos).
      cant = read( fdi, buf + cursorTemp, TAM_STR );   // cant = Bytes leídos.
        
      cursorBuf = 0;  // Para escanear el buf.
   }   // Llegó al final del archivo.

   return palabraClave;
}


//--------------------------------------------------------------------------
//                           contarPalabraClave
//--------------------------------------------------------------------------
// Cuenta la cantidad de palabras CLAVE en el archivo 
// (varios Bytes/lectura).
// Dicha palabra la obtiene como input del usuario.
// Devuelve la palabra clave dinámicamente.
/* # PSEUDOCÓDIGO #
 * Leer una cantidad de Bytes de TAM_STR más lo que ocupe la palabra clave; guardar en "buf".
 * Mientras no se termine el archivo:
 *    Mientras no se termine el array "buf":
 *       Comparar strings entre "buf" y "palabraClave", hasta la longitud de "palabraClave".
 *       Si se encuentra una coincidencia exacta:
 *          Incrementar contador de "cantidadPalabras" en 1.
 *    Guardar los últimos Bytes de "buf" al inicio del mismo, correspondientes a la longitud de "palabraClave".
 *    Hacer una lectura después de estos últimos Bytes.
 */
char * contarPalabraClave( int fdi, int *cantidadPalabras ){
   int  cant = 1;
   char *buf = NULL;
   char *palabraClave = NULL;  // Palabra clave a buscar.
   long longitudClave = 0;     // Longitud de la palabra clave.

   printf( "Ingrese la palabra clave a buscar:\t\t" );
   palabraClave = writeStrD();

   longitudClave = strlen( palabraClave );   // Longitud del string.
   buf = calloc( longitudClave + TAM_STR, sizeof(char) );
   cant = read( fdi, buf, longitudClave + TAM_STR );   // cant = Bytes leídos.
   
   buf[ cant - 1 ] = '\0';

   while ( cant > 0 && palabraClave != NULL ){
   
      char *temp = buf;
      while( ( temp = strstr( temp, palabraClave ) ) != NULL ){
         
         (*cantidadPalabras)++;
         temp++;
      }
      
      for( int i = 0; i < longitudClave + TAM_STR; i++ ){
         
         printf( "%c", buf[ i ] );
      }

      // /*
      // Guarda los últimos bytes correspondientes a longitudClave en las primeras posiciones.
      for ( int cursorTemp = 0; cursorTemp < longitudClave; cursorTemp++ ){
         
         buf[ cursorTemp ] = buf[ cant + cursorTemp - 1 ];
      }
      // */
      
      // strncpy( buf, buf + cant, longitudClave );
        
      // Se saltea los primeros Bytes (anteriores/antiguos).
      cant = read( fdi, buf + longitudClave + 1, TAM_STR );   // cant = Bytes leídos.
      
      buf[ cant + longitudClave - 1 ] = '\0';
      
      printf( "\n[ cant             = %d ]\n", cant );
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
        printf( "\nSe detectaron [ %d ] coincidencias de \"%s\".\n", cantidadPalabras, palabraClave );
    }else{  
        // Modo palabras totales.
        printf( "\nSe detectaron [ %d ] palabras.\n", cantidadPalabras );
    }
}
