// # 2° Parcial - 2025 #
/* # SERVIDOR - PROFESOR/A #
 * Abre archivo "alumnos.dat".
 * "repartido" & "banned" empiezan en FALSE.
 *		Cada cliente entrante dispara un thread de este lado (servidor).
 * 	Validar que el alumno se encuentre en la lista. Caso contrario retornara “E404E”.
 * 	Validar que legajo y DNI coincidan. Caso contrario deber retornar “E403E” y colocar banned en TRUE.
 * 	Validar que banned valga FALSE. Caso contrario retornar “E403E”.
 * 	En caso de pasar las validaciones previas deberá enviar “OK200”, y el archivo de examen aleatorio. 
 * 		Para ello, deberá generar un número pseudo aleatorio entre 1 y 4 y enviar un archivo llamado 
 * 		“TX.tar.gz” donde la X se reemplaza por el número generado. Deberá
 * 		también incrementar el valor de repartido en una unidad.
 */

/* # COMPILACIÓN #
 * clear; gcc -Wall --pedantic-errors -g main_srv.c sock-lib.c -o ../bin/srv.bin
 */


// #################################################################################
// Includes
// #################################################################################
#include "../inc/includes_srv.h"


// #################################################################################
// Variables Globales
// #################################################################################
char						working = 1;			// Por signal handler.
int 						sockFd;					// Por signal handler.


// ---------------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------------
int main( int argc, char *argv[] ) {
	
	
	if ( argc < 2 ) {
		printf( "\n[ USO: ./srv.bin <PORT> ]\n\n" );
	} else {
		manejar_alumnos( atoi( argv[1] ) );
	}
	
	
	pthread_exit( NULL );
}


// ---------------------------------------------------------------------------------
// sig_hand
// ---------------------------------------------------------------------------------
void sig_hand() {
	working = 0;
	close( sockFd );
}


// ---------------------------------------------------------------------------------
// manejar_alumnos
// ---------------------------------------------------------------------------------
/*
 */
int manejar_alumnos( int port ) {
	struct sockaddr_in	localAddr;
	int						clientFd;
	ThreadArg_t				*argThread = NULL;		// Argumentos de threads.
	pthread_t				*tids;
	int						nThreads;
	Nodo_t					*startNode = NULL;	// Compartido entre threads.
	int						dataFd;
	
	
	signal( SIGINT, sig_hand );
	
	sockFd = open_connection( &localAddr, port );
	
	if ( sockFd < 1 ) {
		printf( "\n[ ERROR: NO SE PUDO ABRIR SOCKET. ]\n\n" );
		pthread_exit( NULL );
	} else {
		// # Creación de datos de prueba en "alumnos.dat" #
		// # TEST #
		create_test_data();
		
		// # Apertura de archivo #
		dataFd = open( "../data/prof/alumnos.dat", O_RDONLY );
		
		cargar_lista_archivo( dataFd, &startNode );	// Carga la lista completa de archivo.
		
		close( dataFd );
		
		show_list( startNode );
		
		// if ( (dataFd < 1) || (startNode == NULL) ) {
		if ( (dataFd < 1) ) {
			printf( "\n[ ERROR: NO SE PUDO ABRIR ARCHIVO \"alumnos.dat\". ]\n\n" );
		} else {

			working = 1;
			nThreads = 0;
			tids = (pthread_t *) malloc( sizeof (pthread_t) );
			
			do {
				printf( "\nEsperando pedidos...\n\n" );
				clientFd = aceptar_pedidos( sockFd );
			
				if ( clientFd > 0 ) {
					
					nThreads++;
					tids = (pthread_t *) reallocarray( tids, nThreads, sizeof (pthread_t) );
					
					if ( tids == NULL ) {
						printf( "\n[ ERROR: NO SE PUDO ALOJAR MEMORIA DINÁMICA. ]\n\n" );
					} else {
						
						// # Agrupar bien los argumentos de threads como estructuras... #
						argThread = (ThreadArg_t *) malloc( sizeof (ThreadArg_t) );
						argThread->startList = &startNode;	// Inicializa los argumentos para pasar a threads.
						argThread->inputFd = clientFd;		// FD del alumno.
						
						pthread_create( tids + nThreads - 1, NULL, validacion_alumno, (void *) argThread );
						pthread_detach( tids[nThreads - 1] );	// Libera recursos (incluyendo argumentos) cuando termina.
						
						printf( "* TID creado: %ld [DETACHED].\n", tids[nThreads - 1] );
					}
				}
			} while ( working == 1 );
			
			/*
			for ( int k = 0; k < (nThreads - 1); k++ ) {
				pthread_join( tids[k], NULL );
				// free( argThread... );
			}
			*/
		}	// Archivo abierto exitosamente.
	}	// Socket abierto exitosamente.
	
	return 0;
}


