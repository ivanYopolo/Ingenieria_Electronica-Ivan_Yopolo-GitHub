/* # Lista DOBLEMENTE enlazada #
 * ### Ídem con sockets para cargar y guardar datos en servidor ###
 * # Opciones MENÚ #
   - Realizar ABM (altas-bajas-modificaciones) del equipamiento.
      + ABM: Agregar (altas), eliminar (bajas) o modificar REGISTROS/DATOS.
   - Cargar base de datos LOCAL.
   - Cargar base de datos EN SERVIDOR.
   - Guardar base de datos con nombre LOCAL.
   - Guardar base de datos con nombre EN SERVIDOR.
   - Ordenar los elementos por especialidad, precio o disponibilidades.
   - Mostrar todos los elementos de una determinada especialidad.
   - Mostrar la fecha de la base de datos.
 *
 * Cada NODO de la lista va a ser un SKU de equipamiento.
 * Los IDs se repiten si los SKUs también se repiten.
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

/* Comando: clear; gcc -Wall --pedantic-errors main.c \
            ./includes/Equipamiento_medico/funciones.c \
            ./includes/GetString_console/getstring-lib.c \
            ./includes/Manejo_Listas/Doble/lista_doble-lib.c -o prog.bin
*/
#include "./includes/Equipamiento_medico/funciones.h"
   
/*
 * # ordenamiento[2] #
 * [0]: Dato a ordenar.
 * [1]: Sentido de ordenamiento.
*/

int main() {
   int      menuSelect = 0;                           // Selección del menú.
   int      modeShow = 0;
   
   int      ordenamiento[2] = { ORD_ESP, ORD_ASC };   // Tipo de ordenamiento a realizar.
   int      (*criterio_orden[3])( Nodo_t *backNode, Nodo_t *frontNode, int orden ) = 
               { orden_especialidad, orden_precio, orden_disponibilidad };    // Array de funciones para ordenamiento.
   
   // Formato: DD/MM/YYYY.
   char     *fechaTempStr = NULL;      // String de fecha del tiempo actual.
   
   // Nodo_t   *nodoX = NULL;
   Nodo_t   *startNode = NULL;
   

   printf( "###########################################################################\n"
           "Bienvenida/o al inventario de equipamiento médico.\n"
           "Por favor, seleccione una opción para continuar.\n"
           "###########################################################################\n" );

   do {
      menuSelect = menu();
      
      if ( menuSelect > 0 ) {
         switch ( menuSelect ) {
            case 1:  // Carga datos desde un archivo.
               fechaTempStr = cargar_datos( &startNode, ordenamiento[1], (*criterio_orden[ordenamiento[0]]) );
            break;
            
            case 2:  // ABM de datos.
               altas_bajas_modificaciones( &startNode, ordenamiento[1], (*criterio_orden[ordenamiento[0]]) );
            break;
            
            case 3:  // Guarda datos en un archivo.
               guardar_datos( startNode, fechaTempStr );
            break;
            
            case 4:  // Ordena datos según criterio.
               ordenar_datos( &startNode, ordenamiento, &(*criterio_orden) );
            break;
            
            case 5:  // Mostrar TODOS los datos.
               modeShow = 0;
               mostrar_datos( startNode, modeShow );
            break;
            
            case 6:  // Muestra los datos de una determinada ESPECIALIDAD.
               modeShow = 1;
               mostrar_datos( startNode, modeShow );
            break;
            
            case 7:  // Muestra la fecha actual o del archivo.
               fechaTempStr = mostrar_fecha( fechaTempStr );
            break;
         }
      }
   } while ( menuSelect > 0 ); // Sale del programa.
   
  
   // # Cierre de archivos y liberación de memoria #
   close_session( startNode, fechaTempStr );
   
   return 0;
}

