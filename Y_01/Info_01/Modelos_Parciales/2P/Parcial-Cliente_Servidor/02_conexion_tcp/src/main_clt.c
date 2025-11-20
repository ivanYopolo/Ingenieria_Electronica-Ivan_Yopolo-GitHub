#include "../inc/includes_clt.h"

// clear; gcc -Wall --pedantic-errors main_clt.c sock-lib.c -o ../bin/clt.bin

// ------------------------------------------------------
// main
// ------------------------------------------------------
int main( int argc, char *argv[] ) {
	
	if ( argc != 4 ) {
		printf( "\n[ USO: prog.bin 10.10.1.5 3255 015-025 ]\n\n" );
		exit(1);
	} else {
		conexion_tcp( argv[1], atoi( argv[2] ), argv[3] );
	}
	
	return 0;
}


// ------------------------------------------------------
// conexion_tcp
// ------------------------------------------------------
/* Pide datos de manera DAT076, DAT100 (ej), donde el
 * servidor devuelve los datos correspondientes a los IDs
 * del 76 al 100.
 * El servidor envía los datos de manera secuencial.
 * Cada DATnnn es un string de 256 B y se repite hasta el
 * fin.
 *
 * # PROTOCOLO #
 * SRV -> "READY"
 * loop...
 * CLT -> "DATnnn"
 * SRV -> char datnnn[256]
 * end loop.
 * CLT -> "ACK"
 */
void conexion_tcp( char *ipStr, int port, char *sequence ) {
	int		sockFd = 0;
	int		bytesRd;
	char		buf[MAX_BUF_SIZE];
	char		startSeq[SEQ_LEN];
	char		endSeq[SEQ_LEN];
	char		datMsg[SEQ_LEN];
	char		**inputData = NULL;	// Array de inputs # dinámico #.
	int 		inputDataCursor = 0;	// Cursor del dato "n-ésimo" dentro del array.
	char		ackMsg[ACK_LEN] = "ACK";
	int		nMsgs;			// N° de mensajes a recibir.
	int		nDatCursor;		// Cursor para seleccionar dato a pedir.
	int 		startSeqNum;
	int 		endSeqNum;
	char		sendingMsg = 1;
	
	
	// sequence: "025-030".
	startSeq[SEQ_LEN - 1] = '\0';
	endSeq[SEQ_LEN - 1] = '\0';
	datMsg[SEQ_LEN - 1] = '\0';
	mempcpy( mempcpy( startSeq, "DAT", 3 ), sequence, 3 );		// Ej.: "025".
	mempcpy( mempcpy( endSeq, "DAT", 3 ), sequence + 4, 3 );		// Ej.: "030".
	mempcpy( datMsg, "DAT", 3 );
	
	// Cálculo de N° de mensajes a recibir:
	startSeqNum = atoi( startSeq + 3 );
	endSeqNum = atoi( endSeq + 3 );
	nMsgs = endSeqNum - startSeqNum + 1;	// Si es 0, recibe 1 dato (se suma 1).
	
	if ( nMsgs < 1 ) {	// SECUENCIA INVÁLIDA.
		printf( "\n[ ERROR: SECUENCIA INVÁLIDA. ]\n\n" );
	} else {
		
		sockFd = conectar( ipStr, port );
		
		if ( sockFd < 1 ) {	// SOCKET INVÁLIDO.
			printf( "\n[ ERROR: IP Y/O PUERTO INVÁLIDO/S. ]\n\n" );
		} else {
			inputData = (char **) malloc( nMsgs * sizeof (char *) );	// Inicializa los "nMsgs" arrays.
			
			if ( inputData == NULL ) {
				printf( "\n[ ERROR: SIN MEMORIA. ]\n\n" );
				close( sockFd );
				exit( -1 );
			}
			
			for ( inputDataCursor = 0; inputDataCursor < nMsgs; inputDataCursor++ ) {		// Inicializa cada array.
				inputData[inputDataCursor] = (char *) malloc( INPUT_LEN * sizeof (char) );
				
				if ( inputData[inputDataCursor] == NULL ) {
					printf( "\n[ ERROR: SIN MEMORIA. ]\n\n" );
					free( inputData );
					close( sockFd );
					exit( -1 );
				}
			}
			
			bytesRd = read( sockFd, buf, READY_LEN );
			// buf[bytesRd - 1] = '\0';
			
			if ( bytesRd < READY_LEN ) {
				printf( "\n[ ERROR: MENSAJE INVÁLIDO. ]\n\n" );
				
			} else {
				
				if ( strstr( buf, "READY" ) == NULL ) {
					printf( "\n[ ERROR: SERVER NOT READY. ]\n\n" );
					
				} else {	// Recibió "READY".
					
					nDatCursor = startSeqNum;	// Empieza en el inicio.
					inputDataCursor = 0;
					sendingMsg = 1;
					do {
						if ( nDatCursor <= endSeqNum ) {
							sprintf( datMsg + 3, "%d", nDatCursor );	// Pone el número del "nDato" en "datMsg".
							
							printf( "[ Pidiendo: %s. ]\n", datMsg );
							
							write( sockFd, datMsg, SEQ_LEN );	// Manda "DATnnn"
							
							bytesRd = read( sockFd, inputData[inputDataCursor], INPUT_LEN );	// Recibe un msg de 256 B.
							
							printf( "[ Recibido: \"%s\". ]\n\n", inputData[inputDataCursor] );
							
							nDatCursor++;	// Va al siguiente dato.
							inputDataCursor++;
						} else {	// Terminó de recibir datos según rango por kernel.
							sendingMsg = 0;
						}
					} while ( (bytesRd == INPUT_LEN) && (sendingMsg != 0) );	// Terminó de recibir los datos.
					
					write( sockFd, ackMsg, ACK_LEN );	// Envía "ACK" al servidor.
				}	// Terminó secuencia de datos recibidos por el servidor.
				
			}	// End if READY.
			
			// # Liberación de recursos #
			free( inputData );
			close( sockFd );
		}	// Socket válido.
	}	// Secuencia válida (end > start).
}
