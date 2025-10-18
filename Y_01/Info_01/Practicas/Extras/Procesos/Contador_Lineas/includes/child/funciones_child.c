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
#include "funciones_child.h"


// ########################################################
// Variables GLOBALES
// ########################################################
char     sleeping = 1;  // Maneja si el hijo se queda durmiendo o no.


// ########################################################
// Funciones
// ########################################################
int      count_lines( int fdi );
void     write_local_file( char *arcName, int numLines );


//------------------------------------------------------------------------
// sig_hand_child - [ DONE ]
//------------------------------------------------------------------------
/* Espera la señal del padre para que se cierre.
 * Enlazado con SIGTERM.
 */
void sig_hand_child() {
   sleeping = 0;
}

//------------------------------------------------------------------------
// infant_work - [ INP ]
//------------------------------------------------------------------------
/* Trabajo del hijo.
 * Llama a la función que cuenta las líneas y devuelve
 * dicha cantidad a la función que pone la información en un archivo.
 *
 * # Orden de lógica #
 * Hijo termina su trabajo (queda en un bucle).
 * Padre envía al hijo SIGTERM.
 * Hijo tira mensaje.
 * Hijo termina, envía SIGCHLD al padre.
 * Padre mata al hijo con wait()/waitpid().
 */
void infant_work( int arcFD, char *arcName ) {
   int      numLines = 1;  // Mínimo 1 línea.
   
   signal( SIGTERM, sig_hand_child );
   
   usleep(10);
   
   numLines = count_lines( arcFD );
   
   close( arcFD );
   
   write_local_file( arcName, numLines );
   
   // # Crear BUCLE para que el hijo se quede colgado hasta que el padre envíe SIGTERM # 
   
   while ( sleeping == 1 ) {
      sleep(1);
   }  // RECIBIÓ SIGTERM DEL PADRE.
   
   printf( "Proceso PID: [%d] recibió SIGTERM, finalizando tarea...\n", getpid() );
   
   return;  // Finalizó el hijo.
}


//------------------------------------------------------------------------
// count_lines - [ DONE ]
//------------------------------------------------------------------------
/* Cuenta el N° de renglones de un archivo de texto cualquiera.
 */
int count_lines( int fdi ){
   int   cant = 0;
   int   renglones = 0;
   char  buf[SIZE_BUF];
   char  newLine[ 2 ] = "\n";
   

   cant = read( fdi, buf, SIZE_BUF - 1 );
   
   if ( cant > 0 ) {
      renglones++;   // Cuenta inicio del archivo como el primer renglón.
   
      while ( cant != 0 ){

         buf[ cant ] = '\0';   // Tratado como string.
         char *temp = buf;

         while ( (*temp != '\0') && ( temp = strstr( temp, newLine ) ) != NULL ){

            temp++;     // Si no avanza, se queda en la misma coincidencia.
            renglones++;
         }  // Terminaron las coincidencias en los Bytes leídos.

         cant = read( fdi, buf, SIZE_BUF - 1 );
      }  // Terminó de leer el archivo.
   }  // Si no entró: ARCHIVO VACÍO.
   
   printf( "[ Se detectaron [%d] renglones. ]\n", renglones );
   
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
   char     localFileNameStart[22] = "./archivos/CHILD-";
   char     localFile[SIZE_FILE]; 
   // [ruta] + [CHILD_PID] + .txt + '\0' = SIZE_FILE. 
   // 21 B   + 10 B        + 4 B  + 1 B  = 36 B.
   
   
   childPid = getpid(); // Agarra su propio PID para el nombre del archivo.
   tempCursor = mempcpy( localFile, localFileNameStart, strlen( localFileNameStart ) );
   sprintf( tempCursor, "%d", childPid );
   sprintf( tempCursor + sprintf( tempCursor, "%d", childPid ), ".txt" );
   
   localFd = open( localFile, O_WRONLY | O_TRUNC | O_CREAT, 0666 );
   dprintf( localFd, "El archivo \"%s\" tiene %d líneas.\n", arcName, numLines );
   
   printf( "[ Se terminó de escribir en el archivo hijo (PID = %d). ]\n", childPid );
   
   close( localFd );
}

