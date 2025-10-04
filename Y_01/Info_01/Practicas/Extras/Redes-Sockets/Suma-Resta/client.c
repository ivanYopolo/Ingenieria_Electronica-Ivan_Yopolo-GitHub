/* # SUMA #
 */

#include "./includes/Funciones/includes.h"

/* # Comando de compilación #
   clear; gcc -Wall --pedantic-errors client.c \
   ./includes/Sockets/sock-lib.c \
   -o client.bin; ls -l
 */
/* # Conexión #
 * IP (loopback): 127.0.0.1
 * Puerto: 3490.
 */

int main( int argc, char * argv[] ) {
	int   sockClient;       // File Descriptor para sockets.
	int   numbytes;         // Contendrá el número de bytes recibidos por "read()".
	char  buf[MAXDATASIZE]; // Buffer donde se reciben los datos de "read()".

   // Tratamiento de la línea de comandos. 
	if ( argc < 2 ) {
		fprintf( stderr, "uso: %s hostname [port]\n", argv[0] );
		exit(1);
   }

	sockClient = conectar( argc, argv );

   /** Envio de mensaje hola al servidor*/
   char mensajeInicial[] = "Hola como estas servidor";
   if ( write( sockClient, mensajeInicial, sizeof (mensajeInicial) ) == -1 ) {
      perror("Error en la escritura del socket");
      exit(1);
   }

   /* Recibimos los datos del servidor del archivo a abrir */
   if ( ( numbytes = read( sockClient, buf, MAXDATASIZE ) ) == -1 ) {
      perror("error de lectura en el socket");
      exit(1);
   }

   /* Visualizamos lo recibido */
	buf[numbytes] = '\0';
	printf( "Recibido: %s\n", buf );

   /* Devolvemos recursos al sistema */
	close( sockClient );

	return 0;
}