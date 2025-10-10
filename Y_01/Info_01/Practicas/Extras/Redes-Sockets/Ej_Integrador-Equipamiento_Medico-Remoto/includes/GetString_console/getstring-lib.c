#include "getstring-lib.h"


//--------------------------------------------------------------------------
// writeStrD
//--------------------------------------------------------------------------
/* Agarra un string del Kernel y lo guarda en un string.
 * ### DINÁMICO ###
 */
char * write_str_d() {
   char strI[TAM_STR];

   // No poner strlen() porque toma el salto de línea.
   while ( fgets( strI, TAM_STR, stdin ) == NULL ){
      printf( "[ ERROR: POR FAVOR, ESCRIBA DE VUELTA. ]\n" );
   }  // ERROR
   
   // Flushea el buffer:
   if ( strI[strlen( strI ) - 1] != '\n' ){
 
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
   }

   // Si se detecta un salto de línea:
   if ( strI[strlen( strI ) - 1] == '\n' ){
      strI[strlen( strI ) - 1] = '\0';
   }

   // Aloja memoria en el HEAP para el string.
   char *strO = (char *) calloc( strlen( strI ), sizeof(char) );
  
   strcpy( strO, strI );
  
   return strO;
}


//--------------------------------------------------------------------------
// writeStr
//--------------------------------------------------------------------------
/* Agarra un string del Kernel y lo guarda en un string.
 * ### TAMAÑO FIJO ###
 */
void write_str( char *string, int tamString ) {
   // No poner strlen() porque toma el salto de línea.
   if( fgets( string, tamString, stdin ) == NULL );   // ERROR
   
   // Flushea el buffer:
   if( string[strlen( string ) - 1] != '\n' ){
      int ch = 0;
      while( ( ch = getchar() ) != '\n' && ch != EOF );
   }
   
   // Si se detecta un salto de línea:
   if( string[strlen( string ) - 1] == '\n' )
      string[strlen( string ) - 1] = '\0';
}


//--------------------------------------------------------------------------
// better_scanf
//--------------------------------------------------------------------------
/* "scanf()" con un buffer limpio para "fgets()".
 */
void better_scanf( char *parameters, void *buffer ) {
   scanf( parameters, buffer );
   int ch = 0;
   while ( ( ch = getchar() ) != '\n' && ch != EOF );
}