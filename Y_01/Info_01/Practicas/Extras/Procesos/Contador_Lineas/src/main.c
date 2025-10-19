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
 *
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

/* # Comando (NO dejar espacios después de '\') #
clear; gcc -Wall --pedantic-errors main.c \
   ./includes/father/funciones_father.c \
   ./includes/child/funciones_child.c \
   -o prog.bin
*/

#include "../inc/funciones_child.h"
#include "../inc/funciones_father.h"


#define     SIZE_DIR    10


//------------------------------------------------------------------------
// main - [ DONE ]
//------------------------------------------------------------------------
int main( int argc, char *argv[] ) {
   pid_t       pid = 1;
   pid_t       *childrenPIDs;    // Array dinámico de PIDs.
   int         arcFd;
   char        fileDirectory[SIZE_DIR] = "../input/";
   
   
   if ( argc < 2 ) { // Argumentos inválidos.
      printf( "\n[ ERROR: NÚMERO DE ARGUMENTOS INVÁLIDOS. ]\n\n" );
      return 1;
   } else {
      
      childrenPIDs = (pid_t *) malloc( sizeof(pid_t) );
      
      for ( int nFile = 1; (nFile < argc) && (pid != 0); nFile++ ) {
			// tempCursor = mempcpy( localFile, localFileNameStart, strlen( localFileNameStart ) );
			// sprintf( tempCursor, "%d", childPid );
			// sprintf( tempCursor + sprintf( tempCursor, "%d", childPid ), ".txt" );
		
         
         arcFd = open( argv[nFile], O_RDONLY );
         
         if ( arcFd >= 1 ) {  // Archivo válido.
            printf( "ARCHIVO VÁLIDO.\n" );
         
            // Hacer fork() por cada archivo reconocido.
            pid = fork();
            
            if ( pid == -1 ) {   // ERROR.
               printf( "\n\n[ ERROR. ]\n" );
               perror( "[ ERROR: NO SE PUDO CREAR CHILD PROCESS. ]\n" );
               exit(1);
            } 
            
            if ( pid == 0 ) {    // Child.
               printf( "HIJO CREADO.\n" );
               infant_work( arcFd, argv[nFile] );
            } 
            
            if ( pid > 0 ) {     // Father (gets child PID).
               printf( "PAPÁ CREADO.\t\tPID (hijo): %d\n", pid );
               child_PID_management( childrenPIDs, pid );
            } 
         } else {  
            printf( "\n[ ARCHIVO \"%s\" INVÁLIDO. ]\n\n", argv[nFile] );
         }
      }  // Termina recorrido de archivos.
      
      if ( pid != 0 ) {       // El padre verifica que terminaron todos los hijos.
         // sleep(5);
         printf( "\nTerminaron todos los procesos hijos.\n" );
         father_work( childrenPIDs );
      }
   }
   
   return 0;
}




