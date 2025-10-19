
// ########################################################
// Includes
// ########################################################
#include "../inc/funciones_servidor.h"


// ########################################################
// Variables GLOBLALES
// ########################################################
char                 childEnd = 0;	// Termina el hijo cuando el padre termina.
char                 endSrv = 0;		// Termina el servidor completo con Ctrl+C.
char                 endSave = 0;	// Termina el HIJO (recibió SIGTERM).


/* # Probando conexión con "net-cat" #
 * IP (loopback): 127.0.0.1
 * Puerto: [ VER PUERTO POR FUNCIÓN ].
   nc 127.0.0.1 [ VER PUERTO POR FUNCIÓN ]
 */


// ########################################################
// Manejo de señales
// ########################################################

//------------------------------------------------------------------------
// sig_hand_father # PADRE - HIJO # - [ INP ]
//------------------------------------------------------------------------
/* El padre recibe la señal de SIGCHLD (terminó el hijo) y lo elimina.
 * Ligado a SIGCHLD.
 */
void sig_hand_father() {
   childEnd = 1;
	wait( NULL );
}


//------------------------------------------------------------------------
// sig_hand_end_session # PADRE - I/O # - [ REV ]
//------------------------------------------------------------------------
/* Recibe señal con Ctrl+C (SIGINT) para que termine de forma segura.
 */
void sig_hand_end_session() {
	endSrv = 1;
}


//------------------------------------------------------------------------
// sig_hand_child # HIJO - PADRE # - [ REV ]
//------------------------------------------------------------------------
/* Recibe señal SIGTERM del PADRE para que termine de forma segura.
 */
void sig_hand_child() {
	endSave = 1;
}


// ########################################################
// Server: cargar & guardar datos
// ########################################################

//------------------------------------------------------------------------
// cargar_datos_server # PADRE # - [ REV ]
//------------------------------------------------------------------------
/* CARGA la lista entera en un archivo de base de datos.
 * Usar '.dat'.
 * Ídem "guardar_datos()" pero de manera REMOTA.
 *
 * # Recibe del cliente #
 * - (#) Nombre del archivo a leer.
 * 
 * # Envía al cliente #
 * - (#) 1: si el archivo existe.
 * - (#) 0: si no existe tal archivo.
 * - DATOS DE CADA NODO DE LA LISTA.
 */
void cargar_datos_server( int portRD, pid_t childPid ) {
   int                  sockServer;                // fd para escuchar y recibir conexiones entrantes.
   int                  sockClient;                // fd del cliente específico.
   int                  sockArchivo;               // fd del archivo.
   struct sockaddr_in   srvAddr;                   // IP y puerto locales.
   int                  numBytes;
   char                 reading;
   char                 nombreArchivo[MAX_SIZE_NAME];
   char                 *rutaArchivo = NULL;
   char                 directorioDatos[SIZE_DATA_DIR] = "./data/";
   char                 extensionDatos[5] = ".dat";
   char                 buffReply;                 // 0: no existe el archivo. 1: existe el archivo.
   Dato_t               buffData;						// Recibe del archivo y envía al cliente.
   
   
	signal( SIGINT, sig_hand_end_session );
	signal( SIGCHLD, sig_hand_father );
	do {	// Bucle para seguir activo hasta recibir señal externa.
		// printf( "\n# Abriendo socket... #\n" );
		sockServer = open_conection( &srvAddr, portRD );   // Abre un socket.
		if ( sockServer == -1 ) { 
			perror( "[ ERROR: FALLÓ LA CREACIÓN DE LA CONEXIÓN. ]" ); 
			exit(1);
		}
		
		// # BLOQUEANTE... #
		// Averiguar cómo hacer que detecte una SEÑAL y variar el flujo del código..
		// https://stackoverflow.com/questions/69043581/linux-socket-set-non-blocking-using-o-nonblock
		sockClient = aceptar_pedidos( sockServer );  // Escucha al cliente.
		
		do {  // Comienza la lectura de la ruta y nombre del archivo.
			
			// Recibe del cliente el nombre...
			numBytes = read( sockClient, nombreArchivo, MAX_SIZE_NAME ); // Recibe el nombre del archivo.
			
			// # Se le suma la ruta al nombre del archivo #
			// Bytes:   "data/[nombreArchivo].dat" = sizeof(nombreArchivo) + 10 B (incluye nulo).
			rutaArchivo = malloc( (sizeof(nombreArchivo) + (10 * sizeof(char))) * sizeof(char) );
			mempcpy( mempcpy( mempcpy( rutaArchivo, directorioDatos, strlen(directorioDatos) ), nombreArchivo, strlen(nombreArchivo) ), extensionDatos, strlen(extensionDatos) + 1 );
			
			sockArchivo = open( rutaArchivo, O_RDONLY ); // Abre el archivo.
			if ( sockArchivo < 1 ) {   // NO existe; inválido.
				buffReply = 0;
				reading = 0;
			} else {                   // Existe; es válido.
				buffReply = 1;
				reading = 1;
			} 
			
			// # Avisa al cliente de la existencia del archivo #
			write( sockClient, &buffReply, 1 ); 
			// En caso de no existir el archivo, el cliente debe de ingresar de nuevo el nombre.
		} while ( reading == 1 );
		
		// # Se abre el archivo y se mandan al cliente los datos #
		do {
			numBytes = read( sockArchivo, &buffData, sizeof(Dato_t) );
			
			// Envía datos al cliente.
			if ( numBytes == sizeof(Dato_t) ) {
				write( sockClient, &buffData, sizeof(Dato_t) );
			} 
		} while ( numBytes == sizeof(Dato_t) );
		
		close( sockArchivo );
		close( sockClient );
	} while ( endSrv == 0 );	// Termina servidor.
	
	
	// ### TERMINACIÓN DEL SERVIDOR ###
	
	// Recibió Ctrl+d (SIGINT):
	kill( childPid, SIGTERM );
	while ( childEnd == 0 ) {	// Espera a que el hijo termine de forma segura.
		sleep(1);
	}
	
	free( rutaArchivo );
	close( sockServer );
   
   return;
}


