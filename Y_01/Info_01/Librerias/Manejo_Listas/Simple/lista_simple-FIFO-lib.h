#ifndef includes
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
   #define TAM_STR  1024

   // ########################################################
   // Funciones
   // ########################################################
   Nodo_t * createNode( Dato_t *dataX );
   void     pushNode( Nodo_t **startNode, Nodo_t *newNode );
   void     popNode( Nodo_t **startNode );
#endif