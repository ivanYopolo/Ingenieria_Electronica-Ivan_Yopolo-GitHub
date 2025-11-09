#ifndef INCLUDES_CLIENT
	#define 	INCLUDES_CLIENT
	
	// ######################################################
	// Includes
	// ######################################################
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <pthread.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <ctype.h>
	#include <sys/socket.h>
	
	#include "sock-lib.h"
	#include "getstring-lib.h"
	#include "data_motos.h"
	
	
	// ######################################################
	// Defines
	// ######################################################
	#define 	ABM				1
	#define	GUARDAR			2
	#define	VISUAL_LOCAL	3
	#define	VISUAL_SERVER	4
	
	
	// ######################################################
	// Variables externas
	// ######################################################
	extern int 					threadCount;
	extern pthread_mutex_t	lockSave;
	
	
	// ######################################################
	// Funciones
	// ######################################################
	int 		show_menu();
	void		cargar_datos_casa_central( Nodo_t **startNodeLOAD, int sockfdLOAD );
	void		abm_lista( Nodo_t **startNodeABM );
	void		alta_datos( Nodo_t **startNodeABM );
	void		baja_datos( Nodo_t **startNodeABM );
	void		mod_datos( Nodo_t **startNodeABM );
	void		guardar_datos( Nodo_t *startNodeSAVE, int localDatafdSAVE, int sockfdSAVE );
	void		visualizar_lista_local( Nodo_t *startNodeVISUAL );
	void		visualizar_lista_remoto( int sockfdVISUAL );
	void 		sincronizar( Nodo_t **startNodeSYNC, int localDatafdSYNC, int sockfdSYNC );
	void 		end_session( Nodo_t *startNodeEND, int sockfdEND, int localDatafdEND );
#endif