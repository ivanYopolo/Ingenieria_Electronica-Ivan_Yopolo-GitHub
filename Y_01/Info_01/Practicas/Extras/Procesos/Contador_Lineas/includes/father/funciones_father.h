#ifndef FUNCIONES_FATHER
   #define FUNCIONES_FATHER
   
   // ########################################################
   // Includes
   // ########################################################
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <sys/wait.h>
   #include <unistd.h>
   
   
   
   // ########################################################
   // Defines
   // ########################################################
   #define SIZE_BUF     4096
   
   
   // ########################################################
   // Funciones
   // ########################################################
   // void  sig_hand();  // Manejo de señales/child processes.
   void  write_global_file( int arcFd );
#endif