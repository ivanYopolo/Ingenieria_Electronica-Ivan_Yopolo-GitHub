#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "sock-lib.h"


char						shutDown = 0;
int 						sockFd;

void sig_hand() {
	shutDown = 1;
	close( sockFd );
}


int main( int argc, char *argv[] ) {
	struct sockaddr_in	myAddress;
	
	
	printf( "Señal de SIGINT con sig_hand...\n" );
	signal( SIGINT, sig_hand );
	
	if ( argc == 3 ) {
		printf( "Abriendo socket...\n" );
		sockFd = open_conection( &myAddress, atoi(argv[2]) );
		
		while ( shutDown == 0 && sockFd > 0 ) {
			printf( "Aceptando pedidos...\n" );
			sockFd = aceptar_pedidos( sockFd );

			printf( "Sleeping...\n" );
			sleep(1);
		}
		
		printf( "# CERRANDO SOCKET. #\n" );
		
	}
	
	return 0;
}

