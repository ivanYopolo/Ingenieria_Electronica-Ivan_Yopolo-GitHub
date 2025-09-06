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

   int fdlog = open( "conteoPalabras.log", O_WRONLY | O_TRUNC | O_CREAT, 0666 );

   cant = read( fdi, buf, 1 );   // cant = Bytes leídos.

   if( !isspace( *buf ) )
      (*cantidadPalabras)++;

   while( ( cant > 0 ) ){ // Cuenta la cantidad de palabras encontradas.
      // printf( "%c", *buf );
      dprintf( fdlog, "%c", *buf );

      // Se detecta un espacio en blanco.
      if( ( !espacioBlanco ) && ( isspace( *buf ) ) ){
         espacioBlanco = 1;
      }

      // Se dejó de detectar espacio en blanco: comienza una palabra.
      if( ( espacioBlanco ) && ( !isspace( *buf ) ) ){
         espacioBlanco = 0;
         (*cantidadPalabras)++;
      }

      cant = read( fdi, buf, 1 );   // cant = Bytes leídos.
   } // Llegó al final del archivo.
   
   dprintf( fdlog, "\n\n[ Se registró una cantidad de palabras de:\t %d ]", *cantidadPalabras );
   
   close( fdlog );

   return NULL;
}


//--------------------------------------------------------------------------
//                           contarPalabraClave
//--------------------------------------------------------------------------
// Cuenta la cantidad de palabras CLAVE en el archivo (varios Bytes/lectura).
// Dicha palabra la obtiene como input del usuario.
// Devuelve la palabra clave dinámicamente.
char * contarPalabraClave( int fdi, int *cantidadPalabras ){
   int  cant = 1;
   char *buf = NULL;
   char *palabraClave = NULL;  // Palabra clave a buscar.
   long longitudClave = 0;     // Longitud del string clave.
   
   // Deja los datos en un archivo de LOG (tipo debugging).
   int fdlog = open( "conteoPalabraClave.log", O_WRONLY | O_TRUNC | O_CREAT, 0666 );

   printf( "Ingrese la palabra clave a buscar:\t\t" );
   palabraClave = writeStrD();

   longitudClave = strlen( palabraClave );   // Longitud del string.
   buf = calloc( longitudClave + TAM_STR, sizeof(char) );   // Tamaño dependiente del string clave.
   cant = read( fdi, buf, longitudClave + TAM_STR - 1 );   // cant = Bytes leídos.
   
   buf[ cant ] = '\0';
   
   dprintf( fdlog, "[ BUF tiene tamaño de: %ld + %d = %ld B. ]\n", longitudClave, TAM_STR, longitudClave + TAM_STR );
   dprintf( fdlog, "[ \'\\0\' ubicado en índice: %d ]\n", cant );
   dprintf( fdlog, "[ Mensaje clave a buscar:   \"%s\". ]\n\n", palabraClave );

   while ( cant > 0 && palabraClave != NULL ){
   
      // Por si hay más de 1 coincidencia en 1 sola lectura:
      char *temp = buf;
      while( ( temp = strstr( temp, palabraClave ) ) != NULL ){
         
         (*cantidadPalabras)++;
         temp++;
      }  // Sale si es NULL (no encontró coincidencias).
      
      // Lo guarda en un archivo de log para analizar el texto.
      dprintf( fdlog, "[ Lectura %d B ] -- %s\n\n", cant, buf );

      // Guarda los últimos bytes correspondientes a longitudClave en las primeras posiciones.
      for ( int cursorTemp = 0; cursorTemp < longitudClave; cursorTemp++ ){
         // Empieza a copiar a partir de la longitud mínima del buffer.
         buf[ cursorTemp ] = buf[ TAM_STR + cursorTemp - 1 ];
      }
        
      // Se saltea los primeros Bytes (anteriores/antiguos).
      cant = read( fdi, buf + longitudClave, strlen( buf ) - longitudClave );   // cant = Bytes leídos.
   }  // Llegó al final del archivo.
   
   dprintf( fdlog, "\n\n[ Se detectaron %d coincidencias de \"%s\". ]", *cantidadPalabras, palabraClave );
   
   free( buf );
   
   close( fdlog );
   
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
