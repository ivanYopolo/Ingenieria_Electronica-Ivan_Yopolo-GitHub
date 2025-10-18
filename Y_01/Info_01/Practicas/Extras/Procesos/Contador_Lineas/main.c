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

/* # Comando #
clear; gcc -Wall --pedantic-errors \
./includes/father/funciones_father.c ./includes/child/funciones_child.c \ 
main.c -o prog.bin
*/

#include "./includes/child/funciones_child.h"
#include "./includes/father/funciones_father.h"

int        nChilds = 0;


void sig_hand();


int main( int argc, char *argv[] ) {
   pid_t       pid;
   pid_t       *childPids;    // Array dinámico de PIDs.
   pid_t       nChildsLocal = 0;
   int         arcFd;
   int         lines; 
   char        notChild = 1;
   
   
   if ( argc < 2 ) { // Argumentos inválidos.
      printf( "\n[ ERROR: NÚMERO DE ARGUMENTOS INVÁLIDOS. ]\n\n" );
      return 1;
   } else {
      
      childPids = (pid_t *) malloc( sizeof(pid_t) );
      
      for ( int i = 1; (i < argc && notChild); i++ ) {
         
         arcFd = open( argv[i], O_RDONLY );
         
         if ( arcFd >= 1 ) {  // Archivo válido.
         
            // Hacer fork() por cada archivo reconocido.
            pid = fork();
            if ( pid == -1 ) {      // ERROR.
               perror( stderr, "[ ERROR: NO SE PUDO CREAR CHILD PROCESS. ]\n" );
               exit(1);
               
            } else {
               if ( pid == 0 ) {    // Child.
                  count_lines( arcFd, argv[i] );
                  notChild = 0;                    // Evita que el hijo se "reproduzca".
               } else {             // Father (gets child PID).
                  notChild = 1;                    
                  nChilds++;                       // Empieza en 0 hijos.
                  childPids = (pid_t *) reallocarray( childPids, nChilds, sizeof(pid_t) );
                  childPids[nChilds - 1] = pid;    // Guarda el PID del hijo.
                  
                  signal(SIGTERM, sig_hand);       // La señal para terminar los hijos la maneja "sig_hand".
               }
            }  // PID válido.
         }  // Archivo válido.
      }  // Termina recorrido de archivos.
      
      if ( notChild ) {    // El padre verifica que terminaron todos los hijos.
         nChildsLocal = nChilds;
      
         // # Espera a que terminen los hijos #
         while ( nChilds != 0 ) {   
            sleep(1);  // Checkea cada 1 segundo.
         }  // Sale: terminaron TODOS los hijos.
         
      
         child_signal_management( nChildsLocal, childPids );
      }
   }
   
   return 0;
}


//------------------------------------------------------------------------
// sig_hand - [ DONE ]
//------------------------------------------------------------------------
/* Maneja la señal del hijo para que se cierre.
 * Decrementa el N° de hijos activos.
 */
void sig_hand() {
   wait( NULL );
   nChilds--;
}

