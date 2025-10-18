#include "funciones_child.h"

int contar_renglones( int fdi );

//------------------------------------------------------------------------
// count_lines - [ INP ]
//------------------------------------------------------------------------
/* Cuenta el número de lineas de un archivo.
 */
void count_lines( int arcFd, char *arcName ) {
   char     buf[SIZE_BUF];
   int      numBytes;
   int      numLines = 1;  // Mínimo 1 línea.
   int      cursor;
   
   /*
   numBytes = read( arcFd, buf, SIZE_BUF );
   while ( numBytes > 0 ) {
      for ( cursor = 0; cursor != (SIZE_BUF); cursor++ ) {
         if ( buf[cursor] == '\n' ) {
            numLines++;
         }
      }
      
      numBytes = read( arcFd, buf, SIZE_BUF );
   }
   */
   numLines = contarRenglones( arcFD );
   
   close( arcFd );
   
   write_local_file( arcName, numLines );
   
   // return numLines;
}


//------------------------------------------------------------------------
// contar_renglones - [ DONE ]
//------------------------------------------------------------------------
int contar_renglones( int fdi ){
   int   cant = 0;
   int   renglones = 0;
   char  buf[SIZE_BUF];
   char  newLine[ 2 ] = "\n";
   

   cant = read( fdi, buf, SIZE_BUF - 1 );
   
   if ( cant > 0 ) {
   
      while ( cant != 0 ){

         buf[ cant ] = '\0';   // Tratado como string.
         char *temp = buf;

         while ( *temp != '\0' && ( temp = strstr( temp, newLine ) ) != NULL ){

            temp++;   // Si no avanza, se queda en la misma coincidencia.
            renglones++;
         }  // Terminaron las coincidencias en los Bytes leídos.

         cant = read( fdi, buf, SIZE_BUF - 1 );
      }  // Terminó de leer el archivo.

      renglones++;   // Cuenta el final del archivo como otro renglón.
   }

   return renglones;
}


//------------------------------------------------------------------------
// write_local_file - [ DONE ]
//------------------------------------------------------------------------
/* Maneja un archivo local donde guarda información de las líneas leídas.
 */
void write_local_file( char *arcName, int numLines ) {
   int      localFd;
   char     *tempCursor;
   pid_t    childPid;
   char     localFile[SIZE_FILE]; 
   // [ruta] + [CHILD_PID] + .txt + '\0'. 
   // 21 B   + 10 B        + 4 B  + 1 B.
   char     localFileNameStart[22] = "../../archivos/CHILD-";
   
   
   childPid = getpid(); // Agarra su propio PID para el nombre del archivo.
   tempCursor = mempcpy( localFile, localFileNameStart, strlen( localFileNameStart ) );
   sprintf( tempCursor, "%d", childPid );
   sprintf( tempCursor + sprintf( tempCursor, "%d", childPid ), ".txt" );
   
   localFd = open( localFile, O_WRONLY | O_TRUNC | O_CREAT, 0666 );
   dprintf( localFd, "El archivo %s tiene %d líneas.", arcName, numLines );
   
   
   close( localFd );
}

