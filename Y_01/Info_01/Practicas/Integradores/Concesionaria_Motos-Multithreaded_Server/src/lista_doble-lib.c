#include "../inc/lista_doble-lib.h"


// ########################################################
// ### Manejo de nodos ###
// ########################################################

//------------------------------------------------------------------------
// pop_node - [ DONE ]
//------------------------------------------------------------------------
/* Saca un nodo de la lista.
 * Verifiicar casos:
    * Nodo del diome.
    * Nodo final.
    * Nodo inicial.
 */
void pop_node( Nodo_t *nodeX ) {
   Nodo_t *nodeAux = NULL;
   
   if ( nodeX != NULL ) {
      // Caso primer nodo:
      if ( nodeX->prevNode == NULL ) {
         
         nodeAux = nodeX;           // Auxiliar apunta al nodo "n". 
         nodeX = nodeX->nextNode;   // Apunta al nodo "n+1", elimina el anterior. 
         nodeX->prevNode = NULL;    // "n-1" pasa a ser NULL.
         
         free( nodeAux );    
      } else {
         // Caso último nodo:
         if ( nodeX->nextNode == NULL ) {
            
            nodeX->prevNode = NULL;    // Nodo "n-1" "NULL", elimina el actual. 
            
            free( nodeX );
         } else {
            // Caso nodo del diome:
            if ( nodeX->nextNode != NULL && nodeX->prevNode != NULL ) {
            
               nodeAux = nodeX;     // Auxiliar apunta al nodo "n".
               Nodo_t *backNode  = nodeX->prevNode;   // Apunta a "n-1".
               Nodo_t *frontNode = nodeX->nextNode;   // Apunta a "n+1".
               
               // Back & Front se enlazan entre sí, perdiendo a "nodeX".
               backNode->nextNode  = frontNode;
               frontNode->prevNode = backNode;
               
               free( nodeAux );    
            }
         }
      }
   }
}


//------------------------------------------------------------------------
// push_node - [ REV ]
//------------------------------------------------------------------------
/* Agrega un nodo a la lista entre otros 2 nodos.
 *
 * Verificar casos:
      - Primer nodo:
 *
 * bottom: nodo anterior al nuevo a agregar.
 * ham: nuevo nodo a agregar a la lista.
 * top: nodo posterior al nuevo a agregar.
 */
void push_node( Nodo_t **startNodePUSH, Datos_t inputDataPUSH ) {
	Nodo_t		*newNodePUSH = NULL;
	Nodo_t		*nodoNext = NULL;
   
	
   if ( (*startNodePUSH) == NULL ) {
		(*startNodePUSH) = create_node( inputDataPUSH );
   } else {
		newNodePUSH = create_node( inputDataPUSH );
		nodoNext = startNodePUSH->nodoSig;
		
		newNodePUSH->nodoPrev = NULL;
		newNodePUSH->nodoSig = startNodePUSH->nodoSig;
		
		nodoNext->nodoPrev = newNodePUSH;
		startNodePUSH->nodoSig = newNodePUSH;
	}
}


//------------------------------------------------------------------------
// create_node - [ DONE ]
//------------------------------------------------------------------------
/* Crea un nodo en la lista.
 */
Nodo_t * create_node( Datos_t datoX ) {

   // Asigna nuevo Nodo de forma DINÁMICA (queda en el HEAP).
   Nodo_t *newNode = (Nodo_t *) malloc( sizeof(Nodo_t) );
   
   // Anterior y siguiente apuntan a NULL.
   newNode->prevNode = NULL;
   newNode->nextNode = NULL;
   
   // Copia los contenidos de los structs tipo "Datos_t".
   newNode->datos = datoX;
   
   return newNode;
}


//------------------------------------------------------------------------
// merge_data - [ DONE ]
//------------------------------------------------------------------------
/* Junta datos repetidos en un mismo nodo.
 *
 * # Merge Selection #
   1) Conserva datoInput.
   2) Conserva newData.
 */
void merge_data( Datos_t *datoInput, Datos_t newData, int mergeSelection ) {
   
   datoInput->cantidad += newData.cantidad;   // Junta los Stocks.

   switch ( mergeSelection ) {
      case 1:  // Conserva "datoInput".
         // Do nothing.
      break;
      
      case 2:  // Conserva "newData".
         strncpy( datoInput->descripcion,   newData.descripcion,   strlen( newData.descripcion ) + 1  );
         strncpy( datoInput->detalles,      newData.detalles,      strlen( newData.detalles ) + 1     );
         datoInput->especialidad = newData.especialidad;
         datoInput->precio = newData.precio;
      break;
   }
}



