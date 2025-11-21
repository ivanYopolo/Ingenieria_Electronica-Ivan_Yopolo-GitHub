/* # 03-Inserción Ordenada #
 * Compilación:
 * clear; gcc -Wall --pedantic-errors main.c -o ../bin/prog.bin
 */

#include "../inc/includes.h"


// ------------------------------------------------------
// insertar
// ------------------------------------------------------
/* Inserta un nodo de manera ordenada, segun "dat".
 * Se tiene que crear un nuevo nodo con la info de "dat",
 * tomando a "INI" como el nodo inicial.
 * Se asume resto de la lista ordenada.
 *
 * # Orden ASCENDENTE #
 *
 * # LISTA DOBLE #
 *
 * # RETURN #
 * 0:		nodo insertado exitosamente.
 * -1:	no se pudo insertar nodo.
 */
/* # Pseudo-código #
 * Declarar una flag "searching".
 * Crear estructura de datos con "dat".
 * Crear un nodo con estructura de "dat" y punteros a NULL.
 * Asignar un nodo a un puntero auxiliar para recorrer la lista doble.
 *
 * SI ( "INI" es NULL, o sea, lista vacía )
 *	   Asigna la dirección del nodo de "dat" al puntero "*INI".
 *		Status es 0.
 * Fin SI.
 * SINÓ
 *	  "searching" empieza en 1.
 *	  MIENTRAS ( el puntero auxiliar NO sea NULL && el siguiente NO sea NULL && "searching" sea 1 )		// Recorre la lista.
 *      SI ( "dat" es mayor o igual que el nodo auxiliar y "dat" es menor o igual que el anterior al nodo auxiliar )
 *         "searching" se hace 0.		// Deja de buscar, encontró el lugar apropiado para insertar el nodo.
 *      Fin SI.
 *      SINÓ
 *         Puntero auxiliar apunta al siguiente nodo.
 *      Fin SINÓ.
 *   Fin MIENTRAS.	// Caso límite: siguiente = NULL.
 *   Insertar el nodo entre el puntero auxiliar y el siguiente.
 * Fin SINÓ.
 * 
 * 
 * Retornar el valor de status de inserción (0: exitoso; -1: falló).
 */
int insertar( Nodo_t **INI, int dat ) {
	// INI: inicio de lista.
	// dat: dato a meter en estructura de datos y en un nodo nuevo.
	char		insertionStatus = -1;
	char		searching = 1;
	Nodo_t	*newNode = NULL;
	Nodo_t	*listCurrCursor = NULL;
	Nodo_t	*listNextCursor = NULL;
	
	
	// # Creación del nuevo nodo #
	newNode = (Nodo_t *) malloc( sizeof (Nodo_t) );
	
	if ( newNode == NULL ) {	// No se pudo reservar memoria.
		insertionStatus = -1;
	} else {
		insertionStatus = 0;
		
		newNode->dato.num = dat;
		newNode->prevNode = NULL;
		newNode->nextNode = NULL;
		
		// # Lógica de inserción ordenada #
		if ( (*INI) == NULL ) {		// Lista vacía.
			(*INI) = newNode;			// Nuevo nodo -> inicio de la lista.v
			
		} else {		// Caso general.
			searching = 1;
			listCurrCursor = NULL;
			listNextCursor = (*INI);
			
			if ( newNode->dato.num <= (*INI)->dato.num ) {	// Caso nodo a principio de lista.
				searching = 0;
				// Como "listCurrCursor" es NULL y "listNextCursor" es (*INI), en la inserción se ordena correctamente.
			} else {
				listCurrCursor = listNextCursor;
				listNextCursor = listNextCursor->nextNode;
			}
			
			while ( (listNextCursor != NULL) && (searching == 1) ) {
				
				// Orden Ascendente.
				if ( (listNextCursor->dato.num <= newNode->dato.num) && (newNode->dato.num <= listCurrCursor->dato.num) ) {
					searching = 0;
				} else {
					
					listCurrCursor = listNextCursor;
					listNextCursor = listNextCursor->nextNode;
				}
			}
			
			// # Inserción #
			newNode->prevNode = listCurrCursor;
			newNode->nextNode = listNextCursor;
			
			if ( listCurrCursor != NULL )		// NULL si se inserta al inicio de la lista.
				listCurrCursor->nextNode = newNode;	
			
			if ( listNextCursor != NULL )		// NULL si se inserta al final de la lista.
				listNextCursor->prevNode = newNode;
		}	// Caso general: lista no vacía.
	}	// Memoria reservada exitosamente; nodo creado.
	
	
	return insertionStatus;
}