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
   
   #include "../../../includes/GetString_console/getstring-lib.h"       // Obtener string del kernel.
   #include "../../../includes/Manejo_Listas/Doble/lista_doble-lib.h"   // Manejo de listas dobles.
   #include "../../debugging.h"  // Debugging de funciones.
   #include "../../Sockets/sock-lib.h"
   // #include "STRUCT"
   
   // ########################################################
   // Defines
   // ########################################################
   #define PORT_RD         3494     // Puerto lectura (READ).
   #define PORT_WR         3498     // Puerto escritura (WRITE).
   #define MAXDATASIZE     4096
   #define TRUE            1
   #define FALSE           0
   #define MAX_SIZE_NAME   256
   

   // ########################################################
   // Funciones
   // ########################################################
   char cargar_datos_server( int portRD );
   char guardar_datos_server( int portWR );
#endif

