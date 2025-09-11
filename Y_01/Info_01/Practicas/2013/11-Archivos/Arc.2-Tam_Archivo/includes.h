#ifndef includes
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <ctype.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   #include <unistd.h>

   #define TAM_STR 1024

   void mostrarResultados( long int tamArchivo );
   long int calcularTamArchivo( int fdi );
#endif


// -------------------------------------------------------
// mostrarResultados
// -------------------------------------------------------
void mostrarResultados( long int tamArchivo ){

   printf( "\nEl archivo tiene un tamaño de [%ld] B (Bytes).\n\n", tamArchivo );
}


// -------------------------------------------------------
// calcularTamArchivo
// -------------------------------------------------------
long int calcularTamArchivo( int fdi ){
   int cant = 0;
   char buf[ TAM_STR ];
   long int bytes = 0;

   do{
      cant = read( fdi, buf, TAM_STR );

      bytes += cant;
   }while( cant != 0 );   // Llegó al final del archivo.

   return bytes;
}
