#ifndef DEBUGGING
   #define DEBUGGING
   
   #include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
   
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <string.h>	
   
   #include "struct_datos.h"
   
   void show_data_log( Dato_t datoX, int fdLog );  // [ DONE ]
#endif