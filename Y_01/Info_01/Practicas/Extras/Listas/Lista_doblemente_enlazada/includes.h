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

#ifndef includes
   #include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>	
	#include <ctype.h>
   #include <time.h>
   
   #define TAM_DATE 11
   #define TAM_STR 1024
   #define TAM_DESC 20
   #define TAM_DET 200
   
   #define CARDIOLOGIA        1
   #define CLINICA            2
   #define GASTROENTEROLOGIA  3
   #define CIRUGIA            4
   #define DEREMATOLOGIA      5
   #define OFTALMOLOGIA       6
   #define TRAUMATOLOGIA      7

   typedef struct equipamiento{
      int sku; // Identificador de modelo (puede repetirse).
      char descripcion[ TAM_DESC ];
      char detalles[ TAM_DET ];
      int cantidad;
      int especialidad;
      int precio;
   } Equipamiento_t;
   /* Cada NODO de la lista va a ser un SKU de equipamiento.
    * Los IDs se repiten si los SKUs también se repiten.
    */
   
   typedef struct Nodo_s{
      Equipamiento_t *prevNode;
      Equipamiento_t *nextNode;
      Equipamiento_t dato;
   } Nodo_t;

   int menu();
   void cargarDatos();
   void modificarDatos( Nodo_t *startNode );
   void guardarDatos();
   void ordernarDatos();
   void mostrarDatos();
   void mostrarFecha();
   
   void popNode( Nodo_t **startNode );
   void pushNode( Nodo_t **startNode, Nodo_t *newNode );
   Nodo_t * createNode( Equipamiento_t *datoX );
   Nodo_t * getUserInput();
   
   char * writeStrD();
#endif


//------------------------------------------------------------------------
// menu
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


//------------------------------------------------------------------------
// getUserInput
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
   int especialidad = 1;
   
   Equipamiento_t *newData = malloc( sizeof(Equipamiento_t) );
   
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
      
      scanf( "%d", &especialidad );
      int ch = 0;
      while ( ( ch = getchar() ) != '\n' && ch != EOF );
      
      if ( especialidad < 1 && especialidad > 7 )
         printf( "[ ESPECIALIDAD INVÁLIDA. INTENTE NUEVAMENTE. ]\n\n" );
   }while ( especialidad < 1 && especialidad > 7 );
   newData->especialidad = especialidad;
   
   
   // # PRECIO #
   
   // Carga todo a un nuevo nodo.
   Nodo_t *newNode = createNode( &newData );
   
   // Agrega nodo a la lista (FIFO).
   pushNode( &startNode, newNode );
   
   return newNode;
}


//------------------------------------------------------------------------
// popNode
//------------------------------------------------------------------------
/* Saca un nodo de la lista (FIFO).
 * Verifiicar casos:
    * Nodo del diome.
    * Nodo final.
    * Nodo inicial.
 */
void popNode( Nodo_t **startNode ){
   // Se toma doble pointer porque se necesita cambiar los datos
   // del puntero en sí, que apunte a otro lado este mismo.
   
   if ( *startNode != NULL ){
      // Auxiliar para apuntar al nodo "n".
      Nodo_t *nodeAux = (*startNode);  
      
      // Apunta al nodo "n+1", elimina el anterior. 
      (*startNode) = (*startNode)->nextNode; 
      
      // "n-1" pasa a ser NULL.
      (*startNode)->prevNode = NULL;   
      
      free( nodeAux );    
   }
}


//------------------------------------------------------------------------
// pushNode
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
// createNode
//------------------------------------------------------------------------
/* Crea un nodo en la lista (FIFO).
 */
Nodo_t * createNode( Equipamiento_t *datoX ){
   // Asigna nuevo Nodo de forma DINÁMICA (queda en el HEAP).
   Nodo_t *newNode = (Nodo_t *) malloc( sizeof(Nodo_t) );
   
   // Anterior y siguiente apuntan a NULL.
   newNode->prevNode = NULL;
   newNode->nextNode = NULL;
   
   // Copia structs de DATOS.
   newNode->dato = *datoX;
   
   return newNode;
}


