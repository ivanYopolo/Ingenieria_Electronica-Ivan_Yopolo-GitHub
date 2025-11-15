// ######################################################
// Includes
// ######################################################
#include "../inc/includes_client.h"


// ######################################################
// Variables Globales
// ######################################################
// char					saving = 0;
// pthread_mutex_t   dataSave.lockSAVE;
// Nodo_t				*inicioListaSucursal = NULL;
int					threadCount = 0;	// N° de threads creados (sin contar el main).
pthread_t			*tid = NULL;		// TIDs de los threads (hecho dinámicamente).
Thread_Input_t 	dataSave;			// Global por signal handler "auto_save".
/*
	typedef struct 	Thread_Input_s {
		Nodo_t 				*startNodeSAVE;
		int 					localDatafdSAVE;
		int 					sockfdSAVE;
		pthread_mutex_t	lockSAVE;	// MUTEX.
	} Thread_Input_t;	// Puede ser adaptado a doble puerto RD/WR.
*/


// ######################################################
// Signal Handling: guardado automático
// ######################################################
/* Crea un thread que guarda datos de manera local
 * y de manera remota. Atrapa SIGALRM.
 */
void auto_save() {
	int 			pthreadErr;		// Manejo de errores en creaciones de threads.
	
	
	signal( SIGALRM, auto_save );
	
	// Thread para guardar datos de forma local y remota.
	tid = (pthread_t *) reallocarray( tid, threadCount + 1, sizeof (pthread_t) );
	
	if ( tid != NULL ) {
		fprintf( stderr, "\n[ ERROR: NO SE PUDO GUARDAR AUTOMÁTICAMENTE. ]\n"
							  "[ FALLÓ \"reallocarray()\". FALTA MEMORIA. ]\n\n" );
	} else {
		// Manda al thread a guardar.
		pthreadErr = pthread_create( tid + threadCount, NULL, &guardar_datos, (void *) dataSave );	
		// Guarda automáticamente el TID en "tid[threadCount]".
		
		if ( pthreadErr != 0 ) {	// Checkeo de errores.
			fprintf( stderr, "\n[ ERROR: NO SE PUDO GUARDAR AUTOMÁTICAMENTE. ]\n" 
								  "[ FALLÓ \"pthread_create()\". ]\n\n" );
		
		} else {
			pthread_detach( tid[threadCount] );		// Lo hace independiente.
			threadCount++;
		}
		
		alarm( 60 );	// En 60 segundos vuelve a mandar la señal.
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
		
		better_scanf( "%4d", &showMenuOpcion );
		
		if ( (showMenuOpcion < 0) || (showMenuOpcion > 4) ) {
			printf( "\n[ ERROR: ELIJA UNA OPCIÓN VÁLIDA. ]\n" );
			showMenuOpcion = -1;
		}
	} while ( showMenuOpcion == -1 );
	
	return showMenuOpcion;
}


//------------------------------------------------------
// is_serial_num_repeated
//------------------------------------------------------
/* Busca por números seriales repetidos (coincidencias)
 *
 * return:
	- NULL: lista vacía o no se encontró el N° serial.
	- != NULL: dirección del nodo con la coincidencia.
 */
Nodo_t *is_serial_num_repeated( Nodo_t **startNodeSERIALNUM, int compareSerialNum ) {
	Nodo_t	*nodoCursor = NULL;
	char	   nsRepeat = 0;
	
	
	if ( startNodeSERIALNUM == NULL ) {
		printf( "\n-----------------   LISTA VACÍA   --------------------\n\n" );
		
	} else {
		nodoCursor = startNodeSERIALNUM;
		
		while ( nodoCursor != NULL ) {	// Checkea por repeticiones del número serial.
			if ( nodoCursor->datos.serialNum == compareSerialNum ) {
				nsRepeat = 1;	// COINCIDENCIA.
			} else {
				nodoCursor = nodoCursor->nodoSig;
			}
		}
	}
	
	if ( nsRepeat == 0 ) {	// Caso: no hay coincidencias.
		nodoCursor = NULL;
	}
	
	
	return nodoCursor;
}


//------------------------------------------------------
// get_user_input
//------------------------------------------------------
/* Obtiene datos del usuario.
 */
