#ifndef lista_doble
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
   #define ORD_ASC            1
   #define ORD_DES            2
   
   #define TAM_DATE           11
   #define TAM_DESC           20
   #define TAM_DET            200

   // ########################################################
   // Dato_t
   // ########################################################
   typedef struct equipamiento{
      int   sku;                       // Identificador de modelo (puede repetirse).
      char  descripcion[ TAM_DESC ];
      char  detalles[ TAM_DET ];
      int   cantidad;                  // Disponibilidad / Stock.
      int   especialidad;
      float precio;
   } Dato_t;
   /* Cada NODO de la lista va a ser un SKU de equipamiento.
    * Los IDs se repiten si los SKUs también se repiten.
    */
   
   // ########################################################
   // Nodo_t
   // ########################################################
   typedef struct Nodo_s{
      struct Nodo_s *prevNode;
      struct Nodo_s *nextNode;
      Dato_t         dato;
   } Nodo_t;

   // ########################################################
   // Funciones
   // ########################################################
   
   // ### Manejo de nodos ###
   void     popNode( Nodo_t *nodeX );
   void     pushNode( Nodo_t **startNode, Nodo_t *newNode );
   Nodo_t * createNode( Dato_t *datoX );
   void     mergeData( Dato_t *datoInput, Dato_t newData, int mergeSelection ); 
   
   // ### Ordenamiento ###
   void     sortList( Nodo_t **startNode, int ordenamiento[], \
                      int (*ordenamientoLista[])( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   int      isListOrdered( Nodo_t *startNode, int orden, \
                           int (*ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   void     swapNodes( Nodo_t *backNode, Nodo_t *frontNode );
#endif

