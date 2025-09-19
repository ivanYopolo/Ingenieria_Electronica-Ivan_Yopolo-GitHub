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

#include "includes.h"

TODO: Corregir el ordenamiento.
TODO: Hacer inserción ordenada.
TODO: Ver obtención de fecha y si está el huso horario correcto.
TODO: Ver cargado y guardado de datos en archivos.

// ########################################################
// ### Menú ###
// ########################################################

//------------------------------------------------------------------------
// menu - [ DONE ]
//------------------------------------------------------------------------
int menu(){
   int menuSelect = 0;

   printf( "\n"
           "1) Cargar datos desde una base de datos.\n"
           "2) Agregar, quitar o modificar datos.\n" 
           "3) Guardar cambios de la base de datos.\n" 
           "4) Ordenar los elementos por especialidad, precio o disponibilidades.\n" 
           "5) Mostrar todos los elementos de una determinada especialidad.\n" 
           "6) Mostrar la fecha de una base de datos.\n" );

   do{
      printf( "\nOpción (0 o negativo para finalizar):\t\t" );
      
      scanf( "%d", &menuSelect );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
   }while ( menuSelect > 6 );
   
   return menuSelect;
}


// ########################################################
// ### Manejo de nodos ###
// ########################################################

//------------------------------------------------------------------------
// getUserInput - [ DONE ]
//------------------------------------------------------------------------
/* Cargar:
    * SKU.
    * Descripción.
    * Detalles.
    * Cantidad (stock).
    * Especialidad.
 */
Nodo_t * getUserInput( Nodo_t **startNode ){
   int sku = 1;
   int stock = 1;
   int especialidadTemp = 1;
   float precioTemp = 0;
   
   Dato_t *newData = malloc( sizeof(Dato_t) );
   
   printf( "Ingrese los datos del producto en forma ordenada:\n" );
   
   // # SKU #
   do{
      printf( "* SKU:\t" );
      
      scanf( "%d", &sku );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( sku < 1 )
         printf( "[ SKU INVÁLIDO. INTENTE NUEVAMENTE. ]\n\n" );
   }while ( sku < 1 );
   newData->sku = sku;
   
   
   // # Descripción #
   printf( "* Descripción:\t" );
   
	while( fgets( newData->descripcion, TAM_DESC, stdin ) == NULL ){
      printf( "[ ERROR: POR FAVOR, ESCRIBA DE VUELTA. ]\n" );
   }	// ERROR
	
	// Flushea el buffer:
	if( newData->descripcion[ strlen( newData->descripcion ) - 1 ] != '\n' ){
		int ch = 0;
		while( ( ch = getchar() ) != '\n' && ch != EOF );
	}
   
	// Si se detecta un salto de línea:
	if( newData->descripcion[ strlen( newData->descripcion ) - 1 ] == '\n' ){
      newData->descripcion[ strlen( newData->descripcion ) - 1 ] = '\0';
   }
   
   
   // # Detalles #
   printf( "* Detalles:\t" );
   
   while( fgets( newData->detalles, TAM_DET, stdin ) == NULL ){
      printf( "[ ERROR: POR FAVOR, ESCRIBA DE VUELTA. ]\n" );
   }	// ERROR
	
	// Flushea el buffer:
	if( newData->detalles[ strlen( newData->detalles ) - 1 ] != '\n' ){
		int ch = 0;
		while( ( ch = getchar() ) != '\n' && ch != EOF );
	}
   
	// Si se detecta un salto de línea:
	if( newData->detalles[ strlen( newData->detalles ) - 1 ] == '\n' ){
      newData->detalles[ strlen( newData->detalles ) - 1 ] = '\0';
   }
   
   
   // # Cantidad (stock) #
   do{
      printf( "* Cantidad en stock:\t" );
      
      scanf( "%d", &stock );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( stock < 1 )
         printf( "[ STOCK INVÁLIDO. INTENTE NUEVAMENTE. ]\n\n" );
   }while ( stock < 1 );
   newData->cantidad = stock;
   
   
   // # Especialidad #
   do{
      printf( "* # Especialidad #\n"
              "   1) Cardiología.\n"
              "   2) Clínica.\n"
              "   3) Gastroenterología.\n"
              "   4) Cirugía.\n"
              "   5) Dermatología.\n"
              "   6) Oftalmología.\n"
              "   7) Traumatología.\n" 
              "Opción:\t" );
      
      scanf( "%d", &especialidadTemp );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( especialidadTemp < 1 && especialidadTemp > 7 )
         printf( "[ ESPECIALIDAD INVÁLIDA. INTENTE NUEVAMENTE. ]\n\n" );
   }while ( especialidadTemp < 1 && especialidadTemp > 7 );
   newData->especialidad = especialidadTemp;
   
   
   // # PRECIO #
   do{
      scanf( "%f", &precioTemp );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( precioTemp < 0 )
         printf( "[ PRECIO INVÁLIDO. INTENTE NUEVAMENTE. ]\n\n" );
   }while ( precioTemp < 0 );
   newData->precio = precioTemp;
   
   
   // Carga todo a un nuevo nodo.
   Nodo_t *newNode = createNode( &newData );
   
   // Agrega nodo a la lista (FIFO).
   pushNode( &startNode, newNode );
   
   return newNode;
}


