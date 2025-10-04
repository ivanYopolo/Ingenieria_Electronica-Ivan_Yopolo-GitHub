#ifndef INCLUDES_SUMA_RESTA
   #define INCLUDES_SUMA_RESTA
   
   // ###################################################
   // Defines
   // ###################################################

   #define MAXDATASIZE  4096
   #define FALSE        0
   #define TRUE         1
   #define RESTA        0
   #define SUMA         1
   
   // ###################################################
   // Includes
   // ###################################################

   #include "../Sockets/sock-lib.h"
   
   // ###################################################
   // Funciones
   // ###################################################

   // ### Operations ###
   char   * operation( int firstNum, int secondNum, int op );

   // ### Coms Serv-Client ###
   int    * getNumbers( char * buf );  // Devuelve array de 2 enteros.
#endif