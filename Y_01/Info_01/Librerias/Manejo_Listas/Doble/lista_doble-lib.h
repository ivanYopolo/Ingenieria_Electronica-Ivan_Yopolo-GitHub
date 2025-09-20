#ifndef lista_doble-lib
   // ########################################################
   // Includes
   // ########################################################
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>	
	#include <ctype.h>
   
   // ########################################################
   // Defines
   // ########################################################
   #define TAM_STR            1024
   
   #define ORD_ASC            1
   #define ORD_DES            2

   // ########################################################
   // Funciones
   // ########################################################
   
   // ### Manejo de nodos ###
   void     popNode( Nodo_t **nodeX );
   void     pushNode( Nodo_t **startNode, Nodo_t *newNode );
   Nodo_t * createNode( Dato_t *datoX );
   void     mergeData( Nodo_t *nodoX, Dato_t datoInput, int mergeSelection ); 
   
   
   // ### Ordenamiento ###
   void     sortList( Nodo_t **startNode, const int ordenamiento[], \
                      int (*ordenamientoLista)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   int      isListOrdered( const Nodo_t *startNode, \
                           int (*ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   void     swapNodes( Nodo_t *backNode, Nodo_t *frontNode );
#endif