//------------------------------------------------------------------------
// popNode - [ DONE ]
//------------------------------------------------------------------------
/* Saca un nodo de la lista (FIFO).
 * Verifiicar casos:
    * Nodo del diome.
    * Nodo final.
    * Nodo inicial.
 */
void popNode( Nodo_t **nodeX ){
   Nodo_t *nodeAux = NULL;
   
   if ( *nodeX != NULL ){
      // Caso primer nodo:
      if ( (*nodeX)->prevNode == NULL ){
         // Auxiliar apunta al nodo "n".
         nodeAux = (*nodeX);  
         
         // Apunta al nodo "n+1", elimina el anterior. 
         (*nodeX) = (*nodeX)->nextNode; 
         
         // "n-1" pasa a ser NULL.
         (*nodeX)->prevNode = NULL;   
         
         free( nodeAux );    
      }else
      
      // Caso último nodo:
      if ( (*nodeX)->nextNode == NULL ){
         // Nodo "n-1" "NULL", elimina el actual. 
         (*nodeX)->prevNode = NULL; 
         
         free( *nodeX );
      }
      
      // Caso nodo del diome:
      if ( (*nodeX)->nextNode != NULL && (*nodeX)->prevNode != NULL ){
         // Auxiliar apunta al nodo "n".
         nodeAux = (*nodeX);  
         // Apunta a "n-1".
         Nodo_t *backNode  = (*nodeX)->prevNode;
         // Apunta a "n+1".
         Nodo_t *frontNode = (*nodeX)->nextNode;
         
         // Back & Front se enlazan entre sí, perdiendo a "nodeX".
         backNode->nextNode  = frontNode;
         frontNode->prevNode = backNode;
         
         free( nodeAux );    
      }
      
   }
}


//------------------------------------------------------------------------
// pushNode - [ REV ]
//------------------------------------------------------------------------
/* Agrega un nodo a la lista (FIFO).
 * Ver manera de hacer INSERCIÓN ORDENADA.
 */
void pushNode( Nodo_t **startNode, Nodo_t *newNode ){
   // El siguiente del Nodo nuevo apunta al viejo inicio de la lista (FIFO).
   newNode->nextNode = *startNode;
   
   // El viejo anterior deja de ser NULL y pasa a ser el nuevo Nodo.
   (*startNode)->prevNode = newNode;
   
   // El inicio de la lista es el nuevo Nodo.
   *startNode = newNode;
   
   // El anterior es el NULL.
   newNode->prevNode = NULL;
}


//------------------------------------------------------------------------
// createNode - [ DONE ]
//------------------------------------------------------------------------
/* Crea un nodo en la lista (FIFO).
 */
Nodo_t * createNode( Dato_t *datoX ){
   // Asigna nuevo Nodo de forma DINÁMICA (queda en el HEAP).
   Nodo_t *newNode = (Nodo_t *) malloc( sizeof(Nodo_t) );
   
   // Anterior y siguiente apuntan a NULL.
   newNode->prevNode = NULL;
   newNode->nextNode = NULL;
   
   // Copia structs de DATOS.
   newNode->dato = *datoX;
   
   return newNode;
}


// ########################################################
// ### Especiales ###
// ########################################################

