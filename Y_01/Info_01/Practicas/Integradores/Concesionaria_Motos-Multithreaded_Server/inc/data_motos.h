#ifndef DATA_MOTOS
	#define 		DATA_MOTOS
	
	
	// ######################################################
	// Includes
	// ######################################################
	#include 	<pthread.h>
	
	
	// ######################################################
	// Defines
	// ######################################################
	#define 		NUM_LENGTH	19
	
	// # Datos de vehículos #
	typedef struct 	Datos_s {
		int 						serialNum;
		float 					precio;
		int 						stock;
	} Datos_t;
	
	// # Nodos individuales de la lista #
	typedef struct 	Nodo_s {					// Lista doble de Datos.
		struct Nodo_s			*nodoPrev;
		struct Datos_s			datos;
		struct Nodo_s			*nodoSig;
	} Nodo_t;
	
	// # Datos de cada sucursal #
	typedef struct 	Sucursal_s {
		int						nombre;
		char						numeroTelefono[NUM_LENGTH];
		// int A
	} Sucursal_t;
	
	// # Datos de TODO el sistema; lista de listas (guirnalda) #
	typedef struct 	Guirnalda_s {			// Lista doble de Sucursales.
		pthread_t				tidSucursal;	// TID de la sucursal.
		struct Guirnalda_s	*listaPrev;
		struct Nodo_s			*listaStart;	// Lista de datos de la Sucursal.
		struct Sucursal_s		datosSucursal;	// Datos de la sucursal.
		struct Guirnalda_s	*listaSig;
	} Guirnalda_t;
	
	// # Estado de thread individual + TID propio #
	typedef struct 	ThreadStatus_s {
		pthread_t				tidSucursal;	// TID de la sucursal.
		char						didFinish;		// ¿Terminó?
	} ThreadStatus_t;
#endif