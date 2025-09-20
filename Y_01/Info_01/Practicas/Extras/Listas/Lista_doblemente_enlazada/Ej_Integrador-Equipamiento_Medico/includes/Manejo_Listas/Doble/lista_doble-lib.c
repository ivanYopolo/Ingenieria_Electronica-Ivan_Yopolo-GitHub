#include "lista_doble-lib.h"


// ########################################################
// ### Manejo de nodos ###
// ########################################################


//------------------------------------------------------------------------
// popNode - [ DONE ]
//------------------------------------------------------------------------
/* Saca un nodo de la lista (FIFO).
 * Verifiicar casos:
    * Nodo del diome.
    * Nodo final.
    * Nodo inicial.
 */
void popNode( Nodo_t *nodeX ) {
   Nodo_t *nodeAux = NULL;
   
   if ( nodeX != NULL ){
      // Caso primer nodo:
      if ( nodeX->prevNode == NULL ) {
         // Auxiliar apunta al nodo "n".
         nodeAux = nodeX;  
         
         // Apunta al nodo "n+1", elimina el anterior. 
         nodeX = nodeX->nextNode; 
         
         // "n-1" pasa a ser NULL.
         nodeX->prevNode = NULL;   
         
         free( nodeAux );    
      }else
      
      // Caso último nodo:
      if ( nodeX->nextNode == NULL ) {
         // Nodo "n-1" "NULL", elimina el actual. 
         nodeX->prevNode = NULL; 
         
         free( nodeX );
      }
      
      // Caso nodo del diome:
      if ( nodeX->nextNode != NULL && nodeX->prevNode != NULL ) {
         // Auxiliar apunta al nodo "n".
         nodeAux = nodeX;  
         // Apunta a "n-1".
         Nodo_t *backNode  = nodeX->prevNode;
         // Apunta a "n+1".
         Nodo_t *frontNode = nodeX->nextNode;
         
         // Back & Front se enlazan entre sí, perdiendo a "nodeX".
         backNode->nextNode  = frontNode;
         frontNode->prevNode = backNode;
         
         free( nodeAux );    
      }
      
   }
}


//------------------------------------------------------------------------
// pushNode - [ REV ]
//------------------------------------------------------------------------
/* Agrega un nodo a la lista (FIFO).
 * Ver manera de hacer INSERCIÓN ORDENADA.
 */
void pushNode( Nodo_t **startNode, Nodo_t *newNode ) {
   // El siguiente del Nodo nuevo apunta al viejo inicio de la lista (FIFO).
   newNode->nextNode = *startNode;
   
   // El viejo anterior deja de ser NULL y pasa a ser el nuevo Nodo.
   (*startNode)->prevNode = newNode;
   
   // El inicio de la lista es el nuevo Nodo.
   *startNode = newNode;
   
   // El anterior es el NULL.
   newNode->prevNode = NULL;
}


//------------------------------------------------------------------------
// createNode - [ DONE ]
//------------------------------------------------------------------------
/* Crea un nodo en la lista (FIFO).
 */
Nodo_t * createNode( Dato_t *datoX ) {
   // Asigna nuevo Nodo de forma DINÁMICA (queda en el HEAP).
   Nodo_t *newNode = (Nodo_t *) malloc( sizeof(Nodo_t) );
   
   // Anterior y siguiente apuntan a NULL.
   newNode->prevNode = NULL;
   newNode->nextNode = NULL;
   
   // Copia structs de DATOS.
   newNode->dato = *datoX;
   
   return newNode;
}


//------------------------------------------------------------------------
// mergeData - [ DONE ]
//------------------------------------------------------------------------
/* Junta datos repetidos (SKUs) en un mismo nodo.
 *
 * # Merge Selection #
   1) Conserva datoInput.
   2) Conserva newData.
 */
void mergeData( Dato_t *datoInput, Dato_t newData, int mergeSelection ) {
   
   datoInput->cantidad += newData.cantidad;   // Junta los Stocks.

   switch ( mergeSelection ) {
      case 1:  // Conserva datoInput.
         // Do nothing.
      break;
      
      case 2:  // Conserva newData.
         strncpy( datoInput->descripcion,   newData.descripcion,   strlen( newData.descripcion ) + 1  );
         strncpy( datoInput->detalles,      newData.detalles,      strlen( newData.detalles ) + 1     );
         datoInput->especialidad = newData.especialidad;
         datoInput->precio = newData.precio;
      break;
   }
}


// ########################################################################
// ### Ordenamiento ###
// ########################################################################

//------------------------------------------------------------------------
// sortList - [ REV ]
//------------------------------------------------------------------------
/* Ordena la lista entera (bubblesort).
 * Utiliza puntero a función dependiendo del tipo de dato a ordenar y
 * del sentido del orden.
 *
 * # ordenamiento[2] #
 * 0: Dato a ordenar.
 * 1: Sentido de ordenamiento.
 *
 * Puede ponerse de argumento el puntero a función genérico y se crea 
 * dicho puntero a función por fuera.
 * Ej.:
 * int (*ordenamientoLista[ 3 ])( Nodo_t *backNode, Nodo_t *frontNode, int orden ) = 
 *     { ordenEspecialidad, ordenPrecio, ordenDisponibilidad };
 */