// ---------------------------------------------------------------------------------
// cargar_lista_archivo - MULTI-THREADED
// ---------------------------------------------------------------------------------
/* Lee datos de un archivo "alumnos.dat" y lo carga en RAM como lista doble.
 */
void cargar_lista_archivo( int archivoFd, Nodo_t **inicioLista ) {
	Alumno_t				bufferRd;
	Nodo_t				*auxNode = NULL;
	int					bytesRd;
	
	
	// Lectura de archivo y cargado en lista.
	do {
		bytesRd = read( archivoFd, &bufferRd, sizeof (Alumno_t) );
		
		if ( bytesRd == sizeof (Alumno_t) ) {
			
			if ( (*inicioLista) == NULL ) {		// Caso lista vacía.
				printf( "[ Lista vacía. ]\n" );
			
				(*inicioLista) = (Nodo_t *) malloc( sizeof (Nodo_t) );	// Inicializa nodo.
				
				(*inicioLista)->dato = bufferRd;		// Inicializa dato.
				(*inicioLista)->dato.repartido = FALSE;
				(*inicioLista)->dato.banned = FALSE;
				(*inicioLista)->prevNode = NULL;
				(*inicioLista)->nextNode = NULL;
				
				show_list( *inicioLista );
			} else {										// Caso general (al inicio).
				printf( "[ Nuevo dato leído. ]\n" );
				
				auxNode = (Nodo_t *) malloc( sizeof (Nodo_t) );	// Inicializa nodo.
				
				auxNode->dato = bufferRd;				// Inicializa dato.
				auxNode->dato.repartido = FALSE;
				auxNode->dato.banned = FALSE;
				
				auxNode->prevNode = NULL;				// Enlace de nodos.
				auxNode->nextNode = (*inicioLista);
				(*inicioLista)->prevNode = auxNode;
				(*inicioLista) = auxNode;
				
				show_list( *inicioLista );
			}
		}	// No terminó de leer el archivo.
	} while ( bytesRd == sizeof (Alumno_t) );
	
}


// ---------------------------------------------------------------------------------
// validacion_alumno
// ---------------------------------------------------------------------------------
/* Verifica que el alumno esté en lista por LEGAJO.
 */
