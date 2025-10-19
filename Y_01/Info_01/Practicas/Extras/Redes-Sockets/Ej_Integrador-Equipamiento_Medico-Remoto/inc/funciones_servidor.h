#ifndef FUNCIONES_SERVIDOR
   #define FUNCIONES_SERVIDOR
   
   // ########################################################
   // Includes
   // ########################################################
   #include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
   #include <sys/wait.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>	
	#include <ctype.h>
   #include <time.h>
   
   #include "debugging.h"  			// Debugging de funciones.
   #include "getstring-lib.h" 		// Obtener string del kernel.
   #include "lista_doble-lib.h"   	// Manejo de listas dobles.
   #include "sock-lib.h"				// Librería de sockets (MOD).
   
   // ########################################################
   // Defines
   // ########################################################
   #define PORT_RD         3494     // Puerto lectura (READ).
   #define PORT_WR         3498     // Puerto escritura (WRITE).
   #define MAXDATASIZE     4096
   #define TRUE            1
   #define FALSE           0
   #define MAX_SIZE_NAME   256
	#define SIZE_DATA_DIR	16
   

   // ########################################################
   // Funciones
   // ########################################################
   void cargar_datos_server( int portRD );
   void guardar_datos_server( int portWR );
	// void end_session();
#endif

