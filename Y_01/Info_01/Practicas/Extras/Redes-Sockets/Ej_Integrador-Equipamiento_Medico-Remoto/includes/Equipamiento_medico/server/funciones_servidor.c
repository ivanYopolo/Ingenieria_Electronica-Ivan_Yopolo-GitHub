#include "funciones_servidor.h"


/* # Probando conexión con "net-cat" #
 * IP (loopback): 127.0.0.1
 * Puerto: [ VER PUERTO POR FUNCIÓN ].
   nc 127.0.0.1 [ VER PUERTO POR FUNCIÓN ]
 */

//------------------------------------------------------------------------
// cargar_datos_server - [ REV ]
//------------------------------------------------------------------------
/* CARGA la lista entera en un archivo de base de datos.
 * Usar '.dat'.
 * Ídem "guardar_datos()" pero de manera REMOTA.
 *
 * # Recibe del cliente #
 * - (#) Nombre del archivo a leer.
 * - (##) 1: TERMINA EL SERVIDOR.
 * - (##) 0: continúa su funcionamiento normal.
 * 
 * # Envía al cliente #
 * - (#) 1: si el archivo existe.
 * - (#) 0: si no existe tal archivo.
 * - DATOS DE CADA NODO DE LA LISTA.
 */
char cargar_datos_server( int portRD ) {
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
   int                  longArchivo;               // Longitud del nombre del archivo a recibir.
   char                 buffReply;                 // 0: no existe el archivo. 1: existe el archivo.
   Dato_t               buffData;
   char                 endSrv = 0;
   
   
   // printf( "\n# Abriendo socket... #\n" );
   sockServer = open_conection( &srvAddr, portRD );   // Abre un socket.
   if ( sockServer == -1 ) { 
		perror( "[ ERROR: FALLÓ LA CREACIÓN DE LA CONEXIÓN. ]" ); 
		exit(1);
	}
   
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
   } while ( reading == 1 );
   
   // # Se abre el archivo y se leen los contenidos #
   do {
      numBytes = read( sockArchivo, &buffData, sizeof(Dato_t) );
      
      // Envía datos al cliente.
      if ( numBytes == sizeof(Dato_t) ) {
         write( sockClient, &buffData, sizeof(Dato_t) );
      } 
   } while ( numBytes == sizeof(Dato_t) );
   
   // # Recibe instrucción para terminar el servidor o no (según si terminó el cliente) #
   numBytes = read( sockClient, &endSrv, sizeof(char) );
   if ( endSrv != 1 ) {
      endSrv = 0;       // Sigue el servidor activo.
   }  // Naturalmente, si no entra al if(), es 1. Por ende, termina.
   
   close( sockArchivo );
   close( sockClient );
   
   return endSrv;
}


//------------------------------------------------------------------------
// guardar_datos_server - [ INP ]
//------------------------------------------------------------------------
/* GUARDA la lista entera en un archivo de base de datos.
 * Usar '.dat'.
 * Ídem "guardar_datos()" pero de manera REMOTA.
 * Accede al servidor, mandando la lista entera y el nombre del archivo.
 *
 * # Recibe del cliente #
 * - (#) Nombre del archivo a guardar.
 * - DATOS DE CADA NODO DE LA LISTA ENTERA.
 * - (##) 1: TERMINA EL SERVIDOR.
 * - (##) 0: continúa su funcionamiento normal.
 *
 * # Envía al cliente #
 * - (#) 1: si el archivo ya existe (nombre repetido).
 * - (#) 0: si no existe tal archivo.
 */
char guardar_datos_server( int portWR ) {
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
   char                 endSrv = 0;
   
   
   // printf( "\n# Abriendo socket... #\n" );
   if ( ( sockServer = open_conection( &srvAddr, portWR ) ) == -1 ) { // Abre un socket.
		perror( "[ ERROR: FALLÓ LA CREACIÓN DE LA CONEXIÓN. ]" ); 
		exit (1);
	}
   
   sockClient = aceptar_pedidos( sockServer );  // Escucha al cliente.
   
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
   
   
   // # Recibe instrucción para terminar el servidor o no (según si terminó el cliente) #
   numBytes = read( sockClient, &endSrv, sizeof(char) );
   if ( endSrv != 1 ) {
      endSrv = 0;       // Sigue el servidor activo.
   }  // Naturalmente, si no entra al if(), es 1. Por ende, termina.
   
   close( sockArchivo );
   close( sockClient );
   
   return endSrv;
}

