/* Archivos_01:
 * 
 * Contar palabras y la cantidad de veces que aparece
 * una palabra clave (como "diodo").
 *
 * Comando: gcc -Wall --pedantic-errors includes.c main.c -o prog.bin
 */

#include "includes.h"


int main( int argc, char *argv[] ){
   int fdi = 0;
   int opcion;
   int cantidadPalabras = 0;
   char *palabraClave = NULL;

   // Array de punteros a función:
   char * (* seleccion[ 2 ])( int fdi, int *cantidadPalabras ) = { contarPalabras, contarPalabraClave };

   if( argc == 2 ){
      fdi = open( argv[ 1 ], O_RDONLY );
     
      if( fdi > 0 ){
         printf( "Seleccione el tipo de comportamiento:\n"
                 "1) Cuenta palabras.\n"
                 "2) Cuenta cuantas veces aparece una palabra clave (coincidencia exacta).\n" );
         
         do{ // Input del usuario:
            printf( "\tOpción: " );
            
            scanf( "%d", &opcion );
            // Flushea buffer.
            int ch = 0;
            while( ( ch = getchar() ) != '\n' && ch != EOF );

            if( opcion < 1 || opcion > 2 ){
            
               printf( "\n[ ERROR: INGRESE UNA OPCIÓN VÁLIDA. ]\n" );
            }else{
               // Usar puntero a función para elegir lo que hace.
               palabraClave = seleccion[ opcion - 1 ]( fdi, &cantidadPalabras );
            }
         }while( opcion < 1 || opcion > 2 );
         
         mostrarResultados( cantidadPalabras, palabraClave );
         
         if( palabraClave != NULL )
            free( palabraClave );
         
         close( fdi );
      }else{
         printf( "[ ERROR: NOMBRE DE ARCHIVO INVÁLIDO, NO SE PUDO ABRIR. ]\n" );
      }
   }else{
      printf( "[ ERROR: NÚMERO DE ARGUMENTOS INVÁLIDO. ]\n" );
   }

   return 1;
}



