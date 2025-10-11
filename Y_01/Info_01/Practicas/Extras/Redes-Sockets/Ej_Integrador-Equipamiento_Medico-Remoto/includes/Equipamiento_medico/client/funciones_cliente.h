#ifndef FUNCIONES_CLIENTE
   #define FUNCIONES_CLIENTE
   
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
   
   #include "../../../includes/GetString_console/getstring-lib.h"       // Obtener string del kernel.
   #include "../../../includes/Manejo_Listas/Doble/lista_doble-lib.h"   // Manejo de listas dobles.
   #include "../../debugging.h"  // Debugging de funciones.
   
   
   // ########################################################
   // Defines
   // ########################################################
   #define ORD_ESP            0
   #define ORD_PRE            1
   #define ORD_DISP           2
   
   #define ORD_ASC            1
   #define ORD_DES            2
   
   #define PORT_RD            3494     // Puerto lectura (READ).
   #define PORT_WR            3498     // Puerto escritura (WRITE).
   #define SIZE_IP            16       // IPs: 0.0.0.0 ~ 255.255.255.255
   #define SIZE_PORT          6        // Ports: 0 ~ 65535.

   // ########################################################
   // Funciones
   // ########################################################
   
   // ### Menú ###
   int      menu();                                                                    // [ DONE ]
   
   // ### Manejo de nodos ###
   void     get_user_input( Nodo_t **startNode, int sentido, \
                           int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) );        // [ DONE ]
   void     modificar_datos( Nodo_t **startNode );                                     // [ DONE ]
   void     eliminate_data( Nodo_t **startNode );                                      // [ DONE ] 
   
   // ### Especiales ###
   void     show_data( Dato_t datoX );                                                 // [ DONE ]
   void     close_session( Nodo_t *startNode, char *fechaStr );                        // [ DONE ]
   Nodo_t * is_SKU_repeated( Nodo_t *startNode, int skuInput );                        // [ DONE ]
   char   * obtener_fecha();                                                           // [ DONE ]
   
   // ### Opciones Menú ###
   void     altas_bajas_modificaciones( Nodo_t **startNode, int sentido, \
                           int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) );        // [ DONE ]
   
   char   * cargar_datos( Nodo_t **startNode, int sentido, \
                           int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) );        // [ DONE ]
   
   void     guardar_datos( Nodo_t *startNode, char *fechaAct );                                                // [ DONE ]
   
   char   * cargar_datos_remoto( int portRD, char *srvIP, Nodo_t **startNode, int sentido, \
                           int (*criterio_orden)( Nodo_t *backNode, Nodo_t *frontNode, int sentido ) );        // [ REV ]
   
   void     guardar_datos_remoto( int portWR, char *srvIP, Nodo_t *startNode, char *fechaAct );                // [ INP ]
   
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

