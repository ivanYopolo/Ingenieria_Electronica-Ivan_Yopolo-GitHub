/* # Archivos.6 #
 * Volcar en un archivo binario los contenidos
 * de un array de estructuras.
 *
 * Comando: gcc -Wall --pedantic-errors main.c -o prog.bin
 */

#include "includes.h"

int main(){
   Data_t *datosPoblacion = malloc( sizeof(Data_t) );
   Data_t *datoX = NULL;
   int tamPoblacion = 1;

   do{
      // Nuevo dato a ingresar.
      datoX = getUserInput();

      if ( datoX != NULL ){
         // Nuevo ciudadano ingresado.
         datosPoblacion = realloc( datosPoblacion, tamPoblacion * sizeof(Data_t) );
         datosPoblacion[ tamPoblacion - 1 ] = *datoX;
         tamPoblacion++;
      }else{
         // Terminó el ingreso de datos.
         // A
      }
   }while ( datoX != NULL );

   // Carga datos al archivo.
   saveFileArrStruct( datosPoblacion, tamPoblacion );

   // Libera memoria.
   freeData( datosPoblacion, tamPoblacion );

   return 0;
}
