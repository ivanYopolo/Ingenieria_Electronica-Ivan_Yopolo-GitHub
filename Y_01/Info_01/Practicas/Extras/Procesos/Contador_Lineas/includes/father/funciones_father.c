/* # Contador de líneas con padres-hijos, utilizando fork() #
 * Ejercicio:
 * Cree un programa principal que lea una lista de nombres de archivos de entrada 
 * (pueden ser archivos de texto simples predefinidos) y un archivo de salida global.
 * Por cada archivo de entrada, el proceso principal debe usar fork() para crear un 
 * proceso hijo dedicado a procesar ese archivo.
 *
 * Cada proceso hijo debe:
 * a. Contar el número de líneas en su archivo asignado.
 * b. Escribir el resultado ("El archivo X tiene Y líneas.") en el archivo de salida global.
 *
 * El proceso padre debe esperar a que todos los hijos terminen de manera ordenada (usando wait() o waitpid()).
 * Manejo de Señales: Implemente un mecanismo donde el proceso padre pueda enviar una señal SIGTERM a un hijo 
 * específico. El hijo debe implementar un manejador de señales para SIGTERM que, en lugar de terminar 
 * inmediatamente, imprima un mensaje ("Proceso [PID] recibido SIGTERM, finalizando tarea...") y luego 
 * termine de manera limpia.
 *
 * Cada hijo puede escribir en un archivo temporal mientras el padre copia los contenidos al
 * archivo global.
 *
 * # Desafío extra # 
 * Use kill() en el padre para enviar SIGTERM a un hijo aleatorio después de 5 segundos.
 */


// ########################################################
// Includes
// ########################################################
#include "funciones_father.h"


// ########################################################
// Variables GLOBALES
// ########################################################
int      nChildren = 0;    // Variable global para tomar nota del N° de procesos hijos.


// ########################################################
// Funciones
// ########################################################
void     sig_hand_father();
void     wait_children();
void     write_global_file( int maxChilds, pid_t childrenPIDs[] );


//------------------------------------------------------------------------
// sig_hand_father - [ DONE ]
//------------------------------------------------------------------------
/* Espera la señal del hijo para que se cierre y lo mata.
 * Enlazado con SIGCHLD.
 * Decrementa el N° de hijos activos.
 */
void sig_hand_father() {
   wait( NULL );  // Mata al hijo.
   nChildren--;
   
   if ( nChildren != 0 )
      signal(SIGCHLD, sig_hand_father);
}


//------------------------------------------------------------------------
// wait_children - [ INP ]
//------------------------------------------------------------------------
/* Espera a que terminen los hijos.
 */
void wait_children() {
   signal( SIGCHLD, sig_hand_father );

   // # Espera a que terminen los hijos #
   while ( nChildren != 0 ) {   
      sleep(1);         // Checkea cada 1 segundo.
   }  // Sale: terminaron TODOS los hijos.
   
   return;    
}


//------------------------------------------------------------------------
// father_work - [ INP ]
//------------------------------------------------------------------------
/* Todo lo que hace el padre una vez que terminó de crear hijos.
 *
 * # Orden de lógica #
 * Hijo termina su trabajo (queda en un bucle).
 * Padre envía al hijo SIGTERM.
 * Hijo tira mensaje.
 * Hijo termina, envía SIGCHLD al padre.
 * Padre mata al hijo con wait()/waitpid().
 */
void father_work( pid_t childrenPIDs[] ){
   pid_t       maxChilds;  
   
   
   maxChilds = nChildren;      // Guarda el N° máximo de hijos creados.
   
   for ( int cursor = 0; cursor < maxChilds; cursor++ ) {
      kill( childrenPIDs[cursor], SIGTERM ); // Envía SIGTERM a todos los hijos.
   }
   
   wait_children();           // BLOQUEANTE: sale cuando terminaron todos.
   
   printf( "Escribiendo en el archivo global...\n" );
   write_global_file( maxChilds, childrenPIDs );
   
   
   free( childrenPIDs );
}

//------------------------------------------------------------------------
// child_PID_management - [ INP ]
//------------------------------------------------------------------------
/* Maneja las señales del hijo y guarda los PIDs.
 */
void child_PID_management( pid_t childrenPIDs[], pid_t childPid ) {
   usleep(500);  // 0,5 ms de retardo para que le de tiempo al CHILD de agarrar la señal SIGTERM.

   // # Variable global #
   nChildren++;                              // Empieza en 0 hijos.
   childrenPIDs = (pid_t *) reallocarray( childrenPIDs, nChildren, sizeof(pid_t) );
   childrenPIDs[nChildren - 1] = childPid;   // Guarda el PID del hijo.
}


//------------------------------------------------------------------------
// write_global_file - [ INP ]
//------------------------------------------------------------------------
/* Escribe todo lo que pusieron los hijos en un archivo global.
 */
void write_global_file( int maxChilds, pid_t childrenPIDs[] ) {
   int      childFD;
   int      globalFD;
   int      nBytes;
   char     *tempCursor;
   char     buf[SIZE_BUF];
   char     separator[SIZE_BUF] = "\n------------------------------------------------------------------------\n\n";
   char     localFile[SIZE_FILE]; 
   // [ruta] + [CHILD_PID] + .txt + '\0'. 
   // 21 B   + 10 B        + 4 B  + 1 B.
   char     localFileNameStart[22] = "./archivos/CHILD-";
   
   
   // Archivo global.
   globalFD = open( "./archivos/FATHER.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666 );
   
   // Agarra los PIDs de los hijos y los transforma a rutas de archivos.
   for ( int i = 0; (maxChilds >= 0); i++ ) {
      
      tempCursor = mempcpy( localFile, localFileNameStart, strlen( localFileNameStart ) );
      sprintf( tempCursor, "%d", childrenPIDs[i] );
      sprintf( tempCursor + sprintf( tempCursor, "%d", childrenPIDs[i] ), ".txt" );
      
      childFD = open( localFile, O_RDONLY );
      
      // Copia la info del archivo en un archivo global.
      nBytes = read( childFD, buf, SIZE_BUF );
      while ( nBytes > 0 ) {
         nBytes = write( globalFD, buf, nBytes );
         nBytes = write( globalFD, separator, strlen( separator ) );
         
         nBytes = read( childFD, buf, SIZE_BUF );
      }  // Terminó de leer el archivo.
      
      close( childFD );
      
      maxChilds--;
   }
   
   
   close( globalFD );
}
