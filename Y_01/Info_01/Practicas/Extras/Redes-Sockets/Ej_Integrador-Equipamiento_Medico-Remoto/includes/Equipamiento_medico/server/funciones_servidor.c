#include "funciones_servidor.h"


/* # Probando conexión con "net-cat" #
 * IP (loopback): 127.0.0.1
 * Puerto: [ VER PUERTO POR FUNCIÓN ].
   nc 127.0.0.1 [ VER PUERTO POR FUNCIÓN ]
 */

//------------------------------------------------------------------------
// cargar_datos_server - [ INP ]
//------------------------------------------------------------------------
/* CARGA la lista entera en un archivo de base de datos.
 * Usar '.dat'.
 * Ídem "guardar_datos()" pero de manera REMOTA.
 * Recibe nombre del archivo y devuelve .
 */
void cargar_datos_server() {
   /*
   int                  sockServer;                // fd para escuchar y recibir conexiones entrantes.
   int                  sockClient;
   char                 ecoMessage[MAXDATASIZE];   // Mensaje a devolver, el "eco".
   char                 mensajeSalida[2][6] = { "salir", "exit" };
   struct sockaddr_in   srvAdress;               // IP y puerto locales.
   int                  closeConection = 0;
   
   printf( "\n# Abriendo socket... #\n" );
   
   if ( ( sockServer = open_conection( &srvAdress ) ) == -1 ) { // Abre un socket.
		perror( "[ ERROR: FALLÓ LA CREACIÓN DE LA CONEXIÓN. ]" ); 
		exit (1);
	}
   
   sockClient = aceptar_pedidos( sockServer );  // Escucha al cliente.
   printf( "\n# ESCUCHANDO PEDIDOS... #\n" );
   */
}


//------------------------------------------------------------------------
// guardar_datos_server - [ INP ]
//------------------------------------------------------------------------
/* GUARDA la lista entera en un archivo de base de datos.
 * Usar '.dat'.
 * Ídem "guardar_datos()" pero de manera REMOTA.
 * Accede al servidor, mandando la lista entera y el nombre del archivo.
 *
 * ESCRIBE en el cliente:
   - 1: si el archivo ya existe (nombre repetido).
   - 0: si el archivo es nuevo.
 */
void guardar_datos_server() {
   /*
   int                  sockServer;                // fd para escuchar y recibir conexiones entrantes.
   int                  sockClient;
   char                 ecoMessage[MAXDATASIZE];   // Mensaje a devolver, el "eco".
   char                 mensajeSalida[2][6] = { "salir", "exit" };
   struct sockaddr_in   srvAdress;               // IP y puerto locales.
   int                  closeConection = 0;
   
   printf( "\n# Abriendo socket... #\n" );
   
   if ( ( sockServer = open_conection( &srvAdress ) ) == -1 ) { // Abre un socket.
		perror( "[ ERROR: FALLÓ LA CREACIÓN DE LA CONEXIÓN. ]" ); 
		exit (1);
	}
   
   sockClient = aceptar_pedidos( sockServer );  // Escucha al cliente.
   printf( "\n# ESCUCHANDO PEDIDOS... #\n" );
   */
}