//--------------------------------------------------------------------------
// writeStrD
//--------------------------------------------------------------------------
// Agarra un string del Kernel y lo guarda en un string.
// ### DINÁMICO ###
char * writeStrD(){
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


//------------------------------------------------------------------------
// cargarDatos
//------------------------------------------------------------------------
/* Carga datos de un archivo de base de datos en la lista.
 * NO SOBREESCRIBE LISTA, sinó que agrega nodos a la misma.
 * Si se repiten SKUs, se juntan en un NODO los datos y se suman su "stock".
 * Usar ".dat".
 */
void cargarDatos(){
   int fdDat = 2;
   char fechaTemp[ TAM_DATE ];
   
   do{
      printf( "Ingrese el nombre del archivo a cargar información.\n"
              "Utilizar solamente archivos con extensión \'.dat\':\n" );
      
      char *nombreArchivo = writeStrD();
      
      fdDat = open( nombreArchivo, O_RDONLY );
      
      if ( fdDat < 1 ){
         printf( "\n[ ERROR: NOMBRE DE ARCHIVO INVÁLIDO. ]\n\n" );
         free( nombreArchivo );
      }
   }while ( fdDat < 1 );
   
   
   // Carga datos a la lista.
   
   
   
   // Checkea los SKUs.
   
   
}


//------------------------------------------------------------------------
// modificarDatos (ABM)
//------------------------------------------------------------------------
/* Agrega (alta), saca (baja) o modifica nodos de la lista (datos).
 */
void modificarDatos( Nodo_t *startNode ){
   int seleccion = 1;
   int skuTemp = 1;
   char descripcionTemp[ TAM_DESCR ];
   char detallesTemp[ TAM_DET ];
   Nodo_t *nodoX = NULL;
   
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
   }while ( skuTemp < 1 );

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
   }while ( seleccion < 1 || seleccion > 5 );
   
   switch ( seleccion ){
      case 1:  // SKU.
         do{
            printf( "Ingrese el nuevo SKU:\t" );
            
            scanf( "%d", &(nodoX->sku) );
            int ch = 0;
            while ( ( ch = getchar() ) != '\n' && ch != EOF );
            
            if ( nodoX->sku < 1 )
               printf( "\n[ SKU INVÁLIDO. INGRESE NUEVAMENTE EL DATO. ]\n\n" );
         }while ( nodoX->sku < 1 );
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
// guardarDatos
//------------------------------------------------------------------------
/* Guarda la lista entera en un archivo de base de datos.
 * Usar ".dat".
 */
void guardarDatos( Nodo_t *startNode ){
   int fdDat = open(  );
   Nodo_t *temp = startNode;
   
   while ( temp != NULL ){
      
   }
}


//------------------------------------------------------------------------
// ordenarDatos
//------------------------------------------------------------------------
/* Ordenar los elementos por:
    * Especialidad.
    * Precio.
    * Disponibilidades.
 */
void ordenarDatos(){

}


//------------------------------------------------------------------------
// mostrarDatos
//------------------------------------------------------------------------
/* Mostrar todos los elementos de una determinada especialidad.
 */
void mostrarDatos(){

}


//------------------------------------------------------------------------
// mostrarFecha
//------------------------------------------------------------------------
/* # Mostrar la fecha de la base de datos #
 * Primeros 11 B del archivo de base de datos son para la FECHA.
 * Tratado como STRING (última pos. = '\0').
 * Usar ".dat".
 */
void mostrarFecha( int fdDat ){
   int bytesRd = 0;
   char fecha[ TAM_DATE ]; // 11 Bytes.
   
   if ( fdDat > 1 ){
      bytesRd = read( fdDat, fecha, TAM_DATE );
      
      if ( bytesRd == TAM_DATE )
         printf( "La fecha es:\t[ %s ].\n", fecha );
      else
         printf( "[ ERROR EN LA LECTURA DE LA FECHA. ]\n" );
   }
}
