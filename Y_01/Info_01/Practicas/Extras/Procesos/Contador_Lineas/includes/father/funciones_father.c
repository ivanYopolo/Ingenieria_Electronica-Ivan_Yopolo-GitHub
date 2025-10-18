#include "funciones_father.h"


//------------------------------------------------------------------------
// write_global_file - [ INP ]
//------------------------------------------------------------------------
/* Maneja el archivo global a escribir.
 */
void write_global_file( int arcFd ) {
   // A
}


//------------------------------------------------------------------------
// child_signal_management - [ INP ]
//------------------------------------------------------------------------
/* A
 */
void child_signal_management( int nChildsLocal, pid_t *childPids ) {
   int      childFileFD;
   int      globalFileFD;
   char     *tempCursor;
   char     localFile[SIZE_FILE]; 
   // [ruta] + [CHILD_PID] + .txt + '\0'. 
   // 21 B   + 10 B        + 4 B  + 1 B.
   char     localFileNameStart[22] = "../../archivos/CHILD-";
   
   
   // Archivo global.
   // globalFileFD = open(  );
   
   // Agarra los PIDs de los hijos y los transforma a rutas de archivos.
   for ( int i = 0; (nChildsLocal >= 0); i++ ) {
      
      tempCursor = mempcpy( localFile, localFileNameStart, strlen( localFileNameStart ) );
      sprintf( tempCursor, "%d", childPids[i] );
      sprintf( tempCursor + sprintf( tempCursor, "%d", childPids[i] ), ".txt" );
      
      childFileFD = open( localFile, O_RDONLY );
      
      // Copia la info del archivo en un archivo global.
      
      nChildsLocal--;
   }
}