//------------------------------------------------------------------------
// guardar_datos_server # HIJO # - [ INP ]
//------------------------------------------------------------------------
/* GUARDA la lista entera en un archivo de base de datos.
 * Usar '.dat'.
 * Ídem "guardar_datos()" pero de manera REMOTA.
 * Accede al servidor, mandando la lista entera y el nombre del archivo.
 *
 * # Recibe del cliente #
 * - (#) Nombre del archivo a guardar.
 * - DATOS DE CADA NODO DE LA LISTA ENTERA.
 *
 * # Envía al cliente #
 * - (#) 1: si el archivo ya existe (nombre repetido).
 * - (#) 0: si no existe tal archivo.
 */
void guardar_datos_server( int portWR ) {
   int                  sockServer;                // fd para escuchar y recibir conexiones entrantes.
   int                  sockClient;                // fd del cliente específico.
   int                  sockArchivo;               // fd del archivo.
   struct sockaddr_in   srvAddr;                   // IP y puerto locales.
   int                  numBytes;
   char                 reading;
   char                 nombreArchivo[MAX_SIZE_NAME];
   char                 *rutaArchivo = NULL;
   char                 directorioDatos[6] = "data/";
   char                 extensionDatos[5] = ".dat";
   char                 buffReply;                 // 0: no existe el archivo. 1: existe el archivo.
   Dato_t               buffData;
   
   
	signal( SIGTERM, sig_hand_child );
	do {
		// printf( "\n# Abriendo socket... #\n" );
		sockServer = open_conection( &srvAddr, portWR );	// Abre un socket.
		if ( sockServer == -1 ) { 
			perror( "[ ERROR: FALLÓ LA CREACIÓN DE LA CONEXIÓN. ]" ); 
			exit(1);
		}
		
		sockClient = aceptar_pedidos( sockServer );  		// Escucha al cliente.
		
		do {  // Comienza la lectura de la ruta y nombre del archivo.
			
			// Recibe del cliente el nombre...
			numBytes = read( sockClient, nombreArchivo, MAX_SIZE_NAME ); // Recibe el nombre del archivo.
			
			// # Se le suma la ruta al nombre del archivo #
			// Bytes:   "data/[nombreArchivo].dat" = sizeof(nombreArchivo) + 10 B (incluye nulo).
			rutaArchivo = malloc( (sizeof(nombreArchivo) + (10 * sizeof(char))) * sizeof(char) );
			mempcpy( mempcpy( mempcpy( rutaArchivo, directorioDatos, strlen(directorioDatos) ), nombreArchivo, strlen(nombreArchivo) ), extensionDatos, strlen(extensionDatos) + 1 );
			
			sockArchivo = open( rutaArchivo, O_RDONLY ); // Abre el archivo.
			if ( sockArchivo < 1 ) {   // NO existe; válido.
				buffReply = 0;
				reading = 0;
			} else {                   // Existe; sobreescribe?
				buffReply = 1;
				reading = 1;
				close( sockArchivo );
				
				// # Avisa al cliente de la existencia del archivo #
				write( sockClient, &buffReply, 1 ); 
				
				numBytes = read( sockClient, &buffReply, 1 );
				if ( buffReply == 0 ) {    // Vuelve a elegir el archivo.
					buffReply = 0;
					reading = 1;
					close( sockArchivo );
				} else {    // Caso contrario: SOBREESCRITURA.
					reading = 0;
					close( sockArchivo );
					sockArchivo = open( rutaArchivo, O_WRONLY | O_TRUNC | O_CREAT, 0666 ); // Abre el archivo.
				}
			} 
		} while ( reading == 1 );
		
		
		// # Se leen los contenidos del cliente y se guarda en archivo #
		do {
			numBytes = read( sockClient, &buffData, sizeof(Dato_t) );
			
			// Escribe en archivo.
			if ( numBytes == sizeof(Dato_t) ) {
				write( sockArchivo, &buffData, sizeof(Dato_t) );
			} 
		} while ( numBytes == sizeof(Dato_t) );
		
		close( sockArchivo );
		close( sockClient );

		// Hacer bucle con SEÑALES...
	} while ( endSave == 0 );
	
	// ### TERMINACIÓN DEL SERVIDOR ###
	
	// Recibió SIGTERM:
	free( rutaArchivo );
	close( sockServer );
	
   return;
}


//------------------------------------------------------------------------
// end_session - [ INP ]
//------------------------------------------------------------------------
/* Cierra todo y sale de forma segura.
 */
void end_session() {
	
}