void *validacion_alumno( void * args ) {
	int					alumFd;
	int					bytesRd;
	int					temaFd;	
	int					temaRand;
	char					temaRuta[TEMA_LEN] = "../temas/TX.tar.gz";
	char					bufParcial[MAX_BUF_SIZE];		// Escanea el archivo parcial y lo guarda en esta variable 
																	// para mandarlo al alumno.
	Nodo_t				*listInit = *(((ThreadArg_t *)args)->startList);			// Inicio de lista.
																											// Asigna el primer nodo de la lista (dirección del nodo).
	Nodo_t				*auxNode;		// Para escanear la lista entera.
	char					msgs[3][6] = { "E404E", "E403E", "OK200" };
	int					legajoInput;
	int					dniInput;
	char					flagSearchingList;
	char					flagFoundNode;
	int					cursor;
	
	
	srand( time( NULL ) );
	
	alumFd = ((ThreadArg_t *)args)->inputFd;
	
	if ( listInit == NULL ) {
		printf( "\n[ CURSO VACÍO. NO SE ENVÍA NADA. ]\n\n" );
	} else {
		// Verificar alumno en lista por LEGAJO. 
		// Sinó: SRV -> "E404E".
		
		// Leer dato por SOCKET...
		// Recibe un "int legajo".
		bytesRd = read( alumFd, &legajoInput, sizeof (int) );
		bytesRd = read( alumFd, &dniInput, sizeof (int) );
		
		
		if ( (bytesRd != sizeof (int)) || (legajoInput < 1) || (dniInput < 1) ) {
			printf( "\n[ ERROR: DATOS INVÁLIDOs. ]\n\n" );
			write( alumFd, msgs[0], (strlen( msgs[0] ) + 1) * sizeof (char) );	// "E404E".
		} else {
			
			flagSearchingList = 1;
			flagFoundNode = 0;
			// listInit = ((ThreadArg_t *)args)->(*startList);		// Asigna el primer nodo de la lista (dirección del nodo).
			auxNode = listInit;
			while ( (auxNode != NULL) && (flagSearchingList == 1) ) {	// Busca en la lista entera por coincidencias.
				
				printf( "[ Comparando con %d. ]\n", auxNode->dato.legajo );
				
				if ( auxNode->dato.legajo == legajoInput ) {
					
					flagFoundNode = 1;
					flagSearchingList = 0;
				} else {
					
					auxNode = auxNode->nextNode;
				}
			}
			
			// Verificar que LEGAJO & DNI coincidan entre input client y valor de lista. 
			// Sinó: SRV -> "E403E".
			if ( flagFoundNode != 1 ) {
				
				printf( "\n[ ERROR: N/MATCH. %s ]\n\n", msgs[1] );
				write( alumFd, msgs[1], (strlen( msgs[1] ) + 1) * sizeof (char) );	// "E403E".
			} else {
				
				if ( auxNode->dato.DNI != dniInput ) {
					
					printf( "\n[ ERROR: N/MATCH. %s ]\n\n", msgs[1] );
					write( alumFd, msgs[1], (strlen( msgs[1] ) + 1) * sizeof (char) );	// "E403E".
				} else {
					// Si pasa las validaciones: SRV -> "OK200" + EXAMEN.
					// Genera un N° rand 1~4 + archivo "TX.tar.gz" donde la X se reemplaza por el número generado.
					// Se incrementa el valor "repartido" en 1.
					
					printf( "\n[ Coincidencia entre legajo y DNI. Enviando %s. ]\n\n", msgs[2] );
					write( alumFd, msgs[2], (strlen( msgs[2] ) + 1) * sizeof (char) );	// "OK200".
					
					temaRand = rand() % 4 + 1;
					
					// Concatenar strings con N° de tema...
					for ( cursor = 0; temaRuta[cursor] != 'X'; cursor++ ) {}	// For vacío.
					temaRuta[cursor] = (char) (temaRand + '0');	// Reemplaza 'X'.
					
					temaFd = open( temaRuta, O_RDONLY );
					if ( temaFd < 1 ) {
						
						printf( "\n[ ERROR: N/E ARCHIVO. ]\n\n" );
						auxNode->dato.repartido = 0;
					} else {
						
						printf( "[ Archivo \"%s\" abierto exitosamente. ]\n", temaRuta );
						do {	// Parcial con "temaRand" N° de tema.
							bytesRd = read( temaFd, bufParcial, MAX_BUF_SIZE );	// Lee de archivo.
							
							if ( bytesRd > 0 ) {
								write( alumFd, bufParcial, bytesRd );	// Envía al socket.
							}
						} while ( bytesRd > 0 );
						close( temaFd );
						
						auxNode->dato.repartido = 1;
						printf( "\n### Terminó de enviar parcial. Cerrando... ###\n\n" );
					}	// Encontró el tema correctamente.
				}	// Coinciden Legajo y DNI.
			}	// No se llegó al final de lista.
		}	// Datos recibidos por socket válidos.
	}	// Lista no vacía.
	
	
	
	// # Liberación de recursos #
	close( alumFd );
	free( args );
	// # TEST #
	usleep( 3000000 );
	printf( "{ Terminó el usleep() }\n" );
	pthread_exit( NULL );
	return NULL;
}


