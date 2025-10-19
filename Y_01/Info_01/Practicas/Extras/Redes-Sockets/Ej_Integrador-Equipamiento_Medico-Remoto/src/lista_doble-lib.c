#include "../inc/lista_doble-lib.h"
#include "../inc/debugging.h"


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
void push_node( Nodo_t *bottom, Nodo_t *ham, Nodo_t *top ) {
   // # LOG #
   int      fdLog;
   fdLog = open( "./log/push_node.log", O_WRONLY | O_CREAT | O_TRUNC, 0666 );
   dprintf( fdLog, "------------------------------------------------------------------------\n" );
   dprintf( fdLog, "# Pushing... #\n" );
   dprintf( fdLog, "------------------------------------------------------------------------\n\n" );
   
   if ( ham != NULL ) {
      ham->prevNode = bottom;
      ham->nextNode = top;
      
      if ( bottom == NULL && top != NULL ) {          // Caso nodo al inicio.
         top->prevNode = ham;
         
         // # LOG #
         dprintf( fdLog, "[ Nodo inicial. ]\n" );
         
      } else {
         if ( bottom != NULL && top == NULL ) {       // Caso nodo al final.
            bottom->nextNode = ham;
            
            // # LOG #
            dprintf( fdLog, "[ Nodo final. ]\n" );
            
         } else {
            if ( bottom != NULL && top != NULL ) {    // Caso nodo al diome.
               bottom->nextNode = ham;
               top->prevNode = ham;
               
               // # LOG #
               dprintf( fdLog, "[ Nodo al diome. ]\n" );
            }
         }
      }
   }
   
   // # LOG #
   close( fdLog );
}


//------------------------------------------------------------------------
// ordered_insertion - [ REV ]
//------------------------------------------------------------------------
/* Revisa la lista entera e inserta el nuevo nodo de forma ordenada.
 * Con el puntero a función, checkea el punto exacto donde meter el nodo.
 *
 * Con (criterio_ordenamiento), checkea si "anterior" va antes de "newNode" 
 * y este antes de "posterior" según el criterio de ordenamiento deseado
 * (puntero a función).
 */
void ordered_insertion( Nodo_t **startNode, Nodo_t *newNode, int sentido, \
                        int (*criterio_ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) ) {
   Nodo_t   *anterior = NULL;
   Nodo_t   *posterior = NULL;
   int      ordenados = 0;
   
   // # LOG #
   Nodo_t   *nodoCursor = NULL;
   int      fdLog;
   fdLog = open( "./log/ordered_insertion.log", O_WRONLY | O_CREAT | O_TRUNC, 0666 );
   
   if ( newNode != NULL ) {
      
      if ( *startNode == NULL ) {   // Caso particular: lista vacía.
         *startNode = newNode;
      } else {    // Inserta el nodo donde corresponda.
         
         anterior = NULL;
         posterior = *startNode;
         
         while ( posterior != NULL && ordenados == 0 ) {  // Compara el orden entre "posterior", el siguiente y "newNode".
            // # LOG #
            dprintf( fdLog, "[ Comparando si el nuevo nodo va entre " );
            
            if ( anterior != NULL && posterior != NULL )
               dprintf( fdLog, "%d y %d ]\n", anterior->dato.sku, posterior->dato.sku );
            
            if ( anterior == NULL && posterior != NULL )
               dprintf( fdLog, "NULL y %d ]\n", posterior->dato.sku );
            
            if ( anterior != NULL && posterior == NULL )
               dprintf( fdLog, "%d y NULL ]\n", anterior->dato.sku );
            
            // Orden ASC:                    anterior >= newNode >= posterior.
            // Orden DES:                    anterior <= newNode <= posterior.
            if ( ( (*criterio_ordenamiento)( anterior, newNode, sentido ) ) && \
                 ( (*criterio_ordenamiento)( newNode, posterior, sentido ) ) ) {  // Caso al diome.
               // "newNode" va entre "anterior" y "posterior".
               ordenados = 1;
               
            } 
            
            if ( ordenados != 1 ) {
               // Sigue escaneando la lista. 
               anterior = posterior;
               posterior = posterior->nextNode;
            }
            
            dprintf( fdLog, "[ Ordenados:\t\t%d ]\n\n", ordenados );
         }  // "posterior" llega a NULL si NO está la lista ordenada con el nuevo dato.
         
         push_node( anterior, newNode, posterior );
         
         
         // # LOG #
         if ( anterior != NULL && posterior != NULL )
            dprintf( fdLog, "### Nuevo dato (%d) va entre %d y %d. ###\n\n", newNode->dato.sku, anterior->dato.sku, posterior->dato.sku );
         
         if ( anterior == NULL && posterior != NULL )
            dprintf( fdLog, "### Nuevo dato (%d) va entre NULL y %d. ###\n\n", newNode->dato.sku, posterior->dato.sku );
         
         if ( anterior != NULL && posterior == NULL )
            dprintf( fdLog, "### Nuevo dato (%d) va entre %d y NULL. ###\n\n", newNode->dato.sku, anterior->dato.sku );
         
         
         while ( (*startNode)->prevNode != NULL ) {  // Corrección del START NODE.
            (*startNode) = (*startNode)->prevNode;
         }
      }  // Terminó con lista no vacía.
      
      // # LOG #
      nodoCursor = *startNode;
      dprintf( fdLog, "------------------------------------------------------------------------\n"
                      "Nueva inserción ordenada...\n"
                      "------------------------------------------------------------------------\n" );
      
      while ( nodoCursor != NULL ) {
         show_data_log( nodoCursor->dato, fdLog );
      
         nodoCursor = nodoCursor->nextNode;
      }  // Llegó al final de la lista.
      close( fdLog );
   }
}

