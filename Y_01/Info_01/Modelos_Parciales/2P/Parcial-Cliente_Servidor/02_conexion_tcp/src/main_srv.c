#include "../inc/includes_srv.h"

// clear; gcc -Wall --pedantic-errors main_srv.c sock-lib.c -o ../bin/srv.bin


int						socketFd;
char						working = 1;

// ------------------------------------------------------
// sig_hand
// ------------------------------------------------------
void sig_hand() {
	working = 0;
	close( socketFd );
}


// ------------------------------------------------------
// main
// ------------------------------------------------------
int main( int argc, char *argv[] ) {
	struct sockaddr_in 	local_addr;
	
	
	signal( SIGINT, sig_hand );
	signal( SIGKILL, sig_hand );
	
	if ( argc < 2 ) {
		printf( "\n[ USO: ./srv.bin 314159 <PORT> ]\n\n" );
		
	} else {
		socketFd = open_conection( &local_addr, atoi( argv[1] ) );
		
		if ( socketFd < 1 ) {
			printf( "\n[ ERROR: NO SE PUDO ABRIR SOCKET. ]\n\n" );
		} else {
			enviar_datos_cliente( socketFd );
			
			close( socketFd );
		}
	}
	
	
	return 0;
}


// ------------------------------------------------------
// enviar_datos_cliente
// ------------------------------------------------------
/* # PROTOCOLO #
 * SRV -> "READY"
 * loop...
 * 	CLT -> "DATnnn"
 * 	SRV -> char datnnn[256]
 * end loop.
 * CLT -> "ACK"
 */
void enviar_datos_cliente( int sockFD ) {
	char		mensajes[N_MSGS][MSGS_LEN];		// Hecho con mensajes fijos...
	char		buf[MAX_BUF_SIZE];
	char		readyMsg[READY_LEN] = "READY";
	char		ackMsg[ACK_LEN] = "ACK";
	int		bytesRd;
	int		msgCursor;
	int		clientFd;
	
	
	for ( int cursor = 0; cursor < N_MSGS; cursor++ ) {
		strncpy( mensajes[cursor], "PEPEPAPARULO", 13 );
	}
	
	do {
		printf( "# Esperando a cliente... #\n" );
		clientFd = aceptar_pedidos( sockFD );
		
		if ( clientFd < 1 ) {
			printf( "\n[ ERROR: NO SE PUDO CONECTAR CON CLIENTE. ]\n\n" );
		} else {
			printf( "# Conectado con cliente exitosamente. #\n" );
			
			if ( working == 1 ) {
				write( clientFd, readyMsg, READY_LEN );
				
				do {
					bytesRd = read( clientFd, buf, MAX_BUF_SIZE );
					
					if ( strstr( buf, ackMsg ) != NULL ) {
						printf( "[ Recibido: ACK. Terminando... ]\n" );
						bytesRd = 0;
					} else {
						msgCursor = atoi( buf + 3 );
						
						if ( mensajes[msgCursor] != NULL )
							write( clientFd, mensajes[msgCursor], MSGS_LEN );
					}
				} while ( bytesRd > 0 );
				
				close( clientFd );
			}
		}
	} while ( working == 1 );
}