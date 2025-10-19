/* ### Ej. Integrador + REDES ###
 * # Opciones MENÚ #
 * Cargar base de datos.
 * Realizar ABM (altas-bajas-modificaciones) del equipamiento.
   * ABM: Agregar (altas), eliminar (bajas) o modificar REGISTROS/DATOS.
 * Guardar base de datos con nombre.
 * Ordenar los elementos por especialidad, precio o disponibilidades.
 * Mostrar todos los elementos de una determinada especialidad.
 * Mostrar la fecha de la base de datos.
 *
 * Cada NODO de la lista va a ser un SKU de equipamiento.
 * Los IDs se repiten si los SKUs también se repiten.
 * 
 * # Especialidades #
 * Cardiología.
 * Clínica.
 * Gastroenterología.
 * Cirugía. 
 * Dermatología. 
 * Oftalmología.
 * Traumatología.
 *
 * # IMPORTANTE #
 * Los primeros 11 Bytes del archivo deberán indicar 
 * la fecha de la base de datos en el siguiente formato: DD/MM/YYYY.
 *
 * # CONSIGNA ADICIONAL #
 * Se agregan 2 opciones:
   - Cargar datos remotamente.
   - Guardar datos remotamente.
 * En cada opción, se comunica el programa cliente con el servidor
 * en 1 de 2 puertos distintos; cada puerto se asocia o a CARGAR
 * (leer) o a GUARDAR datos remotamente. Los procesos del mismo archivo
 * se manejan con "fork()".
 */


// ########################################################
// Includes
// ########################################################
#include "../inc/funciones_servidor.h"


// ########################################################
// Variables GLOBLALES
// ########################################################
// char                 endSrv = 0;
// char                 endChild = 0;


/* ### Probando conexión con "net-cat" ###
 * IP (loopback): 127.0.0.1
 * Puerto: [ VER PUERTO POR FUNCIÓN ].
   nc 127.0.0.1 [ VER PUERTO POR FUNCIÓN ]
 */

// Hacer "fork()" para que 2 procesos manejen puertos distintos.
// Servidor solamente toma 2 PUERTOS.
int main( int argc, char *argv[] ) {
   int                  portRD;     // Puerto de lectura (de archivos).
   int                  portWR;     // Puerto de escritura (guardado de archivos).
   pid_t                pid;        // PID del fork (padre-hijo).
   
	
   switch ( argc ) {
      case 1:  // No pasó puertos.
         portRD = PORT_RD;                   // Agarra puerto default de lectura (READ).
         portWR = PORT_WR;                   // Agarra puerto default de lectura (WRITE).
      break;
      
      case 2:  // Pasó 1 puerto.
         portRD = atoi( argv[ 1 ] );
         portWR = PORT_WR;                   // Agarra puerto default de lectura (WRITE).
      break;
      
      case 3:  // Pasó 2 puertos.
         portRD = atoi( argv[ 1 ] );
         portWR = atoi( argv[ 2 ] );
      break;
   }
   
   pid = fork();
	switch ( pid ) {
		case -1:    // ERROR.
			perror( "[ ERROR: NO SE PUDO CREAR EL HIJO CON fork(). ]\n" ); 
			exit(1);
		break;
		
		case 0:     // HIJO.
			usleep(50);
			guardar_datos_server( portWR );
		break;   
		
		default:    // PADRE; obtiene el PID del hijo.
			cargar_datos_server( portRD, pid );
		break;
	}
	
	// Recibió Ctrl+C:
	// ...
	// end_session();
   
   return 0;
}

