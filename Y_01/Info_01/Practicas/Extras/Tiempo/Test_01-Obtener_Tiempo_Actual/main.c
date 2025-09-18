/* # Comando #
 * clear; gcc -Wall --pedantic-errors main.c -o prog.bin
 */
#include <stdio.h>
#include <time.h>

int main(){
   // Obtiene el tiempo actual en segundos desde EPOCH (01/01/1970).
   // Tiempo en UTC.
   time_t tiempoTemp = time( NULL );  
   
   // Estructura que incluye elementos como segundos, minutos, horas, día del mes, mes, año, etc.
   struct tm *fechaTemp = NULL;

   // #############################################################################################
   
   // Ajuste de UTC - 3 (CABA, Argentina).
   tiempoTemp -= (3 * 3600);
   
   fechaTemp = localtime( &tiempoTemp );
   
   // Empieza desde mes 0.
   fechaTemp->tm_mon++;
   
   // Toma 1900 como año 0.
   fechaTemp->tm_year += 1900;
   
   printf(  "\n[ La fecha es:\t%02d/%02d/%d ]\n"
            "[ El tiempo es:\t%02d:%02d:%02d ]\n", 
            fechaTemp->tm_mday, fechaTemp->tm_mon, fechaTemp->tm_year,
            fechaTemp->tm_hour, fechaTemp->tm_min, fechaTemp->tm_sec );
}