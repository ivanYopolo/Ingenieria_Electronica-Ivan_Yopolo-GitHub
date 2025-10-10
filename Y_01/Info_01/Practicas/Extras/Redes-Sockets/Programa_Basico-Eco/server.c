/* ### Eco ###
 * El servidor repite lo que el cliente dice (por el socket).
 * No necesariamente por el kernel.
 * Cierra la conexión cuando se escribe "exit" o "salir".
 * Se abre una sola vez el socket.
 * Ej.:
 * Servidor:
   - Hola
   - Que
 * Cliente:
   - Hola
   - Que
 */

/* # Comando de compilación #
   clear; gcc -Wall --pedantic-errors server.c \
   ./includes/Sockets/sock-lib.c \
   -o server.bin; ls -l
 */
 
/* # Probando conexión con "net-cat" #
 * IP (loopback): 127.0.0.1
 * Puerto: 3490.
   nc 127.0.0.1 3490
 */

#include "./includes/eco/includes_server.h"

int main() {
   int                  sockServer;                // fd para escuchar y recibir conexiones entrantes.
   int                  sockClient;
   char                 ecoMessage[MAXDATASIZE];   // Mensaje a devolver, el "eco".
   char                 mensajeSalida[2][6] = { "salir", "exit" };
   struct sockaddr_in   localAdress;               // IP y puerto locales.
   int                  closeConection = 0;
   
   printf( "\n# Abriendo socket... #\n" );
   
   if ( ( sockServer = open_conection( &localAdress ) ) == -1 ) { // Abre un socket.
		perror( "[ ERROR: FALLÓ LA CREACIÓN DE LA CONEXIÓN. ]" ); 
		exit (1);
	}
   
   sockClient = aceptar_pedidos( sockServer );  // Escucha al cliente.
   printf( "\n# ESCUCHANDO PEDIDOS... #\n" );
   
	do {  // Cierra al recibir "exit" o "salir".

      int numBytes;           // N° de Bytes (caracteres) recibidos.
      char buf[MAXDATASIZE];  // Mensaje a recibir.

      if ( ( numBytes = read( sockClient, buf, MAXDATASIZE ) ) == -1 ) {   // Lee desde "sockClient".
         perror( "[ Error de lectura en el socket. ]" );
         exit(1);
      }
      
      printf( "Mensaje del cliente: %s\n", buf );
      buf[numBytes] = '\0';

      if ( ( strstr( buf, mensajeSalida[0] ) != NULL ) || ( strstr( buf, mensajeSalida[1] ) != NULL ) ) {   // Ciera la conexión.
         printf( "\n[ CONEXIÓN TERMINADA. ]\n" );
         closeConection = 1;
      } else {
         strncpy( ecoMessage, buf, numBytes ); // Copia mensaje para ECO.
         if ( write( sockClient, ecoMessage, numBytes ) == -1 ) {  // Escribe de vuelta a "sockClient".
            perror( "Error escribiendo mensaje en socket" );
            exit(1);
         }
      }
   } while ( closeConection == 0 );
   
   close( sockClient );
   
   return 0;
}