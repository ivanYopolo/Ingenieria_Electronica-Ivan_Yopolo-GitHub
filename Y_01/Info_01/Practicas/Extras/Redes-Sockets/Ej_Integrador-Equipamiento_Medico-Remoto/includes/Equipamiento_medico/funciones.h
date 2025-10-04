#ifndef funciones
   // ########################################################
   // Includes
   // ########################################################
   #include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>	
	#include <ctype.h>
   #include <time.h>
   
   #include "../../includes/GetString_console/getstring-lib.h"       // Obtener string del kernel.
   #include "../../includes/Manejo_Listas/Doble/lista_doble-lib.h"   // Manejo de listas dobles.
   #include "../debugging.h"  // Debugging de funciones.
   
   // ########################################################
   // Defines
   // ########################################################

   #define ORD_ESP            1
   #define ORD_PRE            2
   #define ORD_DISP           3
   
   #define ORD_ASC            1
   #define ORD_DES            2

   #define CARDIOLOGIA        1
   #define CLINICA            2
   #define GASTROENTEROLOGIA  3
   #define CIRUGIA            4
   #define DEREMATOLOGIA      5
   #define OFTALMOLOGIA       6
   #define TRAUMATOLOGIA      7
   

   // ########################################################
   // Funciones
   // ########################################################
   
   // ### Menú ###
   int      menu();                                                                    // [ DONE ]
   
   // ### Manejo de nodos ###
   void     get_user_input( Nodo_t **startNode, int sentido, \
                           int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) );     // [ REV ] - Ver inserción ordenada.
   void     modificar_datos( Nodo_t **startNode );                                     // [ REV ]
   void     eliminate_data( Nodo_t *startNode );                                       // [ REV ] 
   
   // ### Especiales ###
   void     show_data( Dato_t datoX );                                                 // [ DONE ]
   void     close_session( Nodo_t *startNode, char *fechaStr );                        // [ DONE ]
   Nodo_t * is_SKU_repeated( Nodo_t *startNode, int skuInput );                        // [ REV ]
   char   * obtener_fecha();                                                           // [ DONE ]
   
   // ### Opciones Menú ###
   char   * cargar_datos( Nodo_t **startNode, int sentido, \
                           int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) );     // [ REV ]
   void     altas_bajas_modificaciones( Nodo_t **startNode, int sentido, \
                           int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) );     // [ REV ]
   void     guardar_datos( Nodo_t *startNode, char *fechaAct );                        // [ REV ]
   void     ordenar_datos( Nodo_t **startNode, int ordenamiento[], \
                           int (*ordenamiento_lista[3])( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );   // [ DONE ]
   void     mostrar_datos( Nodo_t *startNode, const int mode );                        // [ DONE ]
   char   * mostrar_fecha( char *fechaTemp );                                          // [ DONE ]
   
   // ### Ordenamiento ###
   // Por puntero a función:
   int      orden_especialidad( Nodo_t *backNode, Nodo_t *frontNode, int orden );      // [ DONE ]
   int      orden_precio( Nodo_t *backNode, Nodo_t *frontNode, int orden );            // [ DONE ]
   int      orden_disponibilidad( Nodo_t *backNode, Nodo_t *frontNode, int orden );    // [ DONE ]
#endif