//--------------------------------------------------------------------------
// writeStrD - [ DONE ]
//--------------------------------------------------------------------------
// Agarra un string del Kernel y lo guarda en un string.
// ### DINÁMICO ###
char * writeStrD() {
   char strI[ TAM_STR ];

   // No poner strlen() porque toma el salto de línea.
	while( fgets( strI, TAM_STR, stdin ) == NULL ){
      printf( "[ ERROR: POR FAVOR, ESCRIBA DE VUELTA. ]\n" );
   }	// ERROR
	
	// Flushea el buffer:
	if( strI[ strlen( strI ) - 1 ] != '\n' ){
 
		int ch = 0;
		while( ( ch = getchar() ) != '\n' && ch != EOF );
   }

	// Si se detecta un salto de línea:
	if( strI[ strlen( strI ) - 1 ] == '\n' ){
      strI[ strlen( strI ) - 1 ] = '\0';
   }

   // Aloja memoria en el HEAP para el string.
   char *strO = (char *) calloc( strlen( strI ), sizeof(char) );
  
   strcpy( strO, strI );
  
   return strO;
}


//--------------------------------------------------------------------------
// closeSession - [ DONE ]
//--------------------------------------------------------------------------
/* Libera memoria de la lista entera y cierra el archivo.
 */
void closeSession( Nodo_t *startNode, char *fechaStr, int fdData ) {
   Nodo_t *nodoX = startNode;
   Nodo_t *nodoAux = NULL;
   
   while ( nodoX != NULL ) {
      nodoAux = nodoX;
      nodoX = nodoX->nextNode;
      free( nodoAux );
   }
   
   free( fechaStr );
   
   close( fdData );
}


//--------------------------------------------------------------------------
// isSKURepeated
//--------------------------------------------------------------------------
/* Checkea si se repite el SKU de un dato nuevo en toda la lista.
 *
 * Retorna:
   - NULL si no se repite.
   - La dirección del nodo correspondiente si es que se repite.
 */
Nodo_t * isSKURepeated( Nodo_t *startNode, Dato_t datoInput ) {
   Nodo_t *nodoX = startNode;
   
   
   
   return nodoX;
}


//--------------------------------------------------------------------------
// obtenerFecha - [ DONE ]
//--------------------------------------------------------------------------
/* Obtiene la fecha actual del sistema y lo devuelve como un string.
 * Formato: DD/MM/YYYY.
 */
