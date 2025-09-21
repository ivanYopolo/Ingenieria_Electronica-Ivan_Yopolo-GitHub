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
   typedef struct equipamiento {
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
   typedef struct Nodo_s {
      struct Nodo_s *prevNode;
      struct Nodo_s *nextNode;
      Dato_t         dato;
   } Nodo_t;

   // ########################################################
   // Funciones
   // ########################################################
   
   // ### Manejo de nodos ###
   void     pop_node( Nodo_t *nodeX );
   void     push_node( Nodo_t *bottom, Nodo_t *ham, Nodo_t *top );
   void     ordered_insertion( Nodo_t **startNode, Nodo_t *newNode, int sentido, \
                              int (*criterio_ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   Nodo_t * create_node( Dato_t *datoX );
   void     merge_data( Dato_t *datoInput, Dato_t newData, int mergeSelection ); 
   
   // ### Ordenamiento ###
   void     sort_list( Nodo_t **startNode, int sentido, \
                              int (*criterio_ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   Nodo_t * is_list_ordered( Nodo_t *startNode, int sentido, \
                              int (*ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );
   void     swap_nodes( Nodo_t *backNode, Nodo_t *frontNode );
#endif

