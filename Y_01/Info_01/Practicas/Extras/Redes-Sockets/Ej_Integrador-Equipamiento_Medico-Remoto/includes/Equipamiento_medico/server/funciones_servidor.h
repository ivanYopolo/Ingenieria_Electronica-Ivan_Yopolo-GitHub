#ifndef FUNCIONES_SERVIDOR
   #define FUNCIONES_SERVIDOR
   
   // ########################################################
   // Includes
   // ########################################################
   #include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>	
	#include <ctype.h>
   #include <time.h>
   
   #include "../../../includes/GetString_console/getstring-lib.h"       // Obtener string del kernel.
   #include "../../../includes/Manejo_Listas/Doble/lista_doble-lib.h"   // Manejo de listas dobles.
   #include "../../debugging.h"  // Debugging de funciones.
   #include "../../Sockets/sock-lib.h"
   
   
   // ########################################################
   // Defines
   // ########################################################
   #define PORT_RD      3494     // Puerto lectura (READ).
   #define PORT_WR      3498     // Puerto escritura (WRITE).
   #define MAXDATASIZE  4096
   #define TRUE         1
   #define FALSE        0
   

   // ########################################################
   // Funciones
   // ########################################################
   void cargar_datos_server();
   void guardar_datos_server();
#endif