void get_user_input( Nodo_t **startNodeINPUT ) {
	// Nodo_t			*inputNode = NULL;
	Datos_t			inputData;
	char				inputting = 1;
	int				numeroSerialInput = 0;
	int				stockInput = 0;
	float				precioInput = 0;
	
	
	do {
		printf( "# Ingrese los datos de forma ordenada #\n" );
		
		do {
			printf( "* Número serial:      " );
			better_scanf( "%4d", &numeroSerialInput );
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
			better_scanf( "%4d", &stockInput );
			if ( stockInput < 1 ) {
				printf( "\n[ ERROR: INGRESE UN NÚMERO POSITIVO. ]\n\n" );
				stockInput = 0;
			} else {
				inputData.stock = stockInput;
			}
		} while ( stockInput == 0 );
		
		do {
			printf( "* Precio:      " );
			better_scanf( "%4d", &precioInput );
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
	Datos_t			inputDataSERVER;
	int 				bytesRead = 0;
	int				dataSize = sizeof (Datos_t);
	char				isListEmpty = 1;	// Empieza vacía la lista.
	// # LOG #
	int				fdLog;
	fdLog = open( "../dump/cargar_datos_casa_central.log", O_CREAT | O_TRUNC | O_WRONLY, 0666 );
	
	
	do {
		/* TODO
		 * Protocolo servidor-cliente...
		 * ...
		 */
		
		bytesRead = read( sockfdLOAD, &inputDataSERVER, dataSize );
		
		if ( bytesRd == dataSize ) {
			isListEmpty = 0;
			push_node( startNodeLOAD, inputDataSERVER );
			
			// # LOG #
			dprintf( fdLog, "[ Dato recibido. ]\n" );
			
			/* TODO
			 * Verificar datos repetidos...
			 * Preguntar al usuario cuáles mantener...
			 */
		} else {
			// Caso de primera lectura con cantidad de bytes leídos distinta a la esperada.
			if ( isListEmpty == 1 ) {
				printf( "\n-----------------   LISTA VACÍA   --------------------\n\n" );
			}
		}
	} while ( bytesRead == dataSize );
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

			better_scanf( "%4d", &ambOption );
			
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
		
		better_scanf( "%4d", &ambOption );
		// scanf( "%4d", &ambOption );
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
		better_scanf( "%4d", &numeroSerialInput );
		
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
						  
				better_scanf( "%4d", &altaOption );
				
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
	// Nodo_t	*nodoCursor = startNodeABM;
	
	
	if ( *startNodeABM = NULL ) {
		printf( "\n-----------------   LISTA VACÍA   --------------------\n\n" );
	} else {
		do {
			printf( "# Indique el número serial del vehículo #\n" 
					  "Número:      " );
			better_scanf( "%4d", &numeroSerialInput );
			
			if ( numeroSerialInput < 0 ) {
				printf( "\n[ ERROR: INGRESE UN NÚMERO SERIAL VÁLIDO. ]\n\n" );
				bajaOption = -1;
				numeroSerialInput = -1;
			} else {
				// Checkea por repeticiones del número serial.
				nodoCursor = is_serial_num_repeated( startNodeABM, numeroSerialInput );
				if ( nodoCursor != NULL ) {	
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
		printf( "\n-----------------   LISTA VACÍA   --------------------\n\n" );
	} else {
		do {
			printf( "# Indique el número serial del vehículo #\n" 
					  "Número:      " );
			better_scanf( "%4d", &numeroSerialInput );
			
			if ( numeroSerialInput < 0 ) {
				printf( "\n[ ERROR: INGRESE UN NÚMERO SERIAL VÁLIDO. ]\n\n" );
				modOption = -1;
				numeroSerialInput = -1;
				
			} else {
				
				nodoCursor = is_serial_num_repeated( startNodeABM, numeroSerialInput );
				
				// if ( (nsRepeat == 1) && (nodoCursor != NULL) ) {	// Checkea por repeticiones del número serial.
				if ( nodoCursor != NULL ) {	// Checkea por repeticiones del número serial.
					// Muestra el dato seleccionado:
					visualizar_dato( nodoCursor->datos );
					
					do{
						printf( "# Elija un parámetro a modificar #\n"
								  "1)   Stock."
								  "2)   Número serial."
								  "3)   Precio."
								  "------------------------------------------------------\n"
								  "0)   Cancelar y salir.\n"
								  "Opción:      " );
						better_scanf( "%4d", &modOption );
						
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
								better_scanf( "%4d", &stockInput );
								
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
								better_scanf( "%4d", &numeroSerialInput );
								
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
								better_scanf( "%4f", &precioInput );
								
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
// guardar_datos - [THREADED]
//------------------------------------------------------
/* Guarda datos de la lista entera en un archivo y en el servidor.
 * Puede entrar de forma ASÍNCRONA (cada 1 minuto).
 */
// void guardar_datos( Nodo_t *startNodeSAVE, int localDatafdSAVE, int sockfdSAVE ){
void guardar_datos( void *dataSaveINPUT ){
	Nodo_t			*nodoCursorSAVE = NULL;
	int 				bytesWrtFile = 0;
	int 				bytesWrtSocket = 0;
	const int		dataSize = sizeof (Datos_t);
	Thread_Input_t dataSAVE = (Thread_Input_t) (*dataSaveINPUT);
	
	pthread_mutex_lock( &(dataSave.lockSAVE) );		// Asegura que ningún thread pise la función.
	
	/* Revisar nombre distintos de archivos...
	 * 
	 */
	// localDatafd = open( "../data/sucursal/nombre_archivo_1.dat", O_CREAT | O_TRUNC | O_WRONLY, 0666 );
	
	
	// if ( startNodeSAVE == NULL ) {
	if ( dataSAVE.startNodeSAVE == NULL ) {
		// printf( "\n[ LISTA VACÍA; NADA POR GUARDAR. ]\n\n" );
		
	} else {
		// # Guardado local + remoto #
		
		// nodoCursorSAVE = startNodeSAVE;
		nodoCursorSAVE = dataSAVE.startNodeSAVE;
		while ( nodoCursorSAVE != NULL ) {
			// bytesWrtFile = write( localDatafdSAVE, &(nodoCursorSAVE->datos), dataSize );	// Local.
			bytesWrtFile = write( dataSAVE.localDatafdSAVE, &(nodoCursorSAVE->datos), dataSize );	// Local.
			
			// bytesWrtSocket = write( sockfdSAVE, &(nodoCursorSAVE->datos), dataSize );		// Remoto.
			bytesWrtSocket = write( dataSAVE.sockfdSAVE, &(nodoCursorSAVE->datos), dataSize );		// Remoto.
			
			nodoCursorSAVE = nodoCursorSAVE->nodoSig;
			
			if ( nodoCursorSAVE != NULL ) {				
				if ( (bytesWrtFile < dataSize) || (bytesWrtSocket < dataSize) ) {
					fprintf( stderr, "\n[ ERROR: NO SE PUDO ESCRIBIR EN EL ARCHIVO Y/O EN EL SERVIDOR. ]\n\n" );
					nodoCursorSAVE = NULL;	// Sale del while().
					// exit( -1 );
				}
			}
		}
	}
	
	// # Liberación de recursos #
	// close( localDatafdSAVE );
	close( dataSAVE.localDatafdSAVE );
	
	pthread_mutex_unlock( &(dataSave.lockSAVE) );	// "Libera" el guardado.
	
	pthread_exit( NULL );
}


//------------------------------------------------------
// visualizar_lista_local
//------------------------------------------------------
/* Muestra la lista cargada de manera local.
 */
void visualizar_lista_local( Nodo_t *startNodeVISUAL ) {
	Nodo_t		*nodoCursorVISUAL = NULL;


	if ( startNodeVISUAL == NULL ) {
		printf( "\n-----------------   LISTA VACÍA   --------------------\n\n" );
	} else {
		nodoCursorVISUAL = startNodeVISUAL;
		while ( nodoCursorVISUAL != NULL ) {
			visualizar_dato( nodoCursorVISUAL->datos );
			
			nodoCursorVISUAL = nodoCursorVISUAL->nodoSig;
		}
	}
}


//------------------------------------------------------
// visualizar_lista_remoto
//------------------------------------------------------
/* Muestra la lista cargada de manera remota.
 */
void visualizar_lista_remoto( int sockfdVISUAL ) {
	Datos_t			datoCursorVISUAL;
	int				bytesRd = 0;
	const int		dataSize = sizeof (Datos_t);
	char				isListEmpty = 1;
	
	
	do {
		/* TODO
		 * Protocolo servidor-cliente...
		 * ...
		 */
		
		bytesRd = read( sockfdVISUAL, &datoCursorVISUAL, dataSize );
		
		if ( bytesRd == dataSize ) {
			visualizar_dato( datoCursorVISUAL );
			isListEmpty = 0;
		} else {
			// Caso de primera lectura con cantidad de bytes leídos distinta a la esperada.
			if ( isListEmpty == 1 ) {
				printf( "\n-----------------   LISTA VACÍA   --------------------\n\n" );
			}
		}
	} while ( bytesRd == dataSize );
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
// void sincronizar( Nodo_t **startNodeSYNC, int localDatafdSYNC, int sockfdSYNC ) {
void sincronizar( void *dataSYNC ) {
	guardar_datos( *startNodeSYNC, localDatafdSYNC, sockfdSYNC );
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
	
	
	// Guardado de datos (local y remoto) + cierre de socket y archivo.
	guardar_datos( startNodeEND, sockfdEND );
	close( sockfdEND );
	close( localDatafdEND );
	
	// Liberación recursos de la lista completa.
	while ( nodoTemp != NULL ) {
		nodoPrevTemp = nodoTemp;
		nodoTemp = nodoTemp->nodoSig;
		free( nodoPrevTemp );
	}
	
	// Liberación de threads.
	free( tid );	// Libera array de TIDs.
	
	// pthread_join( tidThreadX, NULL );	// No retorna nada, se le pasa el TID específico.
	/*
	for ( int i = 0; i < threadCount; i++ ) {
		pthread_join( tids[i], NULL );
	}
	*/
	
	// Destrucción del MUTEX.
	pthread_mutex_destroy( &(dataSave.lockSAVE) );
}

