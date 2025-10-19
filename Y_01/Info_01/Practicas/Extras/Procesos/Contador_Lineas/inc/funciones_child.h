#ifndef FUNCIONES
   #define FUNCIONES
   
   // ########################################################
   // Includes
   // ########################################################
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <sys/wait.h>
   #include <unistd.h>
   #include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <ctype.h>
   
   
   // ########################################################
   // Defines
   // ########################################################
   #define SIZE_BUF     1024
   #define SIZE_FILE    36
   // [ruta] + [CHILD_PID] + .txt + '\0' = SIZE_FILE. 
   // 21 B   + 10 B        + 4 B  + 1 B  = 36 B.
   
   
   // ########################################################
   // Funciones
   // ########################################################
   void  infant_work( int arcFD, char *arcName );
#endif