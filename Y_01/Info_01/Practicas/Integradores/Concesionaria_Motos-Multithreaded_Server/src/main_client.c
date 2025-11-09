#include "../inc/includes_client.h"

#define LIMIT 5
#define MAXDATASIZE 4096 
// Máxima cantidad de bytes que puede recibir en una transacción.

int main( int argc, char * argv[] ) {
	int 		i = 0;
	int 		sockfd = 0;   			// File Descriptor para sockets.
	int		port = 0;
	int 		numbytes = 0; 			// Contendrá el número de bytes recibidos por read().
	char 		buf[MAXDATASIZE];  	// Buffer donde se reciben los datos de read().
	int 		menuOption = 0;		// Opción elegida en el menú (1~X).
	Nodo_t	*startNode = NULL;	// Inicio de la lista.
	int		localDatafd = 0;		// File Descriptor de los datos locales.


	// Manejo de argumentos del main (IP + Port).
	if ( argc < 2 ) {
		fprintf( stderr, "[ Uso: %s IP PORT ]\n", argv[0] );
		exit(1);
	}
	
	
	port = atoi( argv[2] );
	sockfd = conectar( argv[1], port );
	
	if ( (sockfd < 1) || (argv[1] == NULL) ) {
		fprintf( stderr, "[ ERROR: PUERTO INVÁLIDO O EN USO. ]\n" );
		fprintf( stderr, "[ Uso: %s IP PORT ]\n", argv[0] );
		exit(1);
	}
	
	// Revisar nombre distintos de archivos...
	// localDatafd = open( "../data/sucursal/nombre_archivo_1.dat", O_CREAT | O_TRUNC | O_WRONLY, 0666 );

	// Creación del MUTEX.
	pthread_mutex_init( &lockSave );

	// ### Inicio del programa ###
	system( "clear" );

	printf( "######################################################\n"
			  "Bienvenido a la concesionaria de motos.\n"
			  "Por favor, ingrese una opción válida.\n"
			  "######################################################\n" );
	
	cargar_datos_casa_central( &startNode, sockfd );
	alarm( 60 );	// Alarma para guardado automático.
	
	// Implementar threads para cada función BLOQUEANTE.
	// O threads para el resto de funciones mientras se bloquea ("asíncronas").
	
	do {
		menuOption = show_menu();
		
		switch ( menuOption ) {
			case ABM:
				abm_lista( &startNode );
			break;
			
			case GUARDAR:
				guardar_datos( startNode, sockfd, localDatafd );
			break;
			
			case VISUAL_LOCAL:
				visualizar_lista_local( startNode );
			break;
			
			case VISUAL_SERVER:
				visualizar_lista_remoto( sockfd );
			break;
			
			case SINCRONIZAR:
				sincronizar( &startNode, sockfd, localDatafd );
			break;
			
			default:
				printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
				menuOption = -1;
		}
	} while ( menuOption != 0 );
	
	
	end_session( startNode, sockfd, localDatafd );
	
	/*
	for ( i = 0; i < LIMIT; i++ ) {
		// Recibimos los datos del servidor.
		if ( ( numbytes = read( sockfd, buf, MAXDATASIZE ) ) == -1 ) {
			perror( "Error de lectura en el socket." );
			exit(1);
		}
		// buf[numbytes] = '\0';
	}
	*/

	return 0;
}
