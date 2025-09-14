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

   #define CARDIOLOGIA        1
   #define CLINICA            2
   #define GASTROENTEROLOGIA  3
   #define CIRUGIA            4
   #define DEREMATOLOGIA      5
   #define OFTALMOLOGIA       6
   #define TRAUMATOLOGIA      7

   // ########################################################
   // DATO
   // ########################################################
   typedef struct equipamiento{
      int sku; // Identificador de modelo (puede repetirse).
      char descripcion[ TAM_DESC ];
      char detalles[ TAM_DET ];
      int cantidad;
      int especialidad;
      float precio;
   } Dato_t;
   /* Cada NODO de la lista va a ser un SKU de equipamiento.
    * Los IDs se repiten si los SKUs también se repiten.
    */
   
   // ########################################################
   // NODO
   // ########################################################
   typedef struct Nodo_s{
      Dato_t *prevNode;
      Dato_t *nextNode;
      Dato_t dato;
   } Nodo_t;

   // ########################################################
   // Funciones
   // ########################################################
   int      menu();                                         // [ DONE ]
   
   Nodo_t * getUserInput( Nodo_t **startNode );             // [ DONE ]
   void     popNode( Nodo_t **nodeX );                      // [ DONE ]
   void     pushNode( Nodo_t **startNode, Nodo_t *newNode );
   Nodo_t * createNode( Dato_t *datoX );                    // [ DONE ]
   
   char   * writeStrD();                                    // [ DONE ]
   
   void     cargarDatos();
   void     modificarDatos( Nodo_t *startNode );
   void     guardarDatos( Nodo_t *startNode );              // [ REV ]
   int      ordenarDatos( const Nodo_t *startNode, int ordenamiento[] );
   void     mostrarDatos( Nodo_t *startNode );              // [ DONE ]
   void     mostrarFecha( char *fechaTemp );                // [ DONE ]
   
   // Por puntero a función:
   int      ordenEspecialidadASC( Nodo_t *backNode, Nodo_t *frontNode );
   int      ordenPrecioASC( Nodo_t *backNode, Nodo_t *frontNode );
   int      ordenDisponibilidadASC( Nodo_t *backNode, Nodo_t *frontNode );
   
   int      ordenEspecialidadDES( Nodo_t *backNode, Nodo_t *frontNode );
   int      ordenPrecioDES( Nodo_t *backNode, Nodo_t *frontNode );
   int      ordenDisponibilidadDES( Nodo_t *backNode, Nodo_t *frontNode );
   
   void     swapNodes( Nodo_t *backNode, Nodo_t *frontNode );
#endif

