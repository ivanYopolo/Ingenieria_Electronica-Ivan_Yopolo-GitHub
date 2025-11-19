#ifndef INCLUDES
	#define INCLUDES
	
	// ######################################################
	// Includes
	// ######################################################
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <ctype.h>
	#include <sys/socket.h>
	#include <pthread.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	
	#include "sock-lib.h"

	
	// ######################################################
	// Defines
	// ######################################################
	// #define 	A 	1
	
	
	// ######################################################
	// Funciones
	// ######################################################
	void 		conexion_tcp( char *ipStr, int port, char *sequence );
#endif