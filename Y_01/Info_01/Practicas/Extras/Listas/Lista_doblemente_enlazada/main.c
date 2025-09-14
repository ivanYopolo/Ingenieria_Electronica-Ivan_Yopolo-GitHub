/* # Lista DOBLEMENTE enlazada #
 * # Opciones MENÚ #
 * Cargar base de datos.
 * Realizar ABM (altas-bajas-modificaciones) del equipamiento.
   * ABM: Agregar (altas), eliminar (bajas) o modificar REGISTROS/DATOS.
 * Guardar base de datos con nombre.
 * Ordenar los elementos por especialidad, precio o disponibilidades.
 * Mostrar todos los elementos de una determinada especialidad.
 * Mostrar la fecha de la base de datos.
 *
 * Cada NODO de la lista va a ser un SKU de equipamiento.
 * Los IDs se repiten si los SKUs también se repiten.
 *
 * El campo id será asignado en forma dinámica por el programa; 
 * mientras que el resto de la información deberá ser 
 * proporcionada por el usuario.
 * 
 * # Especialidades #
 * Cardiología.
 * Clínica.
 * Gastroenterología.
 * Cirugía. 
 * Dermatología. 
 * Oftalmología.
 * Traumatología.
 *
 * # IMPORTANTE #
 * Los primeros 11 Bytes del archivo deberán indicar 
 * la fecha de la base de datos en el siguiente formato: DD/MM/YYYY.
 */

// Comando: gcc -Wall --pedantic-errors main.c funciones.c -o prog.bin

#include "includes.h"

int main(){
   int menuSelect = 0;
   int ordenamiento = ORD_ESP;
   // char *fechaTemp = NULL;  
   time_t tiempoTemp = time( NULL );  
   struct tm *fechaTemp = NULL;
   // Ver fecha actual por "time.h".
   // Formato: DD/MM/YYYY.
   
   /*
   Nodo_t *startNode = malloc( sizeof(Nodo_t) );
   startNode->nextNode = NULL;
   startNode->prevNode = NULL;
   */
   printf( "#######################################################################\n"
           "Bienvenida/o al inventario de equipamiento médico.\n"
           "Por favor, seleccione una opción para continuar.\n"
           "#######################################################################\n" );

   /*
   do{
      menuSelect = menu();
      
      if ( menuSelect > 1 ){
         // Crea un nuevo nodo, lo carga con datos y lo agrega a la lista.
         Nodo_t *newNode = getUserInput( &startNode );
      }

      switch ( menuSelect ){
         case 1:
            fechaTemp = cargarDatos( startNode );
         break;
         
         case 2:
            modificarDatos( startNode );
         break;
         
         case 3:
            guardarDatos( startNode );
         break;
         
         case 4:
            // Ver opción de inserción ordenada.
            // Pensar en puntero a función.
            ordenamiento = ordenarDatos( startNode, ordenamiento );
         break;
         
         case 5:
            mostrarDatos( startNode );
         break;
         
         case 6:
            mostrarFecha( fechaTemp );
         break;
      }
      
   }while ( menuSelect > 1 ); // Sale del programa.
   */
   
   tiempoTemp -= (3 * 3600.00);
   
   fechaTemp = localtime( &tiempoTemp );
   
   
   // fechaTemp->tm_gmtoff -= (3 * 3600.00);
   
   printf(  "\n[ La fecha es:\t%02d/%02d/%d ]\n"
            "[ El tiempo es:\t%02d:%02d:%02d ]\n", 
            fechaTemp->tm_mday, fechaTemp->tm_mon + 1, fechaTemp->tm_year + 1900,
            fechaTemp->tm_hour, fechaTemp->tm_min, fechaTemp->tm_sec );
   
   // # Cierre de archivos y liberación de memoria #
   
   return 0;
}