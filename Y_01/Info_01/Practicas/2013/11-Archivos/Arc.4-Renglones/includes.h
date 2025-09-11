#ifndef includes
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <ctype.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   #include <unistd.h>

   #define TAM_STR 100

   int contarRenglones( int fdi );
   void mostrarResultados( int renglones );
#endif


// --------------------------------------------------------
// mostrarResultados
// --------------------------------------------------------
void mostrarResultados( int renglones ){

   printf( "\n[ Se registraron %d renglones. ]\n\n", renglones );
}


// --------------------------------------------------------
// contarRenglones
// --------------------------------------------------------
int contarRenglones( int fdi ){
   int cant = 0;
   char buf[ TAM_STR ];
   char newLine[ 2 ] = "\n";
   int renglones = 0;

   // # LOG #
   int fdlog = open( "dump.log", O_CREAT | O_TRUNC | O_WRONLY, 0666 );

   cant = read( fdi, buf, TAM_STR - 1 );

   while ( cant != 0 ){

      buf[ cant ] = '\0';   // Tratado como string.
      char *temp = buf;

      // # LOG #
      dprintf( fdlog, "[ BYTES = %d ]\n"
                      "# Renglones = %d #\n"
                      "%s\n\n", cant, renglones, buf );

      while ( *temp != '\0' && ( temp = strstr( temp, newLine ) ) != NULL ){

         temp++;   // Si no avanza, se queda en la misma coincidencia.
         renglones++;
      }  // Terminaron las coincidencias en los Bytes leídos.

      cant = read( fdi, buf, TAM_STR - 1 );
   }  // Terminó de leer el archivo.

   renglones++;   // Cuenta el final del archivo como otro renglón.

   // # LOG #
   dprintf( fdlog, "\n\n### Se registraron %d renglones. ###", renglones );

   close( fdlog );

   return renglones;
}