char * obtenerFecha(){
   time_t    tiempoNuevo;
   struct tm *fechaNueva = NULL;

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
// cargarDatos
//------------------------------------------------------------------------
/* Carga datos de un archivo de base de datos en la lista.
 * NO SOBREESCRIBE LISTA, sinó que agrega nodos a la misma.
 * Si se repiten SKUs, se juntan en un NODO los datos y se suman su "stock".
 * Usar ".dat".
 *
 * Devuelve la fecha leída (DD/MM/YYYY).
 */
char * cargarDatos( Nodo_t *startNode ) {
   int      fdData = 2;
   int      bytesRd = 0;
   char    *fechaTemp = malloc( TAM_DATE * sizeof(char) );
   Dato_t   datoInput;
   Nodo_t  *nodoX = NULL;
   
   // ### Abre el archivo a extraer datos ###
   do {
      printf( "Ingrese el nombre del archivo a cargar información.\n"
              "Utilizar solamente archivos con extensión \'.dat\':\n" );
      
      char *nombreArchivo = writeStrD();
      
      fdData = open( nombreArchivo, O_RDONLY );
      
      if ( fdData < 1 ){
         printf( "\n[ ERROR: NOMBRE DE ARCHIVO INVÁLIDO. ]\n\n" );
         free( nombreArchivo );
      }
   } while ( fdData < 1 );
   
   // ### Carga datos a la lista ###
   
   bytesRd = read( fdData, fechaTemp, TAM_DATE );   // Lee la fecha.
   
   if ( bytesRd == TAM_DATE && fechaTemp != NULL ) {
   
      bytesRd = read( fdData, &datoInput, sizeof(Dato_t) );  // Lee 1 dato.

      while ( bytesRd == sizeof(Dato_t) ) {  // Pasa por la lista entera.
      
         // Checkea los SKUs.
         if ( ( nodoX = isSKURepeated( startNode, datoInput ) ) != NULL ) { 
            // Junta datos del mismo SKU, aumenta stock.
            mergeData( nodoX, datoInput );
         } else {                            
            // Agrega un dato a la lista.
            nodoX = createNode( &datoInput );
            pushNode( nodoX );
         }
         
         bytesRd = read( fdData, &datoInput, sizeof(Dato_t) );  // Lee 1 dato.
      }  // Terminó de leer el archivo.

      printf( "\n[ Lectura exitosa. ]\n\n" );
      close( fdData );
   } else {    // N° de Bytes leídos menor a la fecha.
      printf( "\n[ ARCHIVO VACÍO. ]\n\n" );
      close( fdData );
   }
   
   return fechaTemp;
}


//------------------------------------------------------------------------
// modificarDatos (ABM)
//------------------------------------------------------------------------
/* Agrega (alta), saca (baja) o modifica datos de la lista.
 */
void modificarDatos( Nodo_t *startNode ){
   int      seleccion = 1;
   int      skuTemp = 1;
   char     descripcionTemp[ TAM_DESCR ];
   char     detallesTemp[ TAM_DET ];
   Nodo_t  *nodoX = NULL;
   
   /* # Especialidades #
    1) Cardiología.
    2) Clínica.
    3) Gastroenterología.
    4) Cirugía. 
    5) Dermatología. 
    6) Oftalmología.
    7) Traumatología.
    */

   // Selección de SKU (nodo):
   do{
      printf( "Ingrese el SKU del producto a modificar:\t" );
      
      scanf( "%d", &skuTemp );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( skuTemp < 1 )
         printf( "\n[ SKU INVÁLIDO. INGRESE NUEVAMENTE EL DATO. ]\n\n" );
   } while ( skuTemp < 1 );   // Registró un SKU válido.

   do{
      printf( "Elija el dato a modificar:\n"
              "1) SKU.\n" 
              "2) Descripción.\n" 
              "3) Detalles.\n" 
              "4) Cantidad.\n" 
              "5) Especialidad.\n" );
      
      scanf( "%d", &seleccion );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( seleccion < 1 || seleccion > 5 )
         printf( "\n[ SELECCIÓN INVÁLIDA. ]\n\n" );
   } while ( seleccion < 1 || seleccion > 5 );
   
   switch ( seleccion ) {
      case 1:  // SKU.
         do{
            printf( "Ingrese el nuevo SKU:\t" );
            
            scanf( "%d", &(nodoX->sku) );
            int ch = 0;
            while ( ( ch = getchar() ) != '\n' && ch != EOF );
            
            if ( nodoX->sku < 1 )
               printf( "\n[ SKU INVÁLIDO. INGRESE NUEVAMENTE EL DATO. ]\n\n" );
         } while ( nodoX->sku < 1 );
      break;
      
      case 2:  // Descripción.
         printf( "Ingrese la nueva descripción:\t" );
      break;
      
      case 3:  // Detalles.
         
      break;
      
      case 4:  // Cantidad.
         
      break;
      
      case 5:  // Especialidad.
         
      break;
   }
}


//------------------------------------------------------------------------
// guardarDatos - [ REV ]
//------------------------------------------------------------------------
/* Guarda la lista entera en un archivo de base de datos.
 * Usar '.dat'.
 */
void guardarDatos( Nodo_t *startNode, char *fechaAct ){ 
   int      fdData = 1;
   char    *nombreTemp;
   char    *nombreArchivo;
   int      sobreescribir = 0;
   Nodo_t  *nodoX = startNode;
   
   // Verificar nombre del archivo por input del usuario.
   do{
      printf( "Elija un nombre para el archivo a guardar\t" );
      nombreTemp = writeStrD();
      
      if ( nombreTemp == NULL )
         printf( "\n[ ERROR: INGRESE UN NOMBRE VÁLIDO. ]\n\n" );
      
      // Agregar el '.dat' y pasarlo a "nombreArchivo".
      nombreArchivo = calloc( strlen( nombreTemp ) + 5, sizeof(char) );
      strcat( nombreArchivo, nombreTemp );
      strcat( nombreArchivo, ".dat" );
      
      // Evaluar nombres repetidos.
      if ( open( nombreArchivo, O_RDONLY ) > 1 )
         do{
            printf( "\nExiste un archivo con el mismo nombre, ¿desea sobreescibirlo?\n"
                    "1) Sí.\n"
                    "2) No.\n" 
                    "Opción:\t" );
            
            scanf( "%d", &sobreescribir );
            int ch = 0;
            while ( ( ch = getchar() ) != '\n' && ch != EOF );
            
            if ( sobreescribir != 1 && sobreescribir != 2 )
               printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n" );
         } while ( sobreescribir != 1 && sobreescribir != 2 );
         
         switch ( sobreescribir ){
            case 1:  // Sobreescritura.
               fdData = open( nombreArchivo, O_WRONLY | O_CREAT | O_TRUNC, 0666 );
            break;
         
            case 2:  // Vuelve a elegir el nombre del archivo.
               nombreArchivo = NULL;
            break;
         }
   } while ( nombreArchivo == NULL ); // Nombró correctamente el archivo.
   
   // Escribe la fecha actual en formato "DD/MM/YYYY".
   if ( fechaAct == NULL ) {
      fechaAct = obtenerFecha();
   }
   
   write( fdData, fechaAct, TAM_DATE );
   
   // Guarda TODOS los DATOS en un archivo.
   while ( nodoX != NULL ){
      write( fdData, nodoX->dato, sizeof(Dato_t) );
      nodoX = nodoX->nextNode; 
   }  // Terminó de guardar los datos.
}


//------------------------------------------------------------------------
// ordenarDatos - [ DONE ]
//------------------------------------------------------------------------
/* Ordenar los elementos por:
    * Especialidad.
    * Precio.
    * Disponibilidades.
 */
int ordenarDatos( const Nodo_t *startNode, int ordenamiento[] ){
   int datoDeOrdenamiento = 0;
   int sentidoOrdenamiento = 0;
   
   // Tipo de dato a ordenar.
   do{
      printf( 
      "\n# Seleccione con qué dato ordenar el inventario #\n" 
      "1) Especialidad.\n" 
      "2) Precio.\n" 
      "3) Disponibilidad (stock).\n" );
      
      scanf( "%d", &datoDeOrdenamiento );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( datoDeOrdenamiento > 3 && datoDeOrdenamiento < 1 )
         printf( "\n[ ERROR: INGRESE UNA OPCIÓN VÁLIDA. ]\n" );
   } while ( datoDeOrdenamiento > 3 && datoDeOrdenamiento < 1 );
   
   ordenamiento[ 0 ] = datoDeOrdenamiento;
   
   // Sentido de ordenamiento.
   do{
      printf( 
      "\n# Seleccione el sentido del ordenamiento #\n" 
      "1) Ascendente.\n" 
      "2) Descendente.\n" );
      
      scanf( "%d", &sentidoOrdenamiento );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( sentidoOrdenamiento > 2 && sentidoOrdenamiento < 1 )
         printf( "\n[ ERROR: INGRESE UNA OPCIÓN VÁLIDA. ]\n" );
   } while ( sentidoOrdenamiento > 2 && sentidoOrdenamiento < 1 );
   
   ordenamiento[ 1 ] = sentidoOrdenamiento;
   
   /* Ordenamiento: array de ints (2 pos):
    * 0: Dato a ordenar.
    * 1: Sentido de ordenamiento.
    */
   
   // Ordenamiento en sí mismo.
   sortList( startNode, ordenamiento );

   return nuevoOrdenamiento;
}


//------------------------------------------------------------------------
// mostrarDatos - [ DONE ]
//------------------------------------------------------------------------
/* Mostrar todos los elementos de una determinada especialidad.
 */
void mostrarDatos( Nodo_t *startNode ){
   int especialidadInput = 0;
   Nodo_t *nodoX = startNode;
   
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
      scanf( "%d", &especialidadInput );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( especialidadInput < 1 || especialidadInput > 7 )
         printf( "\n[ ERROR: ELIJA UNA ESPECIALIDAD VÁLIDA. ]\n\n" );
   } while ( especialidadInput < 1 || especialidadInput > 7 );
   
   // Escaneo de la lista por la especialidad pedida.
   while ( nodoX != NULL ){
      if ( nodoX->dato.especialidad == especialidadInput ){
         printf( "\n#######################################\n" );
         printf( "* SKU:               \t%d\n", nodoX->dato.sku );
         printf( "* Descripción:       \t%s\n", nodoX->dato.descripcion );
         printf( "* Detalles:          \t%s\n", nodoX->dato.detalles );
         printf( "* Cantidad en stock: \t%d\n", nodoX->dato.cantidad );
      }
      
      nodoX = nodoX->nextNode;
   }
   
   printf( "\n#######################################\n\n" );
}