void sortList( Nodo_t **startNode, int ordenamiento[], \
               int (*ordenamientoLista[])( Nodo_t *backNode, Nodo_t *frontNode, int orden ) ) {
   
   Nodo_t *nodoX = NULL;
   
   // # Verifica si la lista está ordenada o no #
   
   // Pasada externa para la lista entera.
   // Pasa la dirección de la función requerida.
   while ( !isListOrdered( *startNode, ordenamiento[1], &(*ordenamientoLista[ordenamiento[0]]) ) ) {   
      
      nodoX = *startNode;
      
      // Pasada interna por nodo.
      while ( nodoX != NULL && nodoX->nextNode != NULL ) {
         
         // Compara el nodo actual y el siguiente, si están ordenados.
         if ( (*ordenamientoLista[ordenamiento[0]])( nodoX, nodoX->nextNode, ordenamiento[1] ) == 1 ) {
         
            if ( nodoX == *startNode ) {
               // Para evitar perder el inicio de la lista, antes de 
               // cambiarlos de lugar, se guarda el "nuevo inicio".
               *startNode = nodoX->nextNode;
            }
         
            // Los Intercambia si es que cumple los criterios pedidos.
            swapNodes( nodoX, nodoX->nextNode );
            
         } else { // Si no cambia de lugar los nodos:
         
            nodoX = nodoX->nextNode;   // Pasa al siguiente nodo.
         }
      }  // Terminó de pasar por toda la lista, comparando 1 nodo en particular.
   }  // Terminó de pasar por toda la lista, con todos los nodos.
}


//------------------------------------------------------------------------
// isListOrdered - [ REV ]
//------------------------------------------------------------------------
/* Verifica si la lista entera está ordenada.
 * Sale si llega al final y verifica efectivamente su ordenamiento o si
 * NO está ordenada en algún punto.
 * Devuelve:
   - 0 si NO está ordenada.
   - 1 si está ordenada.
 *
 * # Function Pointer #
 * Esta toma 2 nodos, uno "trasero" y otro "frontal", o "n" y "n+1", además
 * de un entero de "orden" para indicar orden ascendente (ORD_ASC) o 
 * descendente (ORD_DES). 
 * Devuelve:
   - 0 si los 2 nodos NO cumplen el criterio de ordenamiento.
   - 1 si lo cumplen.
 */
int isListOrdered( Nodo_t *startNode, int orden, \
                   int (*ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) ) {
   Nodo_t *nodoX = startNode;   // Temporal como cursor, para recorrer lista.
   int ordenada = 1;
   
   while ( nodoX != NULL && ordenada != 0 ) {
      // Según el método de ordenamiento y sentido orden elegido, evalúa su estado de orden.
      if ( !(*ordenamiento)( nodoX, nodoX->nextNode, orden ) ) {
         ordenada = 0;
      }

      nodoX = nodoX->nextNode;
   }  // Sale si llega al final o si no está ordenada la lista.
   
   return ordenada;  // Ordenados naturalmente a menos que lo indique la función.
}


//------------------------------------------------------------------------
// swapNodes - [ DONE ]
//------------------------------------------------------------------------
/* Cambia los nodos de lugar.
 *
 * Nomenclatura:  
   - anterior  = n-1.
   - backNode  = n.
   - frontNode = n+1.
   - siguiente = n+2.
 *
 * Checkear casos de:
   - Nodo inicial.
   - Nodo del diome.
   - Nodo final.
 */
void swapNodes( Nodo_t *backNode, Nodo_t *frontNode ) {
   Nodo_t *anterior = NULL;      // "n-1".
   Nodo_t *siguiente = NULL;     // "n+2".

   if ( backNode != NULL && frontNode != NULL ) {
      // Caso nodo del diome:
      if ( backNode->prevNode != NULL && frontNode->nextNode != NULL ) {
         anterior = backNode->prevNode;               // "n-1".
         
         siguiente = frontNode->nextNode;             // "n+2".
         
         backNode->nextNode = siguiente;              // Next de "n" apunta a "n+2".
         
         frontNode->prevNode = anterior;              // Prev de "n+1" apunta a "n-1".
         
         backNode->prevNode = frontNode;              // Prev de "n" apunta a "n+1".
         
         frontNode->nextNode = backNode;              // Next de "n+1" apunta a "n".
         
         anterior->nextNode = frontNode;              // Next de "n-1" apunta a "n+1".
         
         siguiente->prevNode = backNode;              // Prev de "n+2" apunta a "n".
      } else {
         // Caso nodo inicial:
         if ( backNode->prevNode == NULL && frontNode->nextNode != NULL ) {
            anterior = NULL;                             // "n-1" = NULL.
            
            siguiente = frontNode->nextNode;             // "n+2".
            
            backNode->nextNode = siguiente;              // Next de "n" apunta a "n+2".
            
            frontNode->prevNode = anterior;              // Prev de "n+1" apunta a NULL.
            
            backNode->prevNode = frontNode;              // Prev de "n" apunta a "n+1".
            
            frontNode->nextNode = backNode;              // Next de "n+1" apunta a "n".
            
            siguiente->prevNode = backNode;              // Prev de "n+2" apunta a "n".
         } else {
            // Caso nodo final:
            if ( backNode->prevNode != NULL && frontNode->nextNode == NULL ) {
               anterior = backNode->prevNode;               // "n-1".
               
               siguiente = NULL;                            // "n+2" = NULL.
               
               backNode->nextNode = siguiente;              // Next de "n" apunta a NULL.
               
               frontNode->prevNode = anterior;              // Prev de "n+1" apunta a "n-1".
               
               backNode->prevNode = frontNode;              // Prev de "n" apunta a "n+1".
               
               frontNode->nextNode = backNode;              // Next de "n+1" apunta a "n".
               
               anterior->nextNode = frontNode;              // Next de "n-1" apunta a "n+1".
            }
         }
      } 
   }
}



