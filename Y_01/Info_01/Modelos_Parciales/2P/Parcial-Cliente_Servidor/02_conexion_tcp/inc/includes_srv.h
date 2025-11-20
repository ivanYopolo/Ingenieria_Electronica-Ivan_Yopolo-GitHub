#ifndef INCLUDES_SRV
	#define INCLUDES_SRV
	
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
	#define	MAX_BUF_SIZE	1024
	#define	SEQ_LEN			7
	#define	READY_LEN		6
	#define	ACK_LEN			4
	#define	MSGS_LEN			256
	#define	N_MSGS			100
	
	
	// ######################################################
	// Funciones
	// ######################################################
	void 		enviar_datos_cliente( int sockFD );
#endif