// ---------------------------------------------------------------------------------
// create_test_data - TEST
// ---------------------------------------------------------------------------------
/* Crea datos de prueba:
 * Datos en "alumnos.dat".
 * Parcial como "TX.tar.gz".
 */
void create_test_data() {
	int				alumnosDataFd;
	char				bufTema[MAX_BUF_SIZE];
	int				temasFd;			// 4 temas.
	const char		temasDir[4][TEMA_LEN] = { "../temas/T1.tar.gz", "../temas/T2.tar.gz", "../temas/T3.tar.gz", "../temas/T4.tar.gz" };
	Alumno_t			alumnosPrueba[3];
	
	
	// # Creación de archivo de datos de alumnos "alumnos.dat" #
	alumnosPrueba[0].legajo = (int) 11;
	alumnosPrueba[0].DNI = (int) 12;
	strcpy( alumnosPrueba[0].nombre, "Pepe" );
	strcpy( alumnosPrueba[0].apellido, "Gomez" );
	
	alumnosPrueba[1].legajo = (int) 13;
	alumnosPrueba[1].DNI = (int) 14;
	strcpy( alumnosPrueba[1].nombre, "Laura" );
	strcpy( alumnosPrueba[1].apellido, "Gonzales" );
	
	alumnosPrueba[2].legajo = (int) 15;
	alumnosPrueba[2].DNI = (int) 16;
	strcpy( alumnosPrueba[2].nombre, "María" );
	strcpy( alumnosPrueba[2].apellido, "Paz" );
	
	alumnosDataFd = open( "../data/prof/alumnos.dat", O_WRONLY | O_TRUNC | O_CREAT, 0666 );
	for ( int i = 0; i < 3; i++ ) {
		write( alumnosDataFd, alumnosPrueba + i, sizeof (Alumno_t) );
	}
	// # Liberación de recursos #
	close( alumnosDataFd );
	
	// ---------------------------------------------------------------------------------
	
	// # Creación de archivo de temas de parcial "TX.tar.gz" #
	for ( int j = 0; j < 4; j++ ) {
		temasFd = open( temasDir[j], O_WRONLY | O_TRUNC | O_CREAT, 0666 );
		
		memset( bufTema, (char) (rand() % (1024 * (j + 1)) + 1), MAX_BUF_SIZE );	// Llena el buffer con números aleatorios.
		printf( "* Buf en Tema %d:   %1024s.\n", j + 1, bufTema );
		
		close( temasFd );
	}
}



// ---------------------------------------------------------------------------------
// show_list - TEST
// ---------------------------------------------------------------------------------
/* Muestra la lista cargada entera.
 */
void show_list( Nodo_t *startNodeShow ) {
	Nodo_t	*nodoCursor = startNodeShow;
	
	printf( "\n### Lista cargada ###\n\n" );
	
	for ( int i = 0; nodoCursor != NULL; i++ ) {
		printf( "\n[ Alumno N° %d ]\n", i + 1 );
		
		printf( "* Legajo: %d\n", nodoCursor->dato.legajo );
		printf( "* DNI: %d\n", nodoCursor->dato.DNI );
		printf( "* Nombre: %s\n", nodoCursor->dato.nombre );
		printf( "* Apellido: %s\n", nodoCursor->dato.apellido );
		
		nodoCursor = nodoCursor->nextNode;
	}
}

