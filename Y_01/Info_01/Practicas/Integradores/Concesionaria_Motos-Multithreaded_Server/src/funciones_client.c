// ######################################################
// Includes
// ######################################################
#include "../inc/includes_client.h"


// ######################################################
// Variables Globales
// ######################################################
Nodo_t		*inicioListaSucursal = NULL;
char			saving = 0;
int			threadCount = 0;



// ######################################################
// Signal Handling: guardado automático
// ######################################################
/* Crea un thread que guarda datos de manera local
 * y de manera remota. Atrapa SIGALRM.
 *
 * pthread_t	tid;
 */
void auto_save() {
	pthread_t 		pthreadErr;
	
	
	signal( SIGALRM, auto_save );
	alarm( 60 );	// En 60 segundos vuelve a mandar la señal.
	saving = 1;
	pthreadErr = pthread_create( tid[0], NULL, guardar_datos );	// Thread para guardar datos de forma local y remota.
	if ( pthreadErr != 0 ) {
		fprintf( stderr, "\n[ ERROR: NO SE PUDO GUARDAR AUTOMÁTICAMENTE. NO SE CREÓ EL THREAD. ]\n\n" );
	}
}


//------------------------------------------------------
// show_menu
//------------------------------------------------------
/* Menú con opciones para el cliente.
 * Devuelve la opción elegida.
 */
int show_menu() {
	int				showMenuOpcion;
	
	
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
	int		numeroSerialInput = 0;
	char		nsRepeat = 0;
	Nodo_t	*nodoCursor = startNodeABM;
	
	
	do {
		printf( "# Indique el número serial del vehículo #\n" 
				  "Número:      " );
		better_scanf( "%d", &numeroSerialInput );
		
		if ( numeroSerialInput < 0 ) {
			printf( "\n[ ERROR: INGRESE UN NÚMERO SERIAL VÁLIDO. ]\n\n" );
			altaOption = -1;
			numeroSerialInput = -1;
		} else {
			while ( nodoCursor != NULL ) {
				if ( nodoCursor->datos.serialNum == numeroSerialInput ) {
					nsRepeat = 1;
				} else {
					nodoCursor = nodoCursor->nodoSig;
				}
			}
			
			if ( nsRepeat == 1 ) {	// Checkea por repeticiones del número serial.
				printf( "\n[ ERROR: NÚMERO SERIAL REPETIDO. ]\n\n" );
				altaOption = -1;
				
			} else {
				
				get_user_input( startNodeABM );
				
				printf( "[ ¿Desea continuar en este menú? ]\n"
						  "1)   Sí, continuar.\n"
						  "0)   No, salir.\n"
						  "Opción:      " );
						  
				better_scanf( "%d", &altaOption );
				
				if ( altaOption < 0 ) {
					printf( "\n[ ERROR: INGRESE UNA OPCIÓN VÁLIDA. ]\n\n" );
					altaOption = -1;
				}
			}
		}
	} while ( altaOption != 0 );
}


//------------------------------------------------------
// baja_datos
//------------------------------------------------------
/* Saca datos de la lista.
 */
void baja_datos( Nodo_t **startNodeABM ) {
	int		numeroSerialInput = 0;	
	int 		bajaOption = 0;
	Nodo_t	*nodoCursor = startNodeABM;
	
	
	if ( *startNodeABM = NULL ) {
		printf( "\n[ LISTA VACÍA. ]\n\n" );
	} else {
		do {
			printf( "# Indique el número serial del vehículo #\n" 
					  "Número:      " );
			better_scanf( "%d", &numeroSerialInput );
			
			if ( numeroSerialInput < 0 ) {
				printf( "\n[ ERROR: INGRESE UN NÚMERO SERIAL VÁLIDO. ]\n\n" );
				bajaOption = -1;
				numeroSerialInput = -1;
			} else {
				while ( nodoCursor != NULL ) {	// Checkea por repeticiones del número serial.
					if ( nodoCursor->datos.serialNum == numeroSerialInput ) {
						nsRepeat = 1;
					} else {
						nodoCursor = nodoCursor->nodoSig;
					}
				}
				
				if ( (nsRepeat == 1) && (nodoCursor != NULL) ) {	// Checkea por repeticiones del número serial.
					pop_node( nodoCursor );
				} else {
					printf( "\n[ ERROR: NÚMERO SERIAL NO EXISTENTE. ]\n\n" );
					bajaOption = -1;
				}
			}
		} while ( bajaOption != 0 );
	}
}


