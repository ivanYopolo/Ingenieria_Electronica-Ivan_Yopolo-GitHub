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
   #define SIZE_BUF     4096
   #define TAM_STR      4096
   
   // ########################################################
   // Funciones
   // ########################################################
   void  count_lines( int arcFd, char *arcName );
   void  write_local_file( char *arcName, int numLines );
#endif