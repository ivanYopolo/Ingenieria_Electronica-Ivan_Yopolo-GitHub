#ifndef LISTA_DOBLE
	#define 	LISTA_DOBLE
	
	// ######################################################
	// Includes
	// ######################################################
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <ctype.h>
	// #include <sys/socket.h>
	
	#include "getstring-lib.h"
	#include "data_motos.h"
	
	
	// ######################################################
	// Defines
	// ######################################################
	
	
	
	// ######################################################
	// Funciones
	// ######################################################
	
   // ### Manejo de nodos ###
   void     pop_node( Nodo_t *nodePOP );
   void     push_node( Nodo_t **startNodePUSH, Nodo_t *newNodePUSH );
   Nodo_t * create_node( Dato_t newDataCREATE );
   void     merge_data( Dato_t *datoInputMERGE, Dato_t newDataMERGE, int mergeSelection ); 
   
   // ### Ordenamiento ###
	/*
   void     sort_list( Nodo_t **startNode, int sentido, \
                              int (*criterio_ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   Nodo_t * is_list_ordered( Nodo_t *startNode, int sentido, \
                              int (*ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   void     swap_nodes( Nodo_t *backNode, Nodo_t *frontNode );
	*/
#endif