//------------------------------------------------------------------------
// create_node - [ DONE ]
//------------------------------------------------------------------------
/* Crea un nodo en la lista.
 */
Nodo_t * create_node( Dato_t datoX ) {
   // # LOG #
   int fdLog = open( "./log/create_node.log", O_WRONLY | O_CREAT | O_TRUNC, 0666 );
   dprintf( fdLog, "\n------------------------------------------------------------------------\n" );
   dprintf( fdLog, "### \tNodo creado\t###\n" );

   // Asigna nuevo Nodo de forma DINÁMICA (queda en el HEAP).
   Nodo_t *newNode = (Nodo_t *) malloc( sizeof(Nodo_t) );
   
   // # LOG #
   dprintf( fdLog, "[ Nodo:\t%p ]", (void *)newNode );
   
   // Anterior y siguiente apuntan a NULL.
   newNode->prevNode = NULL;
   newNode->nextNode = NULL;
   
   // Copia los contenidos de los structs tipo "Dato_t".
   newNode->dato = datoX;
   
   // # LOG #
   close( fdLog );
   
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
void merge_data( Dato_t *datoInput, Dato_t newData, int mergeSelection ) {
   
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


// ########################################################################
// ### Ordenamiento ###
// ########################################################################

//------------------------------------------------------------------------
// sort_list - [ REV ]
//------------------------------------------------------------------------
/* Ordena la lista entera (bubblesort).
 * Utiliza puntero a función dependiendo del tipo de dato a ordenar y
 * del sentido del orden.
 *
 * # ordenamiento[2] #
 * [0]: Dato a ordenar.
 * [1]: Sentido de ordenamiento.
 *
 * Puede ponerse de argumento el puntero a función genérico y se crea 
 * dicho puntero a función por fuera.
 * Ej.:
 * int (*criterio_ordenamiento[ 3 ])( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) = 
 *     { ordenEspecialidad, ordenPrecio, ordenDisponibilidad };
 */
void sort_list( Nodo_t **startNode, int sentido, \
               int (*criterio_ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) ) {
   Nodo_t   *nodoX = NULL;
   
   // # LOG #
   int      fdLog;
   fdLog = open( "./log/sort_list.log", O_WRONLY | O_TRUNC | O_CREAT, 0666 );
   
   // Pasada externa para la lista entera.
   // Pasa la dirección de la función requerida.
   while ( ( nodoX = is_list_ordered( *startNode, sentido, (criterio_ordenamiento) ) ) != NULL ) {   
      
      // Pasada interna por nodo.
      while ( nodoX != NULL && nodoX->nextNode != NULL ) {
      
         // # LOG #
         dprintf( fdLog, "\n------------------------------------------------------------------------\n" );
         dprintf( fdLog, "Nueva pasada de ordenamiento...\n" );
         dprintf( fdLog, "------------------------------------------------------------------------\n\n" );
         if ( nodoX->nextNode != NULL )
            dprintf( fdLog, "[ Comparando productos: \t%d && %d ]\n", nodoX->dato.sku, (nodoX->nextNode)->dato.sku );
         
         // Compara el nodo actual y el siguiente, si están ordenados.
         if ( (*criterio_ordenamiento)( nodoX, nodoX->nextNode, sentido ) == 0 ) {
            // # LOG #
            dprintf( fdLog, "### CAMBIO ###\n\n" );
         
            // Para evitar perder el inicio de la lista, antes de cambiarlos de lugar, 
            // se guarda el "nuevo inicio".
            if ( nodoX == *startNode ) {  // Caso particular: principio de la lista.
               *startNode = nodoX->nextNode;
            }
            swap_nodes( nodoX, nodoX->nextNode );
            
         } else { // Si están ordenados, pasa de largo:
            nodoX = nodoX->nextNode;
         }
      }  // Terminó de pasar por toda la lista, comparando 1 nodo en particular.
   }  // Terminó de pasar por toda la lista, con todos los nodos.
   
   close( fdLog );
}


//------------------------------------------------------------------------
// is_list_ordered - [ REV ]
//------------------------------------------------------------------------
/* Verifica si la lista entera está ordenada.
 * Sale si llega al final y verifica efectivamente su ordenamiento o si
 * NO está ordenada en algún punto.
 * Devuelve:
 *
   - Dirección de "nodoX" si NO está ordenada; la dirección del nodo
     que no está ordenado respecto del siguiente.
 *    
   - NULL si está ordenada.
 *
 * # Function Pointer #
 * Esta toma 2 nodos, uno "trasero" y otro "frontal", o "n" y "n+1", además
 * de un entero de "sentido" para indicar orden ascendente (ORD_ASC) o 
 * descendente (ORD_DES). 
 * Devuelve:
 *
   - 0 si los 2 nodos NO cumplen el criterio de ordenamiento.
 *
   - 1 si lo cumplen.
 */
Nodo_t * is_list_ordered( Nodo_t *startNode, int sentido, \
                          int (*ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) ) {
   Nodo_t *nodoX = startNode;   // Temporal como cursor, para recorrer lista.
   int ordenada = 1;
   
   while ( nodoX != NULL && ordenada != 0 ) {
      // Según el método de ordenamiento y sentido orden elegido, evalúa su estado de orden.
      if ( (*ordenamiento)( nodoX, nodoX->nextNode, sentido ) == 0 ) {
         ordenada = 0;
      } else {
         nodoX = nodoX->nextNode;
      }
   }  // Sale si llega al final o si no está ordenada la lista.
   
   return nodoX;  // Ordenados naturalmente (NULL) a menos que lo indique la función.
}


//------------------------------------------------------------------------
// swap_nodes - [ DONE ]
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
void swap_nodes( Nodo_t *backNode, Nodo_t *frontNode ) {
   Nodo_t *anterior = NULL;      // "n-1".
   Nodo_t *siguiente = NULL;     // "n+2".

   if ( backNode != NULL && frontNode != NULL ) {
      if ( backNode->prevNode != NULL && frontNode->nextNode != NULL ) {         // Caso nodo del diome:
         anterior = backNode->prevNode;               // "n-1".
         
         siguiente = frontNode->nextNode;             // "n+2".
         
         backNode->nextNode = siguiente;              // Next de "n" apunta a "n+2".
         
         frontNode->prevNode = anterior;              // Prev de "n+1" apunta a "n-1".
         
         backNode->prevNode = frontNode;              // Prev de "n" apunta a "n+1".
         
         frontNode->nextNode = backNode;              // Next de "n+1" apunta a "n".
         
         anterior->nextNode = frontNode;              // Next de "n-1" apunta a "n+1".
         
         siguiente->prevNode = backNode;              // Prev de "n+2" apunta a "n".
      } else if ( backNode->prevNode == NULL && frontNode->nextNode != NULL ) {  // Caso nodo inicial:
         anterior = NULL;                             // "n-1" = NULL.
         
         siguiente = frontNode->nextNode;             // "n+2".
         
         backNode->nextNode = siguiente;              // Next de "n" apunta a "n+2".
         
         frontNode->prevNode = anterior;              // Prev de "n+1" apunta a NULL.
         
         backNode->prevNode = frontNode;              // Prev de "n" apunta a "n+1".
         
         frontNode->nextNode = backNode;              // Next de "n+1" apunta a "n".
         
         siguiente->prevNode = backNode;              // Prev de "n+2" apunta a "n".
      } else if ( backNode->prevNode != NULL && frontNode->nextNode == NULL ) {  // Caso nodo final:
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



