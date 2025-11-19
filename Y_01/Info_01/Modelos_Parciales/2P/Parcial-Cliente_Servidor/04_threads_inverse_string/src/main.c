// ### Consigna 4 -  Threads ###
// clear; gcc main.c -o ../bin/prog.bin -lpthread


#include "../inc/includes.h"


// # GLOBAL #
char 					**inversedStrings = NULL;
pthread_mutex_t	inverStrLock;


// ------------------------------------------------------
// main
// ------------------------------------------------------
int main( int argc, char *argv[] ) {
	int 					nLetters;
	int 					arrayCursor;
	
	
	if ( argc < 2 ) {
		printf( "\n[ USO: ./prog.bin mensaje01 mensaje02 ... mensajeNN ]\n\n" );
		exit(1);
	} else {
		// MUTEX
		pthread_mutex_init( &inverStrLock, NULL );
		
		// Inicializa el array de strings dinámico # GLOBAL #.
		inversedStrings = (char **) malloc( (argc - 1) * sizeof (char *) );
		
		// Inicializa los strings de cada puntero dinámico # GLOBAL #.
		for ( nLetters = 0; nLetters < MAX_STR_SIZE; nLetters++ ) {
			inversedStrings[nLetters] = (char *) malloc( MAX_STR_SIZE * sizeof (char) );
		}
		// MAX_STR_SIZE define el N° máx de caracteres por string.
		
		// Llama a la función que dispara los threads a realizar las tareas.
		invertir( argv + 1, inversedStrings, argc - 1 );
		
		
		// # Visualizando output #
		
		printf( "\n### Array de strings originales ###\n\n" );
		for ( arrayCursor = 1; arrayCursor < argc; arrayCursor++ ) {
			printf( "%d)   \"%s\".\n", arrayCursor + 1, argv[arrayCursor] );
		}
		
		printf( "\n### Array de strings invertidos ###\n\n" );
		for ( arrayCursor = 0; arrayCursor < (argc - 1); arrayCursor++ ) {
			printf( "%d)   \"%s\".\n", arrayCursor + 1, inversedStrings[arrayCursor] );
		}
		
		// # Liberación de recursos #.
		free( inversedStrings );
		pthread_mutex_destroy( &inverStrLock );
	}
	
	pthread_exit( NULL );
}


// ------------------------------------------------------
// invertir
// ------------------------------------------------------
/* Agarra un array de strings de "src" y los invierte,
 * guardándolos en "dst".
 * Por cada string, dispara un thread que realice el trabajo.
 */
void invertir( char **src, char **dst, int strc ) {
	pthread_t	*tidList;
	
	if ( strc < 1 ) {
		// NO HACE NADA.
	} else {
		// Creación de threads por N° de strings recibidos.
		tidList = malloc( strc * sizeof (pthread_t) );
		
		for ( int nThreads = 0; nThreads < strc; nThreads++ ) {
			pthread_create( tidList + nThreads, NULL, (void *) (&string_reverse), (void *) src[nThreads] );
			printf( "# Creando Thread N° [%d]. TID = [%ld]. #\n", nThreads + 1, tidList[nThreads] );
			usleep( 100000 );
		}
		
		printf( "\n------------------------------------------------------\n\n" );
		
		// Joineo de threads con el valor de retorno (el string invertido).
		for ( int nThreads = 0; nThreads < strc; nThreads++ ) {
			pthread_join( tidList[nThreads], (void **) (dst + nThreads) );
			printf( "# Terminó Thread TID = [%ld]. #\n", tidList[nThreads] );
		}
		
		printf( "\n------------------------------------------------------\n\n" );
		
		// # Liberación de recursos #.
		free( tidList );
	}
}


// ------------------------------------------------------
// string_reverse
// ------------------------------------------------------
/* Invierte un string.
 */
void *string_reverse( void * const arg ) {
	char 	*strInput = NULL;
	char 	*strOutput = NULL;
	int	stringLen = 0;
	int	cursorOutput;
	int	cursorInput;
	
	
	
	if ( arg == NULL ) {
		printf( "[ string_reverse: String vacío. ]" );
	} else {
		usleep( 100000 );
		
		strInput = (char *) arg;
		
		stringLen = strlen( strInput );
		
		strOutput = (char *) malloc( (stringLen + 1) * sizeof (char) );
		strOutput[stringLen] = '\0';
		
		pthread_mutex_lock( &inverStrLock );
		/* 1) Mete último char de "strInput" en primera pos de "strOutput".
		 * 2) Mete primer char de "strInput" en última pos de "strOutput".
		 * Trabajo 2x1. ;)
		 */
		usleep( 500000 );
		for ( cursorOutput = 0, cursorInput = stringLen - 1; \
				cursorOutput <= cursorInput; \
				cursorOutput++, cursorInput-- ) {
			
			strOutput[cursorOutput] = strInput[cursorInput];	// Asignación último -> primero.
			strOutput[cursorInput] = strInput[cursorOutput];	// Asignación primero -> último.
		}
		pthread_mutex_unlock( &inverStrLock );
	}
	
	
	pthread_exit( (void *) strOutput );
	
	return NULL;
}

