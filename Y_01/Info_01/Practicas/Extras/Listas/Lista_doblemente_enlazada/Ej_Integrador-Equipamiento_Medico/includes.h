#ifndef includes
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
   
   // ########################################################
   // Defines
   // ########################################################
   #define TAM_DATE           11
   #define TAM_STR            1024
   #define TAM_DESC           20
   #define TAM_DET            200

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
      Dato_t *prevNode;
      Dato_t *nextNode;
      Dato_t dato;
   } Nodo_t;

   // ########################################################
   // Funciones
   // ########################################################
   
   // ### Menú ###
   int      menu();                                                                 // [ DONE ]
   
   // ### Manejo de nodos ###
   Nodo_t * getUserInput( Nodo_t **startNode );                                     // [ DONE ]
   void     popNode( Nodo_t **nodeX );                                              // [ DONE ]
   void     pushNode( Nodo_t **startNode, Nodo_t *newNode );                        // [ REV ] - Ver inserción ordenada.
   Nodo_t * createNode( Dato_t *datoX );                                            // [ DONE ]
   
   // ### Especiales ###
   char   * writeStrD();                                                            // [ DONE ]
   void     closeSession( Nodo_t *startNode, char *fechaStr, int fdData );          // [ DONE ]
   Nodo_t * isSKURepeated( Nodo_t *startNode, Dato_t datoInput );                   // [ REV ]
   char   * obtenerFecha();                                                         // [ DONE ]
   
   // ### Opciones Menú ###
   void     cargarDatos();                                                          // ---
   void     modificarDatos( Nodo_t *startNode );                                    // ---
   void     guardarDatos( Nodo_t *startNode, char *fechaAct );                      // [ REV ]
   int      ordenarDatos( const Nodo_t *startNode, int ordenamiento[] );            // [ DONE ]
   void     mostrarDatos( Nodo_t *startNode );                                      // [ DONE ]
   char   * mostrarFecha( char *fechaTemp );                                        // [ REV ]
   
   // ### Ordenamiento ###
   void     sortList( Nodo_t **startNode, const int ordenamiento[] );               // [ REV ]
   int      isListOrdered( const Nodo_t *startNode, int (*ordenamiento)( Nodo_t *backNode, Nodo_t *frontNode, int orden ) );  // [ REV ]
   
   // Por puntero a función:
   int      ordenEspecialidad( Nodo_t *backNode, Nodo_t *frontNode, int orden );    // [ DONE ]
   int      ordenPrecio( Nodo_t *backNode, Nodo_t *frontNode, int orden );          // [ DONE ]
   int      ordenDisponibilidad( Nodo_t *backNode, Nodo_t *frontNode, int orden );  // [ DONE ]
   
   void     swapNodes( Nodo_t *backNode, Nodo_t *frontNode );                       // [ REV ]
#endif

