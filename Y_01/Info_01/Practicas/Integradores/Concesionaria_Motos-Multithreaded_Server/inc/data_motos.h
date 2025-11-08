#ifndef DATA_MOTOS
	#define 		DATA_MOTOS
	
	#define 		NUM_LENGTH	19
	
	#include 	<pthread.h>
	
	typedef struct 	Datos_s {
		int 						stock;
		int 						serialNum;
		float 					precio;
	} Datos_t;
	
	typedef struct 	Nodo_s {					// Lista doble de Datos.
		struct Nodo_s			*nodoPrev;
		struct Datos_s			datos;
		struct Nodo_s			*nodoSig;
	} Nodo_t;
	
	typedef struct 	Sucursal_s {
		int						nombre;
		char						numeroTelefono[NUM_LENGTH];
		// int A
	} Sucursal_t;
	
	typedef struct 	Guirnalda_s {			// Lista doble de Sucursales.
		pthread_t				tidSucursal;	// TID de la sucursal.
		struct Guirnalda_s	*listaPrev;
		struct Nodo_s			*listaStart;	// Lista de datos de la Sucursal.
		struct Sucursal_s		datosSucursal;	// Datos de la sucursal.
		struct Guirnalda_s	*listaSig;
	} Guirnalda_t;
	
	typedef struct 	ThreadStatus_s {
		pthread_t				tidSucursal;	// TID de la sucursal.
		char						didFinish;		// ¿Terminó?
	} ThreadStatus_t;
#endif