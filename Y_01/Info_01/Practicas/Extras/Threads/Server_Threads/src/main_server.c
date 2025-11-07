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


extern int 			sockfd; /* File Descriptor del socket por el que el servidor "escuchará" conexiones*/
extern int			working = 1;

void 	signal_handler() {
	working = 0;
	close( sockfd );
}

struct args {
	int socket;
	char clt_cnt;
	char message[STRSIZE];
	char msg_cnt;
	void *ret;
};


//------------------------------------------------------
// do_something
//------------------------------------------------------
void *do_something( void *input ) {
	int i, j;

	for ( i = 0; i < LIMIT; i++ ) {
		for ( j = 0; j < DELAY; j++ ) {
			usleep( 1000 );
		}
		((struct args*)input)->msg_cnt++;
		
		snprintf( ((struct args*)input)->message, STRSIZE, "Client: %d. Message: %d.\n", ((struct args*)input)->clt_cnt, ((struct args*)input)->msg_cnt );
		
		if ( write( ((struct args*)input)->socket, ((struct args*)input)->message, STRSIZE) == -1 ) {
			perror( "Error escribiendo mensaje en socket" );
			exit(1);
		}
	}

	close( ((struct args*)input)->socket );
	*(int *)((struct args*)input)->ret = 100 * (((struct args*)input)->clt_cnt + 1);
	pthread_exit( ((struct args*)input)->ret );

	return NULL;
}


//------------------------------------------------------
// main
//------------------------------------------------------
int main( int argc, char *argv[] ) {
	int 			err;
	int 			thr_cnt;
	pthread_t 	tid[BACKLOG];
	int			port;
	struct 		sockaddr_in my_addr;	/* contendrá la dirección IP y el número de puerto local */

	int 			i;
	int 			*ptr[BACKLOG];
	struct args svr[BACKLOG];
	int 			ret[BACKLOG];
	

	if ( argc < 2 ) {
		fprintf( stderr, "[ Uso: %s PORT ]\n", argv[0] );
		exit(1);
	}
	port = atoi( argv[1] );
	
	signal( SIGINT, signal_handler );

	thr_cnt = 0;
	for ( i = 0; i < BACKLOG; i++ ) {
		svr[i].msg_cnt = 0;
		svr[i].ret = (void *)&ret[i];
	}

	if ( ( sockfd = open_conection( &my_addr, port ) ) == -1 ) {
		perror( "Falló la creación de la conexión" ); 
		exit(1);
	}

	// while ( thr_cnt < THREAD_LIMIT ) {
	while ( working == 1 ) {
		svr[thr_cnt].socket = aceptar_pedidos( sockfd );
		svr[thr_cnt].clt_cnt = thr_cnt;

		err = pthread_create( &(tid[thr_cnt]), NULL, &do_something, (void *)(&svr[thr_cnt]) );
		if ( err != 0 )
			printf( "\nCan't create thread: [%s].\n", strerror(err) );
		else
			printf( "\nThread %d created successfully.\n", thr_cnt );

		thr_cnt++;
	}

	for ( i = 0; i < thr_cnt; i++ ) {
		pthread_join( tid[i], (void**)&(ptr[i]) );
		printf( "\nReturn value from thread %d is [%d].\n", i, *ptr[i] );
	}

	exit(0);
}
