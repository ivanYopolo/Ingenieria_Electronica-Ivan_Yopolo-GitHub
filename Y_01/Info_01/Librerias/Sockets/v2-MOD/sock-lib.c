#include "sock-lib.h"


//------------------------------------------------------------------------
// conectar - [ CLIENT ]
//------------------------------------------------------------------------
/* El cliente agarra la IP del servidor y el puerto para conectarse.
 */
int conectar( char *ip, int port )
{
	int	               sockfd;
	struct hostent       *he;	         /* Se utiliza para convertir el nombre del host a su dirección IP. */
	struct sockaddr_in   their_addr;    /* Dirección del server donde se conectará. */

	/* Convertimos el nombre del host a su dirección IP. */
	if ( ( he = gethostbyname( (const char *) ip ) ) == NULL )
	{
		herror( "[ Error en gethostbyname. ]" );
		exit(1);
	}
 
   /* Creamos el socket. */
	if ( ( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
	{
		perror( "[ Error en creación de socket. ]" );
		exit(1);
	}

   /* Establecemos "their_addr" con la direccion del server. */
	their_addr.sin_family   = AF_INET;
	// their_addr.sin_port     = ( argc == 2 ) ? htons( PORT ) : htons( atoi( argv[2] ) );
   if ( argc == 2 ) {
      their_addr.sin_port = htons( DEFAULT_PORT );
   } else {
      their_addr.sin_port = htons( port );
   }
	their_addr.sin_addr    = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);

   /* Intentamos conectarnos con el servidor. */
	if ( connect( sockfd, (struct sockaddr *) &their_addr, sizeof (struct sockaddr) ) == -1 )
	{
		perror( "Error tratando de conectar al server" );
		exit(1);
	}
	return sockfd;
}


//------------------------------------------------------------------------
// open_conection - [ SERVER ]
//------------------------------------------------------------------------
/* Abre la conexión (socket) para que reciba pedidos el servidor.
 * Utiliza IP local, propia del servidor mismo.
 * 
 * Declarar "srv_addr" en el main. Se utiliza por referencia.
 */
int open_conection( struct sockaddr_in *srv_addr, int port )
{
	int	               sockaux;	/* Socket auxiliar. */
	int	               aux; 		/* Variable auxiliar. */

	/* Crea un socket y verifica si hubo algún error. */
	if ( ( sockaux = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 ) 
	{
		fprintf( stderr, "[ Error en función socket. Código de error: %s ]\n", strerror( sockaux ) );
		return -1;
	}

   /* Asignamos valores a la estructura "srv_addr". */

	srv_addr->sin_family = AF_INET;		            // Familia de sockets INET para UNIX.
   
   if ( port > 1 ) {
      srv_addr->sin_port = htons( port );
   } else {
      srv_addr->sin_port = htons( DEFAULT_PORT );	// Convierte el entero formato PC a entero formato network.
   }
   
   srv_addr->sin_addr.s_addr = INADDR_ANY;	         // IP local del servidor.
   
   
	bzero( &(srv_addr->sin_zero), 8 );		         // Rellena con ceros el resto de la estructura.

	/* Con la estructura "sockaddr_in" completa, se declara en el Sistema que este proceso escuchará
    * pedidos por la IP y el port definidos.
    */
	if ( ( aux = bind( sockaux, (struct sockaddr *) srv_addr, sizeof (struct sockaddr) ) ) == -1 )
	{
		fprintf( stderr, "[ Error en función bind. Código de error: %s ]\n", strerror( aux ) );
		return -1;
	}
   
	/* Habilitamos el socket para recibir conexiones, con una cola de conexiones en espera que tendrá
    * como máximo el tamaño especificado en "BACKLOG".
    */
	if ( ( aux = listen( sockaux, BACKLOG ) ) == -1 )
	{
		fprintf( stderr, "[ Error en función listen. Código de error: %s ]\n", strerror( aux ) );
		return -1;
   }
   
	return sockaux;
}


//------------------------------------------------------------------------
// aceptar_pedidos - [ SERVER ]
//------------------------------------------------------------------------
/* Acepta pedidos según un file descriptor de entrada donde se aceptan
 * conexiones de entrada.
 *
 * El nuevo file descriptor por el cliente específico lo devuelve en su
 * return.
 */
int aceptar_pedidos( int sockfd )
{
	int                  newfd; 	/* Por este socket duplicado del inicial se transaccionarÃ¡*/
   struct sockaddr_in   their_addr;  /* Contendra la direccion IP y nÃºmero de puerto del cliente */
	unsigned int         sin_size = sizeof (struct sockaddr_in);

	/*Se espera por conexiones ,*/
	if ( ( newfd = accept( sockfd, (struct sockaddr *) &their_addr, &sin_size ) ) == -1 )
	{
		fprintf( stderr, "Error en funciÃ³n accept. CÃ³digo de error %s\n", strerror( newfd ) );
		return -1;
	} else {
		printf( "[ SERVER ] conexión desde:   %s\n", inet_ntoa( their_addr.sin_addr ) );
		return newfd;
	}
}