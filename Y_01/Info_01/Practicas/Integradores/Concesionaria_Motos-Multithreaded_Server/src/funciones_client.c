// ######################################################
// Includes
// ######################################################
#include "../inc/includes_client.h"


// ######################################################
// Variables Globales
// ######################################################
Nodo_t		listaSucursal;
char			saving = 0;



// ######################################################
// Signal Handling: guardado automático
// ######################################################
/* Crea threads separados, uno que guarda datos de manera local,
 * y otro de manera remota. Atrapa SIGALRM.
 *
 * pthread_t	tid[2];
 *	
 * tid[0] = thread para guardar local.
 * tid[1] = thread para guardar en server.
 */
void auto_save() {
	signal( SIGALRM, auto_save );
	alarm( 1 );
	saving = 1;
	pthread_create( tid[0], NULL, guardar_datos );	// Thread para guardar datos de forma local y remota.
}


//------------------------------------------------------
// show_menu
//------------------------------------------------------
/* Menú con opciones para el cliente.
 * Devuelve la opción elegida.
 */
int show_menu() {
	int	showMenuOpcion;
	
	do {
		printf( "1)   Crear, quitar o modificar datos de la concesionaria.\n"
				  "2)   Guardar datos cargados en el sistema (local y en la nube).\n"
				  "3)   Visualizar los datos cargados.\n" 
				  "4)   Visualizar los datos guardados en la nube.\n" 
				  "------------------------------------------------------\n"
				  "0)   Salir.\n" 
				  "------------------------------------------------------\n"
				  "Opción:      " );
		
		better_scanf( "%d", &showMenuOpcion );
		
		if ( (showMenuOpcion < 0) || (showMenuOpcion > 4) ) {
			printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n" );
			showMenuOpcion = -1;
		}
	} while ( showMenuOpcion == -1 );
	
	return showMenuOpcion;
}

//------------------------------------------------------
// get_user_input
//------------------------------------------------------
/* Obtiene datos del usuario.
 */
void get_user_input( Nodo_t **startNodeINPUT ) {
	Datos_t		inputData;
	// Nodo_t		*inputNode = NULL;
	char			inputting = 1;
	int			numeroSerialInput = 0;
	int			stockInput = 0;
	float			precioInput = 0;
	
	
	do {
		printf( "# Ingrese los datos de forma ordenada #\n" );
		
		do {
			printf( "* Número serial:      " );
			better_scanf( "%d", &numeroSerialInput );
			if ( numeroSerialInput < 1 ) {
				printf( "\n[ ERROR: INGRESE UN NÚMERO SERIAL VÁLIDO. ]\n\n" );
				numeroSerialInput = 0;
			} else {
				if ( is_serial_repeated( startNodeINPUT, numeroSerialInput ) == 1 ) {
					printf( "\n[ ERROR: NÚMERO SERIAL TOMADO. ]\n\n" );
					numeroSerialInput = 0;
				} else {
					inputData.serialNum = numeroSerialInput;
				}
			}
		} while ( numeroSerialInput == 0 );
		
		do {
			printf( "* Stock:      " );
			better_scanf( "%d", &stockInput );
			if ( stockInput < 1 ) {
				printf( "\n[ ERROR: INGRESE UN NÚMERO POSITIVO. ]\n\n" );
				stockInput = 0;
			} else {
				inputData.stock = stockInput;
			}
		} while ( stockInput == 0 );
		
		do {
			printf( "* Precio:      " );
			better_scanf( "%d", &precioInput );
			if ( precioInput < 1 ) {
				printf( "\n[ ERROR: INGRESE UN PRECIO VÁLIDO. ]\n\n" );
				precioInput = 0;
			} else {
				inputData.precio = precioInput;
			}
		} while ( precioInput == 0 );
		
		push_node( startNodeINPUT, inputData );
	} while ( inputting != 0 );
}

//------------------------------------------------------
// cargar_datos_casa_central
//------------------------------------------------------
/* Carga datos desde la CC (Casa Central), como sincronización.
 * Se sincroniza una vez se conecta con CC.
 * [OPCIONAL]
	- Puede sincronizarse cada minuto.
 */
void cargar_datos_casa_central( Nodo_t **startNodeLOAD, int sockfdLOAD ) {
	
	
}


//------------------------------------------------------
// abm_lista
//------------------------------------------------------
/* Altas, bajas, modificaciones de la lista de datos local.
 */
