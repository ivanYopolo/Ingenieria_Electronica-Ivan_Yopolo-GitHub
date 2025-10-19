#ifndef LISTA_DOBLE
   #define LISTA_DOBLE
   // ########################################################
   // Includes
   // ########################################################
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>	
	#include <ctype.h>
	
   #include "struct_datos.h"		// Donde se alojan las estructuras tipo Dato_t.
   #include "debugging.h"  		// Para hacer debugging de las funciones.
   
	
   // ########################################################
   // Defines
   // ########################################################
   #define ORD_ASC            1
   #define ORD_DES            2


   // ########################################################
   // Funciones
   // ########################################################
   
   // ### Manejo de nodos ###
   void     pop_node( Nodo_t *nodeX );
   void     push_node( Nodo_t *bottom, Nodo_t *ham, Nodo_t *top );
   void     ordered_insertion( Nodo_t **startNode, Nodo_t *newNode, int sentido, \
                              int (*criterio_ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   Nodo_t * create_node( Dato_t datoX );
   void     merge_data( Dato_t *datoInput, Dato_t newData, int mergeSelection ); 
   
   // ### Ordenamiento ###
   void     sort_list( Nodo_t **startNode, int sentido, \
                              int (*criterio_ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   Nodo_t * is_list_ordered( Nodo_t *startNode, int sentido, \
                              int (*ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   void     swap_nodes( Nodo_t *backNode, Nodo_t *frontNode );
#endif

