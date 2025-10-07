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
 
/* Comando: gcc -Wall --pedantic-errors main.c \
            ./includes/Equipamiento_medico/funciones.c \
            ./includes/GetString_console/getstring-lib.c \
            ./includes/Manejo_Listas/Doble/lista_doble-lib.c -o prog.bin
*/

#include "funciones.h"


// ########################################################
// ### Menú ###
// ########################################################

//------------------------------------------------------------------------
// menu - [ DONE ]
//------------------------------------------------------------------------
int menu() {
   int menuSelect = 0;

   printf( "\n###########################################################################\n\n"
           "1) Cargar datos desde una base de datos.\n"
           "2) Agregar, quitar o modificar datos.\n" 
           "3) Guardar cambios de la base de datos.\n" 
           "4) Ordenar los elementos por especialidad, precio o disponibilidades.\n" 
           "5) Mostrar todos los elementos cargados.\n"
           "6) Mostrar todos los elementos de una determinada especialidad.\n" 
           "7) Mostrar la fecha de una base de datos.\n" );

   do{
      printf( "\nOpción (0 o negativo para finalizar):\t\t" );
      
      better_scanf( "%d", &menuSelect );
      /*
      scanf( "%d", &menuSelect );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      */
   }while ( menuSelect > 7 );
   
   return menuSelect;
}


// ########################################################
// ### Manejo de nodos ###
// ########################################################

//------------------------------------------------------------------------
// get_user_input - [ DONE ]
//------------------------------------------------------------------------
/* Carga en un nodo según input del usuario:
    * SKU.
    * Descripción.
    * Detalles.
    * Cantidad (stock).
    * Especialidad.
    * Precio.
 *
 */
