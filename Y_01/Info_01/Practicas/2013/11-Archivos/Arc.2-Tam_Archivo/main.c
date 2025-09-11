/* # Archivos.2 #
 * Cálculo del tamaño de un archivo.
 *
 * Comando: clear; gcc -Wall --pedantic-errors main.c
 */

#include "includes.h"

int main( int argc, char *argv[] ){

   if ( argc != 2 ){

      printf( "\n[ ERROR: NÚMERO DE ARGUMENTOS INVÁLIDO. ]\n\n" );
   }else{

      int fdi = open( argv[ 1 ], O_RDONLY );

      if ( fdi < 1 ){

         printf( "\n[ ERROR: NOMBRE DE ARCHIVO INVÁLIDO. ]\n\n" );
      }else{

         long int tamArchivo = calcularTamArchivo( fdi );
         mostrarResultados( tamArchivo );

         close( fdi );
      }
   }

   return 0;
}
