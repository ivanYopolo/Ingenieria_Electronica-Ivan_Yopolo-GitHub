/* ### Ej. Integrador + REDES ###
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
 *
 * # CONSIGNA ADICIONAL #
 * Se agregan 2 opciones:
   - Cargar datos remotamente.
   - Guardar datos remotamente.
 * En cada opción, se comunica el programa cliente con el servidor
 * en 1 de 2 puertos distintos; cada puerto se asocia o a CARGAR
 * (leer) o a GUARDAR datos remotamente. Los procesos del mismo archivo
 * se manejan con "fork()".
 */

#include "./includes/Equipamiento_medico/client/funciones_cliente.h"

/* # Comando #
clear; gcc -Wall --pedantic-errors main_client.c \
./includes/debugging.c \
./includes/Equipamiento_medico/client/funciones_cliente.c \
./includes/GetString_console/getstring-lib.c \
./includes/Manejo_Listas/Doble/lista_doble-lib.c \
./includes/Sockets/sock-lib.c \
-o client.bin
*/
   
/*
 * # ordenamiento[2] #
 * [0]: Dato a ordenar.
 * [1]: Sentido de ordenamiento.
*/

// addrStr/argv: IP + PORT_RD + PORT_WR
int main( int argc, char *argv[] ) {
// int main( ) {
   int      menuSelect = 0;                           // Selección del menú.
   int      modeShow = 0;
   int      ordenamiento[2] = { ORD_ESP, ORD_ASC };   // Tipo de ordenamiento a realizar.
   int      (*criterio_orden[3])( Nodo_t *backNode, Nodo_t *frontNode, int orden ) = 
               { orden_especialidad, orden_precio, orden_disponibilidad };    // Array de funciones para ordenamiento.
   
   // Formato: DD/MM/YYYY.
   char     *fechaTempStr = NULL;      // String de fecha del tiempo actual.
   Nodo_t   *startNode = NULL;
   
   /* Array de 2 direcciones (los espacios se cambian por \0): 
    * [0]: IP + PORT_RD.
    * [1]: IP + PORT_WR.
    */
   char     ***addrStr = NULL;
   
   addrStr               = (char ***) malloc( 2 * sizeof (char **) );         // Nivel: ARRAY DE 2 ARRAY DE 2 STRINGS.
   
   *addrStr              = (char **)  malloc( 2 * sizeof (char *) );          // Nivel: ARRAY A DE 2 STRINGS.
   *(*addrStr)           = (char *)   malloc( SIZE_IP   * sizeof (char) );    // Nivel: STRING (IP).
   *(*addrStr + 1)       = (char *)   malloc( SIZE_PROT * sizeof (char) );    // Nivel: STRING (PORT_RD).
   
   *(addrStr + 1)        = (char **)  malloc( 2 * sizeof (char *) );          // Nivel: ARRAY B DE 2 STRINGS.
   *(*(addrStr + 1))     = (char *)   malloc( SIZE_IP   * sizeof (char) );    // Nivel: STRING (IP).
   *(*(addrStr + 1) + 1) = (char *)   malloc( SIZE_PROT * sizeof (char) );    // Nivel: STRING (PORT_WR).
   
   
   switch ( argc ) {
      case 1:  // Hay IP, faltan puertos.
         strcpy( *(*addrStr), argv[0] );                    // IP
         strcpy( **(addrStr + 1), argv[0] );                // IP
         sprintf( *(*addrStr + 1), "%d", PORT_RD );         // PORT_RD
         sprintf( *(*(addrStr + 1) + 1), "%d", PORT_WR );   // PORT_WR
      break;
      
      
      case 2:  // Hay IP, falta 1 puerto.
         strcpy( *(*addrStr), argv[0] );                    // IP
         strcpy( **(addrStr + 1), argv[0] );                // IP
         strcpy( *(*addrStr + 1), argv[1] );                // PORT_RD
         sprintf( *(*(addrStr + 1) + 1), "%d", PORT_WR );   // PORT_WR
      break;
      
      
      case 3:  // Hay IP + PORT_RD + PORT_WR.
         strcpy( *(*addrStr), argv[0] );           // IP
         strcpy( **(addrStr + 1), argv[0] );       // IP
         strcpy( *(*addrStr + 1), argv[1] );       // PORT_RD
         strcpy( *(*(addrStr + 1) + 1, argv[2] );  // PORT_WR
      break;
      
      
      default:
         printf( "\n[ ERROR: FALTA IP + PUERTO. ]\n\n" );
         return 1;
   }
   

   printf( "###########################################################################\n"
           "Bienvenida/o al inventario de equipamiento médico.\n"
           "Por favor, seleccione una opción para continuar.\n"
           "###########################################################################\n" );
   
   do {
      menuSelect = menu();
      
      if ( menuSelect > 0 ) {
         system( "clear" );
         
         switch ( menuSelect ) {
            case 1:  // ABM de datos.
               altas_bajas_modificaciones( &startNode, ordenamiento[1], (criterio_orden[ordenamiento[0]]) );
            break;
            
            case 2:  // Carga datos desde un archivo (LOCAL).
               fechaTempStr = cargar_datos( &startNode, ordenamiento[1], (criterio_orden[ordenamiento[0]]) );
            break;
            
            case 3:  // Guarda datos en un archivo (LOCAL).
               guardar_datos( startNode, fechaTempStr );
            break;
            
            case 4:  // Carga datos desde un archivo (REMOTO).
               fechaTempStr = cargar_datos_remoto( argc, addrStr[0], &startNode, ordenamiento[1], (criterio_orden[ordenamiento[0]]) );
            break;
            
            case 5:  // Guarda datos en un archivo (REMOTO).
               guardar_datos_remoto( argc, addrStr[1], startNode, fechaTempStr );
            break;
            
            case 6:  // Ordena datos según criterio.
               ordenar_datos( &startNode, ordenamiento, criterio_orden );
            break;
            
            case 7:  // Mostrar TODOS los datos.
               modeShow = 0;
               mostrar_datos( startNode, modeShow );
            break;
            
            case 8:  // Muestra los datos de una determinada ESPECIALIDAD.
               modeShow = 1;
               mostrar_datos( startNode, modeShow );
            break;
            
            case 9:  // Muestra la fecha actual o del archivo.
               fechaTempStr = mostrar_fecha( fechaTempStr );
            break;
         }  // Switch de elección de opción del menú.
      }  // Checkeando que no termine el programa.
   } while ( menuSelect > 0 ); // Sale del programa.
   
  
   // # Cierre de archivos y liberación de memoria #
   close_session( startNode, fechaTempStr );
   
   
   return 0;
}