void get_user_input( Nodo_t **startNode, int sentido, \
                     int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) ) {
   int      allowInput = 1;
   int      sku = 1;
   int      stock = 1;
   int      especialidadTemp = 1;
   float    precioTemp = 1; 
   char     especialidadStr[7][20] = 
            { "Cardiología", "Clínica", "Gastroenterología", "Cirugía", "Dermatología", "Oftalmología", "Traumatología" };
   Nodo_t   *newNode = NULL;
   
   // # LOG #
   int      fdLog = 0;
   fdLog = open( "./log/get_user_input.log", O_WRONLY | O_CREAT | O_TRUNC, 0666 );
   
   do {  // Repetición de función.
      Dato_t newData;
   
      dprintf( fdLog, "### Creando dato... ###\n" );
      
      printf( "Ingrese los datos del producto en forma ordenada:\n" );
      
      // # SKU #
      do {
         printf( "* SKU:        \t\t" );
         
         better_scanf( "%d", &sku );
         /*
         scanf( "%d", &sku );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( sku < 1 )
            printf( "[ SKU INVÁLIDO. INTENTE NUEVAMENTE. ]\n\n" );
      } while ( sku < 1 );
      newData.sku = sku;
      // # LOG #
      dprintf( fdLog, "* SKU:        \t\t%d\n", sku );
      
      
      // # Descripción #
      printf( "* Descripción:\t\t" );
      write_str( newData.descripcion, TAM_DESC );
      
      // # LOG #
      dprintf( fdLog, "* Descripción:\t\t%s\n", newData.descripcion );
      
      
      // # Detalles #
      printf( "* Detalles:   \t\t" );
      write_str( newData.detalles, TAM_DESC );
      
      // # LOG #
      dprintf( fdLog, "* Detalles:   \t\t%s\n", newData.detalles );
      
      
      // # Cantidad (stock) #
      do {
         printf( "* Cantidad en stock:\t" );
         
         better_scanf( "%d", &stock );
         /*
         scanf( "%d", &stock );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( stock < 1 )
            printf( "[ STOCK INVÁLIDO. INTENTE NUEVAMENTE. ]\n\n" );
      } while ( stock < 1 );
      newData.cantidad = stock;
      // # LOG #
      dprintf( fdLog, "* Stock:   \t\t%d\n", stock );
      
      
      // # Especialidad #
      do {
         printf( "* # Especialidad #\n" );
         for ( int i = 0; i < TRAUMATOLOGIA; i++ ) {
            printf( "   %d) %s.\n", i + 1, especialidadStr[i] );
         }
         printf( "Opción:\t" );
         
         better_scanf( "%d", &especialidadTemp );
         /*
         scanf( "%d", &especialidadTemp );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( especialidadTemp < 1 || especialidadTemp > 7 )
            printf( "[ ESPECIALIDAD INVÁLIDA. INTENTE NUEVAMENTE. ]\n\n" );
      } while ( especialidadTemp < 1 || especialidadTemp > 7 );
      newData.especialidad = especialidadTemp;
      // # LOG #
      dprintf( fdLog, "* Especialidad:   \t%s\n", especialidadStr[especialidadTemp - 1] );
      
      
      // # PRECIO #
      do {
         printf( "* Precio:   \t\t" );
         better_scanf( "%f", &precioTemp );
         /*
         scanf( "%f", &precioTemp );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( precioTemp < 0 )
            printf( "[ PRECIO INVÁLIDO. INTENTE NUEVAMENTE. ]\n\n" );
      } while ( precioTemp < 0 );
      newData.precio = precioTemp;
      // # LOG #
      dprintf( fdLog, "* Precio:   \t\t%.02f\n", precioTemp );
      
      
      // # LOG #
      dprintf( fdLog, "### Dato cargado con éxito. ###\n" );
      
      
      // Carga todo a un nuevo nodo.
      if ( *startNode == NULL ) {         // Caso particular: primer dato.
         *startNode = create_node( newData );
         newNode = *startNode;
      } else {                            // Caso general.
         newNode = create_node( newData );
         // Agrega nodo a la lista (inserción ordenada).
         ordered_insertion( startNode, newNode, sentido, criterio_orden );
      }
      
      // # LOG #
      dprintf( fdLog, "[ Nodo creado:\t%p ]\n", (void *) newNode );
      dprintf( fdLog, "--------------------------------------------------------------\n" );
      
      printf( "\n" );
      
      do {
         printf( "# ¿Desea continuar registrando equipamiento? #\n"
                 "1) Sí.\n" 
                 "0) No.\n" 
                 "Opción: \t" );
         better_scanf( "%d", &allowInput );
         /*
         scanf( "%d", &allowInput );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( allowInput != 1 && allowInput != 0 )
            printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
      } while ( allowInput != 1 && allowInput != 0 );
      
   } while ( allowInput == 1 );  
   // Terminó de registrar datos.
   
   // # LOG #
   close( fdLog );
}


//------------------------------------------------------------------------
// modificar_datos - [ REV ]
//------------------------------------------------------------------------
/* Modifica datos de un nodo de la lista.
 */
void modificar_datos( Nodo_t **startNode ) {
   int      seleccion = 1;
   int      allowMod = 1;
   int      skuTemp = 1;
   char     descripcionTemp[ TAM_DESC ];
   char     detallesTemp[ TAM_DET ];
   int      cantidadTemp = 1;
   int      especialidadTemp = 1;
   float    precioTemp = 1;
   int      mergeSelection = 1;
   Nodo_t   *nodoX = NULL;       // Nodo-cursor para buscarlo por SKU.
   Nodo_t   *nodoAux = NULL;     // Auxiliar por SKU repetido.

   do {  // Repetición de función.
      do {  // Selección de SKU (nodo).
         printf( "Ingrese el SKU del producto a modificar:\t" );
         
         better_scanf( "%d", &skuTemp );
         /*
         scanf( "%d", &skuTemp );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         
         if ( skuTemp < 1 ) {
            printf( "\n[ ERROR: SKU INVÁLIDO. INGRESE NUEVAMENTE EL DATO. ]\n\n" );
         } else {
            // Busca el nodo con el SKU pedido.
            if ( ( nodoX = is_SKU_repeated( *startNode, skuTemp ) ) == NULL ) // No encontró el SKU.
               printf( "\n[ NO EXISTE EQUIPAMIENTO CON EL SKU PEDIDO. INTENTE NUEVAMENTE. ]\n\n" );
         }
      } while ( skuTemp < 1 || nodoX == NULL );   
      // Registró un SKU válido.

      do {
         printf( "Elija el dato a modificar:\n"
                 "1) SKU.\n" 
                 "2) Descripción.\n" 
                 "3) Detalles.\n" 
                 "4) Cantidad.\n" 
                 "5) Especialidad.\n" 
                 "6) Precio.\n" );

         better_scanf( "%d", &seleccion );
         /*
         scanf( "%d", &seleccion );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( seleccion < 1 || seleccion > 6 )
            printf( "\n[ SELECCIÓN INVÁLIDA. ]\n\n" );
      } while ( seleccion < 1 || seleccion > 6 );
      
      switch ( seleccion ) {
         case 1:  // SKU.
            do {
               printf( "Ingrese el nuevo SKU:\t" );
               
               better_scanf( "%d", &skuTemp );
               /*
               scanf( "%d", &(skuTemp) );
               int ch = 0;
               while ( ( ch = getchar() ) != '\n' && ch != EOF );
               */
               if ( skuTemp < 1 )
                  printf( "\n[ SKU INVÁLIDO. INGRESE NUEVAMENTE EL DATO. ]\n\n" );
            } while ( skuTemp < 1 );   // Obtuvo el SKU correctamente.
            
            
            // # Chekea SKUs repetidos #
            nodoAux = is_SKU_repeated( *startNode, skuTemp );
            
            if ( nodoAux == NULL ) {         // No se repite el SKU. 
               nodoX->dato.sku = skuTemp;
            } else { 
               if ( nodoAux ==  nodoX ) {    // SKU del nodo a modificar invariante.
                  printf( "Mismo SKU; no realizó cambios.\n" );
               } else {                      // SKU repetido en otro nodo.
                  printf( "# Se detectó un dato/producto con mismo SKU #\n" );
                  
                  show_data( nodoX->dato );
                  show_data( nodoAux->dato );
                  
                  do {
                     printf( "# Elija el dato a conservar #\n" 
                             "1) Dato elegido a modificar.\n" 
                             "2) Dato guardado en el archivo.\n" 
                             "Opción:   \t" );
                     
                     better_scanf( "%d", &mergeSelection );
                     /*
                     scanf( "%d", &mergeSelection );
                     int ch = 0;
                     while ( ( ch = getchar() ) != '\n' && ch != EOF );
                     */
                     if ( mergeSelection != 1 && mergeSelection != 2 )
                        printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
                     
                  } while ( mergeSelection != 1 && mergeSelection != 2 );
               
                  // Junta datos del mismo SKU, aumenta stock.
                  merge_data( &(nodoX->dato), nodoAux->dato, mergeSelection );
               }
            }
         break;
         
         case 2:  // Descripción.
            printf( "# Ingrese la nueva descripción #\n" );
            
            descripcionTemp[ 0 ] = '\0';
            
            write_str( descripcionTemp, TAM_DESC );
            
            strncpy( nodoX->dato.descripcion, descripcionTemp, TAM_DESC );
         break;
         
         case 3:  // Detalles.
            printf( "# Ingrese los nuevos detalles #\n" );
            
            detallesTemp[ 0 ] = '\0';
            
            write_str( detallesTemp, TAM_DET );

            strncpy( nodoX->dato.detalles, detallesTemp, TAM_DET );
         break;
         
         case 4:  // Cantidad.
            do {
               printf( "# Ingrese la nueva cantidad/stock #\n" );
               
               better_scanf( "%d", &cantidadTemp );
               /*
               scanf( "%d", &cantidadTemp );
               int ch = 0;
               while ( ( ch = getchar() ) != '\n' && ch != EOF );
               */
               if ( cantidadTemp < 1 )
                  printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
               
            } while ( cantidadTemp < 1 );
            
            nodoX->dato.cantidad = cantidadTemp;
         break;
         
         case 5:  // Especialidad.
            do {
               printf( "# Ingrese la nueva especialidad #\n" );
               
               better_scanf( "%d", &especialidadTemp );
               /*
               scanf( "%d", &especialidadTemp );
               int ch = 0;
               while ( ( ch = getchar() ) != '\n' && ch != EOF );
               */
               if ( especialidadTemp < 1 || especialidadTemp > 7 )
                  printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
               
            } while ( especialidadTemp < 1 || especialidadTemp > 7 );
            
            nodoX->dato.especialidad = especialidadTemp;
         break;
         
         case 6:  // Precio.
            do {
               printf( "# Ingrese el nuevo precio #\n" );
               
               better_scanf( "%f", &precioTemp );
               /*
               scanf( "%f", &precioTemp );
               int ch = 0;
               while ( ( ch = getchar() ) != '\n' && ch != EOF );
               */
               if ( precioTemp < 1 )
                  printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
               
            } while ( precioTemp < 1 );
            
            nodoX->dato.precio = precioTemp;
         break;
      }
      
      do {
         printf( "# ¿Desea continuar modificando datos? #\n" 
                 "1) Sí.\n"
                 "0) No.\n"
                 "Opción: \t" );
         
         better_scanf( "%d", &allowMod );
         /*
         scanf( "%d", &allowMod );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( allowMod != 0 && allowMod != 1 )
            printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
         
      } while ( allowMod != 0 && allowMod != 1 );
   } while ( allowMod == 1 );
}


//------------------------------------------------------------------------
// eliminate_data - [ REV ]
//------------------------------------------------------------------------
/* Elimina datos (nodo) de la lista.
 */
void eliminate_data( Nodo_t *startNode ) {
   int      allowEliminate = 1;
   int      skuTemp = 0;
   Nodo_t   *nodoX = startNode;
   
   while ( allowEliminate == 1 && nodoX != NULL ) {   // Repetición de función.
      do {
         printf( "Ingrese el SKU del producto a eliminar:\t" );
            
         better_scanf( "%d", &skuTemp );
         /*
         scanf( "%d", &skuTemp );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( skuTemp < 0 )
            printf( "\n[ ERROR: SKU INVÁLIDO. INGRÉSELO NUEVAMENTE. ]\n\n" );
      } while ( skuTemp < 0 );
      
      if ( ( nodoX = is_SKU_repeated( startNode, skuTemp ) ) != NULL ) {
         pop_node( nodoX );
      } else {
         printf( "\n[ No se encontró el producto. ]\n\n" );
      }
      
      do {
         printf( "# ¿Desea continuar eliminando equipamiento? #\n" 
                 "1) Sí.\n" 
                 "0) No.\n" 
                 "Opción.\t" );
         
         better_scanf( "%d", &allowEliminate );
         /*
         scanf( "%d", &allowEliminate );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( allowEliminate != 1 && allowEliminate != 0 )
            printf( "\n[ ERROR: OPCIÓN INVÁLIDA. ]\n" );
      } while ( allowEliminate != 1 && allowEliminate != 0 );
   }  // Deja de eliminar datos o se vació el inventario.
   
   if ( nodoX == NULL )
      printf( "\n[ INVENTARIO VACÍO. ]\n\n" );
}


// ########################################################
// ### Especiales ###
// ########################################################

//--------------------------------------------------------------------------
// show_data - [ DONE ]
//--------------------------------------------------------------------------
/* Muestra datos de un nodo en pantalla.
 */
void show_data( Dato_t datoX ) {
   printf( "\n#########################################################\n" );
   printf( "* SKU:               \t%d\n", datoX.sku );
   printf( "* Descripción:       \t%s\n", datoX.descripcion );
   printf( "* Detalles:          \t%s\n", datoX.detalles );
   printf( "* Cantidad en stock: \t%d\n", datoX.cantidad );
   printf( "* Precio:            \t%.02f\n", datoX.precio );
   
   switch ( datoX.especialidad ){   // Imprimir según especialidad.
      case CARDIOLOGIA:
         printf( "* Especialidad:      \tCARDIOLOGÍA.\n" );
      break;
      
      case CLINICA:
         printf( "* Especialidad:      \tCLÍNICA.\n" );
      break;
      
      case GASTROENTEROLOGIA:
         printf( "* Especialidad:      \tGASTROENTEROLOGÍA.\n" );
      break;
      
      case CIRUGIA:
         printf( "* Especialidad:      \tCIRUGÍA.\n" );
      break;
      
      case DERMATOLOGIA:
         printf( "* Especialidad:      \tDERMATOLOGÍA.\n" );
      break;
      
      case OFTALMOLOGIA:
         printf( "* Especialidad:      \tOFTALMOLOGÍA.\n" );
      break;
      
      case TRAUMATOLOGIA:
         printf( "* Especialidad:      \tTRAUMATOLOGÍA.\n" );
      break;
   }
}


//--------------------------------------------------------------------------
// close_session - [ DONE ]
//--------------------------------------------------------------------------
/* Libera memoria de la lista entera y cierra el archivo.
 */
void close_session( Nodo_t *startNode, char *fechaStr ) {
   Nodo_t *nodoX = startNode;
   Nodo_t *nodoAnt = NULL;
   
   while ( nodoX != NULL ) {
      nodoAnt = nodoX;
      nodoX = nodoX->nextNode;
      free( nodoAnt );
   }
   
   if ( fechaStr != NULL )
      free( fechaStr );
}


//--------------------------------------------------------------------------
// is_SKU_repeated - [ DONE ]
//--------------------------------------------------------------------------
/* Checkea si se repite el SKU de un dato nuevo en toda la lista.
 *
 * Retorna:
   - NULL si no se repite.
   - La dirección del nodo correspondiente si es que se repite.
 */
Nodo_t * is_SKU_repeated( Nodo_t *startNode, int skuInput ) {
   Nodo_t *nodoX = NULL;
   Nodo_t *nodoAnt = NULL; // Para guardar el anterior.
   
   if ( startNode != NULL ) {
      nodoX = startNode;
      nodoAnt = nodoX;

      while ( ( nodoX != NULL ) && ( nodoX->dato.sku != skuInput ) ) {  // Escanea la lista por coincidencias.
         nodoAnt = nodoX;
         nodoX = nodoX->nextNode;
      }  // nodoX llega a NULL o al SKU deseado.
      
      if ( nodoAnt->dato.sku == skuInput ) { // Guarda la dirección del nodo en caso de coincidencia.
         nodoX = nodoAnt;
      } else {    // No se repite el SKU.
         nodoX = NULL;
         nodoAnt = NULL;
      }
   }
   
   return nodoX;
}


//--------------------------------------------------------------------------
// obtener_fecha - [ DONE ]
//--------------------------------------------------------------------------
/* Obtiene la fecha actual del sistema y lo devuelve como un string.
 * Formato: DD/MM/YYYY.
 */
char * obtener_fecha() {
   time_t      tiempoNuevo;
   struct tm   *fechaNueva = NULL;
   char        *fechaNuevaStr = NULL;

   // Fecha nueva.
   tiempoNuevo = time( NULL );
   // tiempoNuevo -= 3 * 3600;      // Ajuste UTC - 3.
   
   fechaNueva = localtime( &tiempoNuevo );
   fechaNueva->tm_mon++;         // Mes empieza en 0.
   fechaNueva->tm_year += 1900;  // Año empieza con 0 relativo en 1900.
   
   fechaNuevaStr = malloc( TAM_DATE * sizeof(char) );
   
   sprintf( fechaNuevaStr, "%02d/%02d/%d",
            fechaNueva->tm_mday, fechaNueva->tm_mon, fechaNueva->tm_year );
   
   return fechaNuevaStr;
}


// ########################################################
// ### Opciones Menú ###
// ########################################################

//------------------------------------------------------------------------
// cargar_datos - [ DONE ]
//------------------------------------------------------------------------
/* Carga datos de un archivo de base de datos en la lista.
 * NO SOBREESCRIBE LISTA, sinó que agrega nodos a la misma.
 * Si se repiten SKUs, se juntan en un NODO los datos y se suman su "stock".
 * Usar ".dat".
 *
 * Devuelve la fecha leída (DD/MM/YYYY).
 *
 * ERR: queda en:
   - dprintf( fdLog, "[ Checkeando SKUs... ]\n" );
 */
char * cargar_datos( Nodo_t **startNode, int sentido, \
                     int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) ) {
   int      fdData = 2;
   int      bytesRd = 0;
   int      mergeSelection = 0;
   char     *fechaTemp = malloc( TAM_DATE * sizeof(char) );
   Nodo_t   *nodoX = NULL;
   char     directorio[8] = "./data/";
   char     *nombreArchivo = NULL;
   char     *rutaArchivo = NULL;
   
   fechaTemp[TAM_DATE - 1] = '\0';
   
   // # LOG #
   int      fdLog = 0;
   fdLog = open( "./log/read_file.log", O_WRONLY | O_CREAT | O_TRUNC, 0666 );
   
   // ### Abre el archivo a extraer datos ###
   do {
      printf( "Ingrese el nombre del archivo a cargar información.\n"
              "Utilizar solamente archivos con extensión \'.dat\':\n" );
      
      nombreArchivo = write_str_d();
      
      if ( nombreArchivo == NULL ) {
         printf( "\n[ ERROR: NOMBRE DE ARCHIVO INVÁLIDO. ]\n\n" );
      } else {
         // Agregarle al nombre la ruta hasta "./data/" (+ 7 B).
         rutaArchivo = malloc( strlen( nombreArchivo ) + strlen( directorio ) + 1 );
         strcpy( rutaArchivo, directorio );
         strcpy( rutaArchivo + strlen( directorio ), nombreArchivo );
         rutaArchivo[strlen( nombreArchivo ) + strlen( directorio )] = '\0';
         fdData = open( rutaArchivo, O_RDONLY );
         
         if ( fdData < 1 ) {
            printf( "\n[ ERROR: NOMBRE DE ARCHIVO INVÁLIDO. ]\n\n" );
            free( nombreArchivo );
            free( rutaArchivo );
         }
      }
   } while ( fdData < 1 || nombreArchivo == NULL );
   
   // # LOG #
   dprintf( fdLog, "------------------------------------------------------------------------\n" );
   dprintf( fdLog, "### Archivo leído exitosamente ###\n" );
   dprintf( fdLog, "------------------------------------------------------------------------\n\n" );
   dprintf( fdLog, "* Ruta:\t\t%s\n", rutaArchivo );
   
   // ### Carga datos a la lista ###
   
   bytesRd = read( fdData, fechaTemp, TAM_DATE );   // Lee la fecha.
   
   if ( bytesRd == TAM_DATE ) {
   
      // # LOG #
      dprintf( fdLog, "* Fecha:\t%s\n", fechaTemp );
   
      do {  // Pasa por la lista entera.
         
         Dato_t datoInput;
         bytesRd = read( fdData, &datoInput, sizeof(Dato_t) );  // Lee 1 dato.
         
         if ( bytesRd == sizeof(Dato_t) ) {
         
            // # LOG #
            dprintf( fdLog, "[ DATO LEÍDO. ]\n" );
            show_data_log( datoInput, fdLog );
            
            // Checkea los SKUs.
            // # LOG #
            dprintf( fdLog, "[ Checkeando SKUs... ]\n" );
            
            if ( *startNode != NULL ) {   // Caso general.
               
               if ( ( nodoX = is_SKU_repeated( *startNode, datoInput.sku ) ) != NULL ) { // SKU repetido.
                  printf( "Se detectaron los siguientes datos con el mismo SKU:\n" );
                  dprintf( fdLog, "[ SKUs REPE. ]\n" );
               
                  show_data( nodoX->dato );
                  
                  show_data( datoInput );
                  
                  do {
                     printf( "# Elija el dato a conservar #\n" 
                             "1) Dato ya creado en el programa.\n" 
                             "2) Dato guardado en el archivo.\n" 
                             "Opción:   \t" );
                     
                     better_scanf( "%d", &mergeSelection );
                     /*
                     scanf( "%d", &mergeSelection );
                     int ch = 0;
                     while ( ( ch = getchar() ) != '\n' && ch != EOF );
                     */
                     if ( mergeSelection != 1 && mergeSelection != 2 )
                        printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
                     
                  } while ( mergeSelection != 1 && mergeSelection != 2 );
               
                  // Junta datos del mismo SKU, aumenta stock.
                  merge_data( &(nodoX->dato), datoInput, mergeSelection );
                  
               } else { // No se repite el SKU.
                  // # LOG #
                  dprintf( fdLog, "[ SKUs NO repe. ]\n" );
                  
                  nodoX = create_node( datoInput );     // Agrega un dato a la lista.
                  // # LOG #
                  dprintf( fdLog, "[ Creando nodo... ]\n" );
                  
                  push_node( *startNode, nodoX, (*startNode)->nextNode );
                  sort_list( startNode, sentido, (criterio_orden) );
                  // ordered_insertion( startNode, nodoX, sentido, (criterio_orden) );
                  // # LOG #
                  dprintf( fdLog, "[ Insertado ordenadamente de manera exitosa. ]\n" );
               }
               
            } else {          // Lista vacía.
               // # LOG #
               dprintf( fdLog, "[ SKUs NO repe. ]\n" );
               
               nodoX = create_node( datoInput );     // Agrega un dato a la lista.
               // # LOG #
               dprintf( fdLog, "[ Creando nodo... ]\n" );
               
               push_node( *startNode, nodoX, (*startNode)->nextNode );
               sort_list( startNode, sentido, (criterio_orden) );
               // ordered_insertion( startNode, nodoX, sentido, (criterio_orden) );
               // # LOG #
               dprintf( fdLog, "[ Insertado ordenadamente de manera exitosa. ]\n" );
            }
         }
      } while ( bytesRd == sizeof(Dato_t) );  
      // Terminó de leer el archivo.

      printf( "\n[ Lectura exitosa. ]\n\n" );
      
      // # LOG #
      dprintf( fdLog, "\n[ Lectura exitosa. ]\n"
                      "------------------------------------------------------------------------\n" );
      
   } else {    // N° de Bytes leídos menor a la fecha.
      printf( "\n[ ARCHIVO VACÍO. ]\n\n" );
      
      // # LOG #
      dprintf( fdLog, "\n[ ARCHIVO VACÍO. ]\n"
                      "------------------------------------------------------------------------\n" );
   }
   
   free( nombreArchivo );
   free( rutaArchivo );
   close( fdData );
   
   // # LOG #
   close( fdLog );
   
   return fechaTemp;
}


//------------------------------------------------------------------------
// altas_bajas_modificaciones (ABM) - [ REV ]
//------------------------------------------------------------------------
/* Agrega (alta), saca (baja) o modifica datos de la lista.
 * # ordenamiento[2] #
 * [0]: Dato a ordenar.
 * [1]: Sentido de ordenamiento.
 */
void altas_bajas_modificaciones( Nodo_t **startNode, int sentido, \
                                 int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) ) {
   int seleccion = 1;
   
   if ( *startNode == NULL ) { // Caso particular: lista vacía.
      // Pasa el criterio para ordenar según diga el main().
      get_user_input( startNode, sentido, (criterio_orden) );
      
   } else { // Caso general.
      do {  // Repetición de la función.
         do {
            printf( "### Elija una opción ###\n" 
                    "1) Agregar datos al inventario.\n"
                    "2) Sacar datos del inventario.\n"
                    "3) Modificar datos del inventario.\n"
                    "Opción:\t\t" );
            better_scanf( "%d", &seleccion );
            /*
            scanf( "%d", &seleccion );
            int ch = 0;
            while ( ( ch = getchar() ) != '\n' && ch != EOF );
            */
            if ( seleccion < 1 || seleccion > 3 )
               printf( "\n[ ERROR: OPCIÓN INVÁLIDA. ]\n\n" );
         } while ( seleccion < 1 || seleccion > 3 );
         
         switch ( seleccion ) {
            case 1:  // Alta.
               get_user_input( startNode, sentido, (criterio_orden) );
            break;
            
            case 2:  // Baja.
               eliminate_data( *startNode );
            break;
            
            case 3:  // Mod.
               modificar_datos( startNode );
            break;
         }
         
         do {
            printf( "### ¿Desea continuar agregando, quitando o modificando datos? ###\n" 
                    "1) Sí.\n"
                    "0) No.\n"
                    "Opción: \t" );
            
            better_scanf( "%d", &seleccion );
            /*
            scanf( "%d", &seleccion );
            int ch = 0;
            while ( ( ch = getchar() ) != '\n' && ch != EOF );
            */
            if ( seleccion != 1 && seleccion != 0 )
               printf( "\n[ ERROR: OPCIÓN INVÁLIDA. ]\n\n" );
            
         } while ( seleccion != 1 && seleccion != 0 );
         
      } while ( seleccion == 1 );   // Sale si no quiere continuar haciendo ABM.
   }  // Termina caso general.
}  // Termina función.


//------------------------------------------------------------------------
// guardar_datos - [ DONE ]
//------------------------------------------------------------------------
/* Guarda la lista entera en un archivo de base de datos.
 * Usar '.dat'.
 */
void guardar_datos( Nodo_t *startNode, char *fechaAct ) { 
   int      fdData = 0;
   char     *nombreArchivo = NULL;
   char     *rutaArchivo = NULL;
   char     directorio[8] = "./data/";
   int      sobreescribir = 0;
   Nodo_t   *nodoX = NULL;
   
   // # LOG #
   int      fdLog;
   fdLog = open( "./log/guardar_datos.log", O_WRONLY | O_TRUNC | O_CREAT, 0666 );
   dprintf( fdLog, 
            "------------------------------------------------------------------------\n"
            "Guardando datos...\n"
            "------------------------------------------------------------------------\n\n" );
   
   if ( startNode != NULL ) {
      do{   // Verificar nombre del archivo por input del usuario.
         printf( "Elija un nombre para el archivo a guardar los datos + .dat:\t" );
         nombreArchivo = write_str_d();
         
         // # LOG #
         dprintf( fdLog, "* Nombre obtenido\t %s \n", nombreArchivo );
         
         if ( nombreArchivo == NULL ) {
            printf( "\n[ ERROR: INGRESE UN NOMBRE VÁLIDO. ]\n\n" );
            
         } else { // Evaluar nombres repetidos.
            dprintf( fdLog, "* Nombre archivo:\t%s\n", nombreArchivo );
            
            // Agregarle al nombre la ruta hasta "./data/" (+ 7 B).
            rutaArchivo = malloc( strlen( nombreArchivo ) + strlen( directorio ) + 1 );
            strcpy( rutaArchivo, directorio );
            strcpy( rutaArchivo + strlen( directorio ), nombreArchivo );
            rutaArchivo[strlen( nombreArchivo ) + strlen( directorio )] = '\0';
            
            // # LOG #
            dprintf( fdLog, "* Ruta:\t\t%s \n", rutaArchivo );
            
            if ( ( fdData = open( rutaArchivo, O_RDONLY ) ) > 1 ) {   // Repetido
            // if ( ( fdData = open( nombreArchivo, O_RDONLY ) ) > 1 ) {   // Repetido
               
               // # LOG #
               dprintf( fdLog, "* Sobreescritura\t=\t" );
               
               do {
                  printf( "\nExiste un archivo con el mismo nombre, ¿desea sobreescibirlo?\n"
                          "1) Sí.\n"
                          "2) No.\n" 
                          "Opción:\t" );
                  
                  better_scanf( "%d", &sobreescribir );
                  /*
                  scanf( "%d", &sobreescribir );
                  int ch = 0;
                  while ( ( ch = getchar() ) != '\n' && ch != EOF );
                  */
                  if ( sobreescribir != 1 && sobreescribir != 2 )
                     printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n" );
               } while ( sobreescribir != 1 && sobreescribir != 2 );
               
               
               switch ( sobreescribir ) {
                  case 1:  // Sobreescritura.
                     // # LOG #            
                     dprintf( fdLog, "1\n" );
                     
                  break;
               
                  case 2:  // Vuelve a elegir el nombre del archivo.
                     // # LOG #
                     dprintf( fdLog, "0\n" );
                     
                     free( nombreArchivo );
                     free( rutaArchivo );
                     fdData = 0;
                     close( fdData );
                  break;
               }  // Switch de sobreescritura.
            }  // Evaluación nombres repetidos.
            
         }
      // fdData < 0: NO existe el archivo o no se pudo abrir.
      // fdData >= 1: EXISTE el archivo y se ABRIÓ.
      } while ( nombreArchivo == NULL || rutaArchivo == NULL || fdData >= 1 ); 
      // Nombró correctamente el archivo.
      
      fdData = open( rutaArchivo, O_WRONLY | O_CREAT | O_TRUNC, 0666 );
      // fdData = open( nombreArchivo, O_WRONLY | O_CREAT | O_TRUNC, 0666 );
      
      // Escribe la fecha actual en formato "DD/MM/YYYY".
      if ( fechaAct == NULL ) {
         fechaAct = obtener_fecha();
      }
      
      write( fdData, fechaAct, TAM_DATE );
      
      // # LOG #
      dprintf( fdLog, "* Fecha:\t%s\n", fechaAct );
      dprintf( fdLog, "* Datos:\n" );
      
      // Guarda TODOS los DATOS en un archivo.
      nodoX = startNode;
      while ( nodoX != NULL ) {
         // # LOG #
         show_data_log( nodoX->dato, fdLog );
         
         write( fdData, &(nodoX->dato), sizeof(Dato_t) );
         nodoX = nodoX->nextNode; 
      }  // Terminó de guardar los datos.
      
      close( fdData );
      free( nombreArchivo );
      free( rutaArchivo );
   } else {
      printf( "\n[ ERROR: INVENTARIO VACÍO. ]\n\n" );
   }

   // # LOG #
   close( fdLog );
}


//------------------------------------------------------------------------
// ordenar_datos - [ ERR ] (Segmentation Fault).
//------------------------------------------------------------------------
/* Ordenar los elementos por:
   * Especialidad.
   * Precio.
   * Disponibilidades.
 *
 * Ordenamiento: array de ints (2 pos):
   * 0: Dato a ordenar.
   * 1: Sentido de ordenamiento.
 */
void ordenar_datos( Nodo_t **startNode, int ordenamiento[], \
                    int (*criterio_orden[3])( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) ) {
   int datoDeOrdenamiento = 0;
   int sentidoOrdenamiento = 0;
   
   if ( *startNode == NULL ) {
      printf( "\n[ ERROR: INVENTARIO VACÍO. ]\n\n" );
   } else {
      // Tipo de dato a ordenar.
      do{
         printf( 
         "\n# Seleccione con qué dato ordenar el inventario #\n" 
         "1) Especialidad.\n" 
         "2) Precio.\n" 
         "3) Disponibilidad (stock).\n" );
         
         better_scanf( "%d", &datoDeOrdenamiento );
         /*
         scanf( "%d", &datoDeOrdenamiento );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( datoDeOrdenamiento > 3 || datoDeOrdenamiento < 1 )
            printf( "\n[ ERROR: INGRESE UNA OPCIÓN VÁLIDA. ]\n" );
      } while ( datoDeOrdenamiento > 3 || datoDeOrdenamiento < 1 );
      
      ordenamiento[0] = datoDeOrdenamiento;
      
      // Sentido de ordenamiento.
      do{
         printf( 
         "\n# Seleccione el sentido del ordenamiento #\n" 
         "1) Ascendente.\n" 
         "2) Descendente.\n" );
         
         better_scanf( "%d", &sentidoOrdenamiento );
         /*
         scanf( "%d", &sentidoOrdenamiento );
         int ch = 0;
         while ( ( ch = getchar() ) != '\n' && ch != EOF );
         */
         if ( sentidoOrdenamiento > 2 || sentidoOrdenamiento < 1 )
            printf( "\n[ ERROR: INGRESE UNA OPCIÓN VÁLIDA. ]\n" );
      } while ( sentidoOrdenamiento > 2 || sentidoOrdenamiento < 1 );
      
      ordenamiento[1] = sentidoOrdenamiento;
      
      // Ordenamiento en sí mismo.
      sort_list( startNode, ordenamiento[1], (criterio_orden[ordenamiento[0]]) );
   }
}


//------------------------------------------------------------------------
// mostrar_datos - [ DONE ]
//------------------------------------------------------------------------
/* Mostrar todos los elementos de una determinada especialidad.
 * Mode:
   - 0: mostrar TODO.
   - != 0: mostrar por especialidad.
 */
void mostrar_datos( Nodo_t *startNode, const int mode ) {
   int especialidadInput = 0;
   Nodo_t *nodoX = startNode;
   
   if ( nodoX == NULL ) {
      printf( "\n\t[ INVENTARIO VACÍO. ]\n\n" );
   } else {
      if ( mode != 0 ) {
         do{
            printf( "Elija la especialidad a mostrar:\n"
                    "   1) Cardiología.\n"
                    "   2) Clínica.\n"
                    "   3) Gastroenterología.\n"
                    "   4) Cirugía.\n"
                    "   5) Dermatología.\n"
                    "   6) Oftalmología.\n"
                    "   7) Traumatología.\n" 
                    "Opción:\t" );
            
            better_scanf( "%d", &especialidadInput );
            /*
            scanf( "%d", &especialidadInput );
            int ch = 0;
            while ( ( ch = getchar() ) != '\n' && ch != EOF );
            */ 
            if ( especialidadInput < 1 || especialidadInput > 7 )
               printf( "\n[ ERROR: ELIJA UNA ESPECIALIDAD VÁLIDA. ]\n\n" );
         } while ( especialidadInput < 1 || especialidadInput > 7 );
      }
      
      // Escaneo de la lista por la especialidad pedida.
      while ( nodoX != NULL ) {
         if ( mode != 0 ) {   // Muestra de una determinada especialidad.
            if ( nodoX->dato.especialidad == especialidadInput ) {
               show_data( nodoX->dato );
            }
         } else {    // Muestra todo.
            show_data( nodoX->dato );
         }
         
         nodoX = nodoX->nextNode;
         printf( "\n---------------------------------------------------------------------------\n\n" );
      }
   }
}


//------------------------------------------------------------------------
// mostrar_fecha - [ DONE ]
//------------------------------------------------------------------------
/* # Mostrar la fecha de la base de datos #
 * Primeros 11 B del archivo de base de datos son para la FECHA.
 * Tratado como STRING (última pos. = '\0').
 * Usar ".dat".
 */
char * mostrar_fecha( char *fechaTemp ) {
   char *fechaNuevaStr = NULL;
   
   if ( fechaTemp != NULL ) { 
      // Fecha ya creada.
      printf( "La fecha es:\t[ %s ].\n\n", fechaTemp );
      fechaNuevaStr = fechaTemp;
   } else { 
      // Obtiene fecha actual.
      fechaNuevaStr = obtener_fecha();
      printf( "La nueva fecha es:\t[ %s ].\n\n", fechaNuevaStr );
   }
   
   return fechaNuevaStr;
}


// ########################################################################
// ### Ordenamiento ###
// ########################################################################

//------------------------------------------------------------------------
// orden_especialidad - [ DONE ]
//------------------------------------------------------------------------
/* Checkea si "backNode" va antes de "frontNode". 
 * Evalúa si ambos nodos están ordenados según:
 * ESPECIALIDAD.
 *
 * Retorna:
   - 0 si NO están ordenados.
   - 1 si están ordenados.
 */
int orden_especialidad( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) {
   int ordenados = 0;
   
   if ( frontNode != NULL && backNode != NULL ) {
      // Indica el SENTIDO del orden (ascendente o descendente).
      switch ( sentido ) {
         case ORD_ASC:
            if ( backNode->dato.especialidad <= frontNode->dato.especialidad )
               ordenados = 1;
            else
               ordenados = 0;
         break;
         
         case ORD_DES:
            if ( backNode->dato.especialidad >= frontNode->dato.especialidad )
               ordenados = 1;
            else
               ordenados = 0;
         break;
      }
   } else {
      ordenados = 1;
   }
   
   return ordenados;
}


//------------------------------------------------------------------------
// orden_precio - [ DONE ]
//------------------------------------------------------------------------
/* Checkea si "backNode" va antes de "frontNode". 
 * Evalúa si ambos nodos están ordenados según:
 * PRECIO.
 *
 * Retorna:
   - 0 si NO están ordenados.
   - 1 si están ordenados.
 */
int orden_precio( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) {
   int ordenados = 0;
   
   if ( frontNode != NULL && backNode != NULL ) {
      // Indica el SENTIDO del orden (ascendente o descendente).
      switch ( sentido ) {
         case ORD_ASC:
            if ( backNode->dato.precio <= frontNode->dato.precio )
               ordenados = 1;
            else
               ordenados = 0;
         break;
         
         case ORD_DES:
            if ( backNode->dato.precio >= frontNode->dato.precio )
               ordenados = 1;
            else
               ordenados = 0;
         break;
      }
   } else {
      ordenados = 1;
   }
   
   return ordenados;
}


//------------------------------------------------------------------------
// orden_disponibilidad - [ DONE ]
//------------------------------------------------------------------------
/* Checkea si "backNode" va antes de "frontNode". 
 * Evalúa si ambos nodos están ordenados según:
 * DISPONIBILIDAD (stock).
 *
 * Retorna:
   - 0 si NO están ordenados.
   - 1 si están ordenados.
 */
int orden_disponibilidad( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) {
   int ordenados = 0;
   
   if ( frontNode != NULL && backNode != NULL ) {
      // Indica el SENTIDO del orden (ascendente o descendente).
      switch ( sentido ) {
         case ORD_ASC:
            if ( backNode->dato.cantidad <= frontNode->dato.cantidad )
               ordenados = 1;
            else
               ordenados = 0;
         break;
         
         case ORD_DES:
            if ( backNode->dato.cantidad >= frontNode->dato.cantidad )
               ordenados = 1;
            else
               ordenados = 0;
         break;
      }
   } else {
      ordenados = 1;
   }
   
   return ordenados;
}