//------------------------------------------------------
// mod_datos
//------------------------------------------------------
/* Modifica datos de la lista.
 */
void mod_datos( Nodo_t **startNodeABM ) {
	int		numeroSerialInput = 0;	
	int		stockInput = 0;
	int 		modOption = 0;
	Nodo_t	*nodoCursor = startNodeABM;
	
	
	if ( *startNodeABM = NULL ) {
		printf( "\n[ LISTA VACÍA. ]\n\n" );
	} else {
		do {
			printf( "# Indique el número serial del vehículo #\n" 
					  "Número:      " );
			better_scanf( "%d", &numeroSerialInput );
			
			if ( numeroSerialInput < 0 ) {
				printf( "\n[ ERROR: INGRESE UN NÚMERO SERIAL VÁLIDO. ]\n\n" );
				modOption = -1;
				numeroSerialInput = -1;
			} else {
				while ( nodoCursor != NULL ) {	// Checkea por repeticiones del número serial.
					if ( nodoCursor->datos.serialNum == numeroSerialInput ) {
						nsRepeat = 1;
					} else {
						nodoCursor = nodoCursor->nodoSig;
					}
				}
				
				if ( (nsRepeat == 1) && (nodoCursor != NULL) ) {	// Checkea por repeticiones del número serial.
					// Mostrar el dato seleccionado:
					visualizar_dato( nodoCursor->datos );
					
					do{
						printf( "# Elija un parámetro a modificar #\n"
								  "1)   Stock."
								  "2)   Número serial."
								  "3)   Precio."
								  "------------------------------------------------------\n"
								  "0)   Cancelar y salir.\n"
								  "Opción:      " );
						better_scanf( "%d", &modOption );
						
						if ( (modOption < 0) || (modOption > 3) ) {
							printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n\n" );
							modOption = -1;
						}
					} while ( modOption == -1 );	// Sale con valor correcto o 0.
					
					switch ( modOption ) {
						case 1:	// STOCK.
							do {
								printf( "# Indique el nuevo stock del vehículo #\n" 
										  "Número:      " );
								better_scanf( "%d", &stockInput );
								
								if ( stockInput < 1 ) {
									printf( "\n[ ERROR: STOCK INVÁLIDO. ]\n\n" );
								}
							} while ( stockInput < 1 );
							
							nodoCursor->datos.stock = stockInput;
						break;
						
						case 2:	// SERIAL NUM.
							do {
								printf( "# Indique el nuevo número serial del vehículo #\n" 
										  "Número:      " );
								better_scanf( "%d", &numeroSerialInput );
								
								if ( numeroSerialInput < 1 ) {
									printf( "\n[ ERROR: NÚMERO SERIAL INVÁLIDO. ]\n\n" );
								}
							} while ( numeroSerialInput < 1 );
							
							nodoCursor->datos.serialNum = numeroSerialInput;
						break;
						
						case 3:	// PRECIO.
							do {
								printf( "# Indique el precio del vehículo #\n" 
										  "Número:      " );
								better_scanf( "%f", &precioInput );
								
								if ( precioInput < 1 ) {
									printf( "\n[ ERROR: PRECIO INVÁLIDO. ]\n\n" );
								}
							} while ( precioInput < 1 );
							
							nodoCursor->datos.precio = precioInput;
						break;
						
						default:	// SALIR/EXIT.
							modOption = 0;
					}
					
				} else {
					printf( "\n[ ERROR: NÚMERO SERIAL NO EXISTENTE. ]\n\n" );
					modOption = -1;
				}
			}
		} while ( modOption != 0 );
	}
}


//------------------------------------------------------
// guardar_datos
//------------------------------------------------------
/* Guarda datos de la lista entera en un archivo y en el servidor.
 */
void guardar_datos( Nodo_t *startNodeSAVE, int localDatafdSAVE, int sockfdSAVE ){
	
	
	
	
	saving = 0;	// "Libera" el guardado.
	// Mutex?
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
// visualizar_dato
//------------------------------------------------------
/* Muestra un único dato por pantalla.
 * Serial Num.
 * Precio.
 * Stock.
 */
void visualizar_dato( Datos_t datoVISUAL ) {
	printf( "\n------------------------------------------------------\n" );
	printf( "# Número de serie:      %d #\n", datoVISUAL.serialNum );
	printf( "# Precio:               %f #\n", datoVISUAL.precio );
	printf( "# Stock:                %d #\n", datoVISUAL.stock );
	printf( "\n------------------------------------------------------\n\n" );
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
	
	// Liberación de threads.
	
}

