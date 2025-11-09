#include "../inc/sock-lib.h"

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY 			5000
#define LIMIT 			4
#define STRSIZE 		20
#define THREAD_LIMIT 15
// #define PORT			314159


Nodo_t		*startThreadNode;
int 			sockfd; 				// File Descriptor del socket por el que el servidor "escuchará" conexiones.
int			working = 1;

void 	signal_handler() {
	working = 0;
	close( sockfd );
}

struct args {
	int 		cltfd;
	char 		cltCount;
	char 		msg[STRSIZE];
	char 		msgCount;
	void 		*returnValue;		// Valor de retorno.
};


//------------------------------------------------------
// do_something
//------------------------------------------------------
void *do_something( void *input ) {
	int i; 
	int j;
	int nBytes;

	for ( i = 0; i < LIMIT; i++ ) {
		for ( j = 0; j < DELAY; j++ ) {
			usleep( 1000 );
		}
		
		( ((struct args*)input)->msgCount )++;
		
		snprintf( ((struct args*)input)->msg, STRSIZE, "Client: %d. Message: %d.\n", \
					 ((struct args*)input)->cltCount, ((struct args*)input)->msgCount );
		
		nBytes = write( ((struct args*)input)->cltfd, ((struct args*)input)->msg, STRSIZE );
		if ( nBytes == -1 ) {
			perror( "Error escribiendo mensaje en socket" );
			exit(1);
		}
	}

	close( ((struct args*)input)->cltfd );	// Cierra el socket.
	
	// Sale con "pthread_exit()" y su valor de retorno correspondiente.
	pthread_exit( ((struct args*)input)->returnValue );

	return NULL;
}

//------------------------------------------------------
// main
//------------------------------------------------------
/* Armar una lista GLOBAL con información de los threads.
 * Las estructuras pueden tener datos de si los threads terminaron, así se
 * puede preguntar sin bloquear por quién termino, para hacer join y liberar
 * recursos.
 */
int main( int argc, char *argv[] ) {
	int			port;
	struct 		sockaddr_in my_addr;		// Contendrá la dirección IP y el número de puerto local.
	int 			i;

	int 			err;
	int 			threadCount;
	pthread_t 	tid[BACKLOG];					// Array de Threads IDs (TIDs).
	// int 			*ptr[BACKLOG];				// Array de valores de retorno de los threads.
	struct args svr[BACKLOG];					// Argumentos a pasar a la función del thread; array de estructuras.
	int 			returnValueLocal[BACKLOG];	// Array de valores de retorno de los threads.
	

	if ( argc < 2 ) {
		fprintf( stderr, 
					"######################################################\n"
					"[ Uso: %s PORT ]\n"
					"######################################################\n", argv[0] );
		exit(1);
	}
	port = atoi( argv[1] );
	
	signal( SIGINT, signal_handler );

	threadCount = 0;
	for ( i = 0; i < BACKLOG; i++ ) {
		// Mensajes.
		svr[i].msgCount = i + 1;				
		// Guarda la dirección donde se van a guardar los valores de retorno.
		svr[i].returnValue = (void *)(returnValueLocal + i);		
	}

	sockfd = open_conection( &my_addr, port );
	if ( sockfd == -1 ) {
		perror( "Falló la creación de la conexión" ); 
		exit(1);
	}
	
	printf( "Esperando conexiones...\n" );

	// while ( (threadCount < THREAD_LIMIT) && (working == 1) ) {
	while ( working == 1 ) {
		svr[threadCount].cltfd = aceptar_pedidos( sockfd );	// Guarda el socket del cliente en específico.
		
		threadCount++;
		svr[threadCount].cltCount = threadCount;	// Guarda cuantos threads se crearon.

		// Crea el thread pasando por referencia la variable "tid" donde se guarda el TID, 
		// la dirección de la función "do_something", 
		// y los argumentos en "srv".
		err = pthread_create( tid + threadCount - 1, NULL, &do_something, (void *)(svr + threadCount - 1) );
		if ( err != 0 )
			printf( "\nCan't create thread: [%s].\n", strerror(err) );
		else
			printf( "\nThread %d created successfully.\n", threadCount );
	}

	// Agarra los valores de retorno de cada thread.
	for ( i = 0; i < threadCount; i++ ) {
		pthread_join( tid[i], (void**)(returnValueLocal + i) );
		printf( "\nReturn value from thread %d is [%d].\n", i, returnValueLocal[i] );
	}


	return 0;
}
