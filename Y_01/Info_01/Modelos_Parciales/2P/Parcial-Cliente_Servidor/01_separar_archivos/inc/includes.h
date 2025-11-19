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

	
	// ######################################################
	// Defines
	// ######################################################
	#define 	ARCHSTR_SIZE	1024

	typedef struct Config_Data_s {
		int	port;
		int	backLog;
		char	archStr[MAX_FILES_SIZE];
	} Config_Data_t;
	
	
	// ######################################################
	// Funciones
	// ######################################################
	Config_Data_t	load_conf( char *fileName );
#endif