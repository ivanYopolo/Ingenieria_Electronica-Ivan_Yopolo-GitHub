/* # SUMA-RESTA #
 * Se realiza o una suma o una resta según diga el cliente. 
 * El cliente indica la operación "SUMA" o "RESTA" seguido de 2 números. 
 * Todos los parámetros están separados por espacios.
 */

/* # Comando de compilación #
   clear; gcc -Wall --pedantic-errors server.c \
   ./includes/Sockets/sock-lib.c \
   -o server.bin; ls -l
 */
 
/* # Conexión #
 * IP (loopback): 127.0.0.1
 * Puerto: 3490.
   nc 127.0.0.1 3490
 */

#include "./includes/Funciones/includes.h"

int main() {
   int                  sockServer;                // fd para escuchar y recibir conexiones entrantes.
   int                  sockClient;
   char                 parameter[2][6] = { "SUMA", "RESTA" };   
   int                  *numbers;
   int                  resultNum;                 // Resultado entero.
   char                 resultStr[MAXDATASIZE];    // Mensaje a devolver, el resultado.
   char                 mensajeSalida[2][6] = { "salir", "exit" };
   struct sockaddr_in   localAdress;               // IP y puerto locales.
   int                  closeConection = 0;
   int                  numBytes;                  // N° de Bytes (caracteres) recibidos.
   char                 buf[MAXDATASIZE];          // Mensaje a recibir.
   char                 errorMsg[34] = "[ ERROR: INSTRUCCIÓN INVÁLIDA. ]\n";
   
   printf( "\n# Abriendo socket... #\n" );
   
   if ( ( sockServer = open_conection( &localAdress ) ) == -1 ) { // Abre un socket.
		perror( "[ ERROR: FALLÓ LA CREACIÓN DE LA CONEXIÓN. ]" ); 
		exit (1);
	}
   
   sockClient = aceptar_pedidos( sockServer );  // Escucha al cliente.
   printf( "\n# ESCUCHANDO PEDIDOS... #\n" );
   
	do {  // Cierra al recibir "exit" o "salir".

      if ( ( numBytes = read( sockClient, buf, MAXDATASIZE ) ) == -1 ) {   // Lee desde "sockClient".
         perror( "[ Error de lectura en el socket. ]" );
         exit(1);
      }
      
      printf( "Mensaje del cliente: %s\n", buf );
      buf[numBytes] = '\0';

      if ( ( strstr( buf, mensajeSalida[0] ) != NULL ) || ( strstr( buf, mensajeSalida[1] ) != NULL ) ) {   // Ciera la conexión.
         printf( "\n[ CONEXIÓN TERMINADA. ]\n" );
         closeConection = 1;
      } else { // Conexión/mensaje válido.
         if ( strstr( parameter[0], buf ) != NULL || strstr( parameter[1], buf ) != NULL ) {  // Verifica mensaje correcto.
            // numbers[0] = atoi( buf + 5 );
            // 2° número después del 2° espacio.
            // numbers[1] = atoi( buf + 7 ); // Verificar segundo número.
            numbers = getNumbers( buf );
            
            if ( strstr( parameter[0], buf ) != NULL ) { // SUMA.
               resultStr = operation( numbers[0], numbers[1], SUMA );
            } else { // RESTA.
               resultStr = operation( numbers[0], numbers[1], RESTA );
            }
            write( sockClient, resultStr, strlen( resultStr ) + 1 );
            
         } else { // Instrucción inválida.
            printf( "%s", errorMsg );
            write( sockClient, errorMsg, strlen( errorMsg ) + 1 );
         }
         
         if ( write( sockClient, resultStr, strlen( resultStr ) ) == -1 ) {  // Escribe de vuelta a "sockClient".
            perror( "[ Error escribiendo mensaje en socket. ]" );
            exit(1);
         }
      }
   } while ( closeConection == 0 );
   
   free( numbers );
   close( sockClient );
   
   return 0;
}