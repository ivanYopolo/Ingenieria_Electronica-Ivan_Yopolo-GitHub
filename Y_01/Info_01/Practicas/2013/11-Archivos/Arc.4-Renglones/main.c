/* # Archivos.4 #
 * Contar N° de renglones de un
 * archivo de texto
 *
 * Comando: gcc -Wall --pedantic-errors main.c
 */

#include "includes.h"


int main( int argc, char *argv[] ){


   if ( argc == 2 ){

      int fdi = open( argv[ 1 ], O_RDONLY );

      int renglones = contarRenglones( fdi );

      mostrarResultados( renglones );

      close( fdi );
   }else{

      printf( "\n[ ERROR: NÚMERO DE ARGUMENTOS INVÁLIDO. ]\n\n" );
   }

   return 0;
}
