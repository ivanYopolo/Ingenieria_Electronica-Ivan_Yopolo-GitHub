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
   
   #include "../GetString_console/getstring-lib.h"
   #include "../Manejo_Listas/Doble/lista_doble-lib.h"
   
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
   int      menu();                                                                 // [ DONE ]
   
   // ### Manejo de nodos ###
   Nodo_t * getUserInput( Nodo_t **startNode );                                     // [ DONE ]
   
   // ### Especiales ###
   void     showData( Dato_t datoX );                                               // [ DONE ]
   void     closeSession( Nodo_t *startNode, char *fechaStr, int fdData );          // [ DONE ]
   Nodo_t * isSKURepeated( Nodo_t *startNode, int skuInput );                       // [ REV ]
   char   * obtenerFecha();                                                         // [ DONE ]
   
   // ### Opciones Menú ###
   char   * cargarDatos();                                                          // [ REV ]
   void     modificarDatos( Nodo_t *startNode );                                    // ---
   void     guardarDatos( Nodo_t *startNode, char *fechaAct );                      // [ REV ]
   void     ordenarDatos( Nodo_t **startNode, int ordenamiento[] );                 // [ DONE ]
   void     mostrarDatos( Nodo_t *startNode );                                      // [ DONE ]
   char   * mostrarFecha( char *fechaTemp );                                        // [ REV ]
   
   // ### Ordenamiento ###
   // Por puntero a función:
   int      ordenEspecialidad( Nodo_t *backNode, Nodo_t *frontNode, int orden );    // [ DONE ]
   int      ordenPrecio( Nodo_t *backNode, Nodo_t *frontNode, int orden );          // [ DONE ]
   int      ordenDisponibilidad( Nodo_t *backNode, Nodo_t *frontNode, int orden );  // [ DONE ]
#endif