//------------------------------------------------------------------------
// mostrarFecha - [ DONE ]
//------------------------------------------------------------------------
/* # Mostrar la fecha de la base de datos #
 * Primeros 11 B del archivo de base de datos son para la FECHA.
 * Tratado como STRING (última pos. = '\0').
 * Usar ".dat".
 */
char * mostrarFecha( char *fechaTemp ) {
   char *fechaNuevaStr = NULL;
   
   if ( fechaTemp != NULL ) { 
      // Fecha ya creada.
      printf( "La fecha es:\t[ %s ].\n\n", fechaTemp );
      fechaNuevaStr = fechaTemp;
   } else { 
      // Obtiene fecha actual.
      fechaNuevaStr = obtenerFecha();
      printf( "La nueva fecha es:\t[ %s ].\n\n", fechaNuevaStr );
   }
   
   return fechaNuevaStr;
}


// ########################################################################
// ### Ordenamiento ###
// ########################################################################

//------------------------------------------------------------------------
// sortList - [ REV ]
//------------------------------------------------------------------------
/* Ordena la lista entera (bubblesort).
 * Utiliza puntero a función dependiendo del tipo de dato a ordenar y
 * del sentido del orden.
 */
void sortList( Nodo_t **startNode, const int ordenamiento[] ) {
   Node_t *nodoX = NULL;
   // Puntero a función con array de funciones.
   // Cada una ordena según las 3 opciones.
   int (*ordenamientoLista[ 3 ])( Nodo_t *backNode, Nodo_t *frontNode, int orden ) = 
      { ordenEspecialidad, ordenPrecio, ordenDisponibilidad };
   
   /* Ordenamiento: array de ints (2 pos):
    * 0: Dato a ordenar.
    * 1: Sentido de ordenamiento.
    */
   
   // ### Ordenamiento de la lista (bubblesort) ###
   
   // Verifica si la lista está ordenada o no.
   // Pasada externa para la lista entera.
   while ( !isListOrdered( *startNode, (*ordenamientoLista)[ ordenamiento[ 0 ] ]( nodoX, nodoX->nextNode, ordenamiento[ 1 ] ) ) ) {   
      
      nodoX = *startNode;
      
      // Pasada interna por nodo.
      while ( nodoX != NULL ) {
         
         // Compara según el dato a ordenar entre el nodo actual y el siguiente.
         if ( (*ordenamientoLista)[ ordenamiento[ 0 ] ]( nodoX, nodoX->nextNode, ordenamiento[ 1 ] ) ) {
         
            if ( nodoX == *startNode ) {
               // Para evitar perder el inicio de la lista, antes de 
               // cambiarlos de lugar, se guarda el "nuevo inicio".
               *startNode = nodoX->nextNode;
            }
         
            // Los Intercambia si es que cumple los criterios pedidos.
            swapNodes( nodoX, nodoX->nextNode );
         } else { // Si no cambia de lugar los nodos.
         
            nodoX = nodoX->nextNode;   // Pasa al siguiente nodo.
         }
      }  // Terminó de pasar por toda la lista, comparando 1 nodo en particular.
   }  // Terminó de pasar por toda la lista, con todos los nodos.
}