void abm_lista( Nodo_t **startNodeABM ) {
	int	ambOption = 0;
	
	
	do {
		do {
			printf( "# Elija una de las siguientes opciones #\n" 
					  "1)   Agregar datos.\n"
					  "2)   Sacar datos.\n"
					  "3)   Modificar datos.\n"
					  "------------------------------------------------------\n"
					  "0)   Salir.\n"
					  "Opción:      " );

			better_scanf( "%d", ambOption );
			
			if ( (ambOption < 0) || (3 < ambOption) ) {
				printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
				ambOption = 0;
			}
		} while ( ambOption == 0 );
		
		/* Implementar threads para cada función BLOQUEANTE.
		 */
		switch ( ambOption ) {
			case 1:	// Alta.
				alta_datos( startNodeABM );
			break;
			
			case 2:	// Baja.
				baja_datos( startNodeABM );
			break;
			
			case 3:	// Mod.
				mod_datos( startNodeABM );
			break;
		}
		
		
		printf( "[ ¿Desea continuar en este menú? ]\n"
				  "1)   Sí, continuar.\n"
				  "0)   No, salir.\n"
				  "Opción:      " );
		
		better_scanf( "%d", ambOption );
	} while ( ambOption != 0 );
}


//------------------------------------------------------
// alta_datos
//------------------------------------------------------
/* Agrega datos a la lista.
 */
void alta_datos( Nodo_t **startNodeABM ) {
	int 		altaOption = 0;
	int		numeroSerial = 0;
	Nodo_t	*nodoCursor = startNodeABM;
	
	
	do {
		printf( "# Indique el número serial del vehículo #\n" 
				  "Número:      " );
		better_scanf( "%d", &numeroSerial );
		
		if ( numeroSerial < 0 ) {
			printf( "\n[ ERROR: INGRESE UN NÚMERO SERIAL VÁLIDO. ]\n\n" );
			altaOption = 0;
			numeroSerial = 0;
		} else {
			get_user_input( startNodeABM );
			
			printf( "[ ¿Desea continuar en este menú? ]\n"
					  "1)   Sí, continuar.\n"
					  "0)   No, salir.\n"
					  "Opción:      " );
					  
			better_scanf( "%d", &altaOption );
			
			if ( altaOption < 0 ) {
				printf( "\n[ ERROR: INGRESE UNA OPCIÓN VÁLIDA. ]\n\n" );
				altaOption = 0;
			}
		}
	} while ( altaOption == 0 );
}


//------------------------------------------------------
// baja_datos
//------------------------------------------------------
/* Saca datos de la lista.
 */
void baja_datos( Nodo_t **startNodeABM ) {
	int 	bajaOption = 0;
	
	if ( *startNodeABM = NULL ) {
		printf( "\n[ LISTA VACÍA. ]\n\n" );
	} else {
		
	}
}


//------------------------------------------------------
// mod_datos
//------------------------------------------------------
/* Modifica datos de la lista.
 */
void mod_datos( Nodo_t **startNodeABM ) {
	int 	modOption = 0;
	
	
	if ( *startNodeABM = NULL ) {
		printf( "\n[ LISTA VACÍA. ]\n\n" );
	} else {
		
	}
}


//------------------------------------------------------
// guardar_datos
//------------------------------------------------------
/* Guarda datos de la lista entera en un archivo y en el servidor.
 */
void guardar_datos( Nodo_t *startNodeSAVE, int localDatafdSAVE, int sockfdSAVE ){
	
	
	
	
	saving = 0;	// "Libera" el guardado.
}


//------------------------------------------------------
// visualizar_lista_local
//------------------------------------------------------
/* Muestra la lista cargada de manera local.
 */
void visualizar_lista_local( Nodo_t *startNodeVISUAL ) {
	
	
}


//------------------------------------------------------
// visualizar_lista_remoto
//------------------------------------------------------
/* Muestra la lista cargada de manera remota.
 */
void visualizar_lista_remoto( int sockfdVISUAL ) {
	
	
}


//------------------------------------------------------
// sincronizar
//------------------------------------------------------
/* Guarda datos de forma local, carga datos remotos y
 * sincroniza los datos locales con los datos remotos.
 */
void sincronizar( Nodo_t **startNodeSYNC, int localDatafdSYNC, int sockfdSYNC ) {
	// guardar_datos( *startNodeSYNC, localDatafdSYNC, sockfdSYNC );
	// cargar_datos_casa_central( startNodeSYNC, sockfdSYNC );
}


//------------------------------------------------------
// A
//------------------------------------------------------
/* A
 */
void A() {
	
	
}


//------------------------------------------------------
// end_session
//------------------------------------------------------
/* Devuelve recursos al sistema de manera segura y guarda antes de salir.
 */
void end_session( Nodo_t *startNodeEND, int sockfdEND, int localDatafdEND ) {
	Nodo_t		*nodoTemp = startNodeEND;
	Nodo_t		*nodoPrevTemp = NULL;
	
	
	guardar_datos( startNodeEND, sockfdEND );
	close( sockfdEND );
	close( localDatafdEND );
	
	// Libera recursos de la lista completa.
	while ( nodoTemp != NULL ) {
		nodoPrevTemp = nodoTemp;
		nodoTemp = nodoTemp->nodoSig;
		free( nodoPrevTemp );
	}
}

