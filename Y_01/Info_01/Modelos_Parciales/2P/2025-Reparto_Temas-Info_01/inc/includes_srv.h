#ifndef INCLUDES_SRV
	#define INCLUDES_SRV
	
	// #################################################################################
	// Includes
	// #################################################################################
	#include <pthread.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>	
	#include <ctype.h>
	#include <time.h>
	#include "sock-lib.h"
	
	
	// #################################################################################
	// Defines
	// #################################################################################
	#define	MAX_BUF_SIZE	1024
	#define	TEMA_LEN			19
	#define	FALSE 			0
	#define	TRUE 				1
	
	typedef struct alumno {
		int 				legajo;
		int 				DNI;
		char 				nombre[20];
		char 				apellido[20];
		int 				repartido;
		int 				banned;
	} Alumno_t;
	
	
	typedef struct nodo {
		struct nodo 	*prevNode;
		Alumno_t			dato;
		struct nodo 	*nextNode;
	} Nodo_t;
	
	
	typedef struct	ThreadArg_s {
		int 				inputFd;
		Nodo_t			**startList;
	} ThreadArg_t;
	
	
	// #################################################################################
	// Funciones
	// #################################################################################
	int 				manejar_alumnos( int port );
	void 				cargar_lista_archivo( int archivoFd, Nodo_t **inicioLista );
	void 				*validacion_alumno( void *args );	// MULTI-THREADED.
	void 				create_test_data();
	void 				show_list( Nodo_t *startNodeShow );
#endif