//------------------------------------------------------------------------
// isListOrdered - [ REV ]
//------------------------------------------------------------------------
/* Verifica si la lista está ordenada.
 * Devuelve:
   - 0 si NO está ordenada.
   - 1 si está ordenada.
 */
int isListOrdered( const Nodo_t *startNode, int (*ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) ) {
   Node_t *nodoX = startNode;   // Temporal como cursor, para recorrer lista.
   int ordenada = 1;
   
   while ( nodoX != NULL && ordenada != 0 ) {
      // Según el método de ordenamiento y sentido orden elegido, evalúa su estado de orden.
      if ( !(*ordenamiento)( nodoX, nodoX->nextNode, orden ) ) {
         ordenada = 0;
      }

      nodoX = nodoX->nextNode;
   }  // Sale si llega al final o si no está ordenada la lista.
   
   return ordenada;  // Ordenados naturalmente a menos que lo indique la función.
}


//------------------------------------------------------------------------
// ordenEspecialidad - [ DONE ]
//------------------------------------------------------------------------
/* Evalúa si ambos nodos están ordenados según:
 * ESPECIALIDAD.
 *
 * Retorna:
   - 0 si NO están ordenados.
   - 1 si están ordenados.
 */
int ordenEspecialidad( Nodo_t *backNode, Nodo_t *frontNode, int orden ) {
   int ordenados = 0;
   
   if ( frontNode != NULL && backNode != NULL ) {
      // Indica el SENTIDO del orden (ascendente o descendente).
      switch ( orden ) {
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
// ordenPrecio - [ DONE ]
//------------------------------------------------------------------------
/* Evalúa si ambos nodos están ordenados según:
 * PRECIO.
 *
 * Retorna:
   - 0 si NO están ordenados.
   - 1 si están ordenados.
 */
int ordenPrecio( Nodo_t *backNode, Nodo_t *frontNode, int orden ) {
   int ordenados = 0;
   
   if ( frontNode != NULL && backNode != NULL ) {
      // Indica el SENTIDO del orden (ascendente o descendente).
      switch ( orden ) {
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
// ordenDisponibilidad - [ DONE ]
//------------------------------------------------------------------------
/* Evalúa si ambos nodos están ordenados según:
 * DISPONIBILIDAD (stock).
 *
 * Retorna:
   - 0 si NO están ordenados.
   - 1 si están ordenados.
 */
int ordenDisponibilidad( Nodo_t *backNode, Nodo_t *frontNode, int orden ) {
   int ordenados = 0;
   
   if ( frontNode != NULL && backNode != NULL ) {
      // Indica el SENTIDO del orden (ascendente o descendente).
      switch ( orden ) {
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


//------------------------------------------------------------------------
// swapNodes - [ REV ]
//------------------------------------------------------------------------
/* Cambia los nodos de lugar.
 *
 * Nomenclatura:  
   - anterior  = n-1.
   - backNode  = n.
   - frontNode = n+1.
   - siguiente = n+2.
 *
 * Checkear casos de:
   - Nodo inicial.
   - Nodo del diome.
   - Nodo final.
 */
void swapNodes( Nodo_t *backNode, Nodo_t *frontNode ) {
   Nodo_t *anterior = NULL;      // "n-1".
   Nodo_t *siguiente = NULL;     // "n+2".

   // Caso nodo del diome:
   if ( backNode->prevNode != NULL && frontNode->nextNode != NULL ) {
      anterior = backNode->prevNode;               // "n-1".
      
      siguiente = frontNode->nextNode;             // "n+2".
      
      backNode->nextNode = siguiente;              // Next de "n" apunta a "n+2".
      
      frontNode->prevNode = anterior;              // Prev de "n+1" apunta a "n-1".
      
      backNode->prevNode = frontNode;              // Prev de "n" apunta a "n+1".
      
      frontNode->nextNode = backNode;              // Next de "n+1" apunta a "n".
      
      anterior->nextNode = frontNode;              // Next de "n-1" apunta a "n+1".
      
      siguiente->prevNode = backNode;              // Prev de "n+2" apunta a "n".
   }
   
   // Caso nodo inicial:
   if ( backNode->prevNode == NULL && frontNode->nextNode != NULL ) {
      anterior = NULL;                             // "n-1" = NULL.
      
      siguiente = frontNode->nextNode;             // "n+2".
      
      backNode->nextNode = siguiente;              // Next de "n" apunta a "n+2".
      
      frontNode->prevNode = anterior;              // Prev de "n+1" apunta a NULL.
      
      backNode->prevNode = frontNode;              // Prev de "n" apunta a "n+1".
      
      frontNode->nextNode = backNode;              // Next de "n+1" apunta a "n".
      
      siguiente->prevNode = backNode;              // Prev de "n+2" apunta a "n".
   }
   
   // Caso nodo final:
   if ( backNode->prevNode != NULL && frontNode->nextNode == NULL ) {
      anterior = backNode->prevNode;               // "n-1".
      
      siguiente = NULL;                            // "n+2" = NULL.
      
      backNode->nextNode = siguiente;              // Next de "n" apunta a NULL.
      
      frontNode->prevNode = anterior;              // Prev de "n+1" apunta a "n-1".
      
      backNode->prevNode = frontNode;              // Prev de "n" apunta a "n+1".
      
      frontNode->nextNode = backNode;              // Next de "n+1" apunta a "n".
      
      anterior->nextNode = frontNode;              // Next de "n-1" apunta a "n+1".
   }
}


