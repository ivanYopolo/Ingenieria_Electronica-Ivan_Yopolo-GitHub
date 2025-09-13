#ifndef includes
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   #include <unistd.h>
   #include <stdio.h>
   #include <string.h>
   #include <stdlib.h>
   #include <ctype.h>

   #define TAM_STR 100

   typedef struct Data_s {
      int dni;
      char *nombre;
      char *apellido;
   } Data_t;

   char * writeStrD();

   Data_t * getUserInput();

   void saveFileArrStruct( Data_t *arrData, int arrSize );

   void freeData( Data_t *arrData, int arrSize );
#endif


//--------------------------------------------------------------------------
// writeStrD
//--------------------------------------------------------------------------
/* Agarra un string del Kernel y lo guarda en un string.
 * ### DINÁMICO ###
 */
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


//--------------------------------------------------------------------------
// getUserInput
//--------------------------------------------------------------------------
/* Carga información del ciudadano en un struct.
 * Retorna dirección del struct creado.
 * ### DINÁMICO ###
 */
Data_t * getUserInput(){
   Data_t *dataX = malloc( 1 * sizeof(Data_t) );

   // DNI:
   printf( "Ingrese su DNI:         \t" );
   scanf( "%d", &(dataX->dni) );
   int ch = 0;
   while ( ( ch = getchar() ) != '\n' && ch != EOF );

   if ( dataX->dni > 1 ){
      // Nombre/s:
      printf( "Ingrese su/s nombre/s:  \t" );
      dataX->nombre = writeStrD();

      // Apellido/s:
      printf( "Ingrese su/s apellido/s:\t" );
      dataX->apellido = writeStrD();
   }else{
      // Finalizó el ingreso de datos.
      free( dataX );
      dataX = NULL;
   }

   return dataX;
}


//--------------------------------------------------------------------------
// saveFileArrStruct
//--------------------------------------------------------------------------
/* Copia los contenidos de un puntero a
 * estructura en un archivo binario.
 */
void saveFileArrStruct( Data_t *arrData, int arrSize ){
   int fdData = open( "Struct.data", O_WRONLY | O_CREAT | O_TRUNC, 0666 );

   for( int index = 0; index < arrSize; index++ ){
      write( fdData, arrData + index, sizeof(*arrData) );
   }

   close( fdData );
}


//--------------------------------------------------------------------------
// freeData
//--------------------------------------------------------------------------
/* Libera memoria del array de structs.
 */
void freeData( Data_t *arrData, int arrSize ){
   /* ALT: libera por elemento.
   for ( int index = 0; index < arrSize; index++ ){

      free( arrData + index );
   }
   */

   free( arrData );
}

