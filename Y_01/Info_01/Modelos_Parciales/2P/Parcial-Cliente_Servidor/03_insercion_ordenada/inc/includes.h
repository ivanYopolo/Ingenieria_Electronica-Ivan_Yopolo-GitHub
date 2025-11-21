#ifndef INCLUDES
	#define INCLUDES
	
	// ######################################################
	// Includes
	// ######################################################
	
	
	// ######################################################
	// Defines
	// ######################################################
	
	typedef struct Dato_s {
		int				num;
	} Dato_t;
	
	typedef struct Nodo_s {
		struct Nodo_s	*prevNode; 
		Dato_t			dato;
		struct Nodo_s	*nextNode; 
	} Nodo_t;
	
	// ######################################################
	// Funciones
	// ######################################################
	int 	insertar( Nodo_t **INI, int dat );
#endif