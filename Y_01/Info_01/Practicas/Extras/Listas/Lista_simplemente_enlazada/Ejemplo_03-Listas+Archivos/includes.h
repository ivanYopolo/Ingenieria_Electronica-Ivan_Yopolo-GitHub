#ifndef includes
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   #include <unistd.h>

   #define TAM 100
   #define TAM_STR 200

   typedef struct Alumno{  // Data a guardar.
     float   legajo;
     int     nota;
     char    *nombres;      // Dinámico.
     char    *apellidos;    // Dinámico.
   } Alumno_s;

   typedef struct Nodo{    // Nodo de la lista.
     struct Alumno   data;  // Struct Alumno dentro.
     struct Nodo     *next; // Puntero al siguiente nodo.
   } Nodo_s;

   // ###################################################################################

   int getInputData( Alumno_s *alumX );

   char * getString();

   void copiarStruct( Alumno_s *destino, Alumno_s origen );

   Nodo_s * createNode( Alumno_s *dataX );

   void pushNode( Nodo_s **startNode, Nodo_s *newNode );

   void popNode( Nodo_s **startNode );

   void printData( const Alumno_s alumX );

   void writeListInFile( Nodo_s *startNode );
#endif