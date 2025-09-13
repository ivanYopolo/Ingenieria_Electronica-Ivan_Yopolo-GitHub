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

#include "includes.h"

int main(){
   int menuSelect = 0;
   Nodo_t *startNode = malloc( sizeof(Nodo_t) );
   
   startNode->nextNode = NULL;
   startNode->prevNode = NULL;
   
   printf( "#######################################################################\n"
           "Bienvenida/o al inventario de equipamiento médico.\n"
           "Por favor, seleccione una opción para continuar.\n"
           "#######################################################################\n" );

   do{
      menuSelect = menu();
      
      if ( menuSelect > 1 ){
         // Crea un nuevo nodo, lo carga con datos y lo agrega a la lista.
         Nodo_t *newNode = getUserInput( &startNode );
      }

      switch ( menuSelect ){
         case 1:
            cargarDatos(  );
         break;
         
         case 2:
            modificarDatos( startNode );
         break;
         
         case 3:
            guardarDatos(  );
         break;
         
         case 4:
            // Ver opción de inserción ordenada.
            ordenarDatos( startNode );
         break;
         
         case 5:
            mostrarDatos( startNode );
         break;
         
         case 6:
            mostrarFecha(  );
         break;
      }
   }while ( menuSelect > 1 ); // Sale del programa.
   
   return 0;
}