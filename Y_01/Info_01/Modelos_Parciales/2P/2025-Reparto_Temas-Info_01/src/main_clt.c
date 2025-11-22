// # 2° Parcial - 2025 #
/* # CLIENTE - ALUMNO/A # 
 *
 */

/* # COMPILACIÓN #
 * clear; gcc -Wall --pedantic-errors main_clt.c sock-lib.c -o ../bin/clt.bin
 */

#include "../inc/includes_clt.h"

int main ( int argc, char *argv[] ) {
	int			srvFd;
	int			parcialArchivoFd;
	char			parcialRd[MAX_BUF_SIZE];
	char			bufMsg[MSG_LEN];
	char			okMsg[MSG_LEN] = "OK200";
	int			bytesRd;
	int			legajo;
	int			dni;
	
	
	if ( argc != 5 ) {
		
		printf( "\n[ USO: ./clt.bin <IP> <PORT> <LEGAJO> <DNI> ]\n\n" );
	} else {
		
		srvFd = conectar( argv[1], atoi( argv[2] ) );
		
		if ( srvFd < 1 ) {
			
			printf( "\n[ ERROR: IP + PUERTO INVÁLIDOS. ]\n\n" );
		} else {
			
			legajo = atoi( argv[3] );
			dni = atoi( argv[4] );
			
			// 1) Envía LEGAJO + DNI, en ese orden.
			write( srvFd, &legajo, sizeof (int) );
			write( srvFd, &dni, sizeof (int) );
			
			// 2) Espera "OK200". Si recibe error, termina.
			bytesRd = read( srvFd, bufMsg, MSG_LEN );
			bufMsg[MSG_LEN - 1] = '\0';
			
			if ( strstr( bufMsg, okMsg ) == NULL ) {
				
				printf( "\n[ ERROR: %s ]\n", bufMsg );
			} else {
				
				// 3) "OK200", recibe el parcial de a 1024 B.
				parcialArchivoFd = open( "../data/alum/Parcial.tar.gz", O_CREAT | O_TRUNC | O_WRONLY, 0666 );
				if ( parcialArchivoFd < 1 ) {
					
					printf( "\n[ ERROR: NO SE PUDO CREAR ARCHIVO PARCIAL. ]\n\n" );
				} else {
					
					do {
						bytesRd = read( srvFd, parcialRd, MAX_BUF_SIZE );
						write( parcialArchivoFd, parcialRd, bytesRd );
					} while ( bytesRd > 0 );
					close( parcialArchivoFd );
				}
			}
			
			close( srvFd );
		}
	}
	
	return 0;
}