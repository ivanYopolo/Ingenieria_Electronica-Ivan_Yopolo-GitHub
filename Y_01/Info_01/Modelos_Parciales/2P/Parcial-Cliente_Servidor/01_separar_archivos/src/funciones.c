#include "../inc/includes.h"

// clear; gcc -Wall --pedantic-errors main.c -lpthread -o ../bin/prog.bin


// ------------------------------------------------------
// main
// ------------------------------------------------------
int main( int argc, char *argv[] ) {
	Config_Data_t		dataRd;
	
	
	if ( argc != 2 ) {
		printf( "\n[ USO: prog.bin archivo_01.dat ]\n\n" );
		exit(1);
	} else {
		dataRd = load_conf( argv[1] );
		
		printf( "\n------------------------------------------------------\n\n" );
		printf( "* PORT:     %d\n", dataRd.port );
		printf( "* BACKLOG:  %d\n", dataRd.backLog );
		printf( "* ARCHIVOS: " );
		for ( int strCursor = 0; dataRd.archStr[strCursor] != NULL; strCursor++ ) {
			printf( "%s - ", dataRd.archStr[strCursor] );
			free( dataRd.archStr[strCursor]  );
		}
		printf( "\n\n" );
		
		free( dataRd.archStr );
	}
	
	return 0;
}


// ------------------------------------------------------
// load_conf
// ------------------------------------------------------
/* Recibe un nombre de archivo (string), abre y devuelve estructura.
 *
 * # Archivo (formato) #
 * PORT=num
 * BACKLOG=num
 * ARCHIVOS=arch01.txt,arch02.txt,…
 */
Config_Data_t load_conf( const char *const fileName ) {
	int					fdGlobalFile;
	const char			keywords[3][10] = { "PORT=", "BACKLOG=", "ARCHIVOS=" };
	const char			archSep = ',';
	int					nBytesRead;
	char					buf[ARCH_LIST_SIZE];	// Buffer para leer archivo.
	int					bufCursor;
	int					cursorArchStr;
	int					numberArch;		// N° de archivos creados.
	Config_Data_t		outputData;		// Estructura con datos a enviar.
	memset( (void *) &outputData, 0, sizeof (Config_Data_t) );	
	// Pone todo en 0 en caso de que no se lea nada.
	
	
	if ( fileName == NULL ) {
		printf( "\n[ SIN INPUT: NO LEYÓ NADA. ]\n\n" );
	} else {
		fdGlobalFile = open( fileName, O_RDONLY );
		
		if ( fdGlobalFile < 1 ) {
			printf( "\n[ ARCHIVO INVÁLIDO: NO LEYÓ NADA. ]\n\n" );
		} else {
			for ( int cursor = 0; cursor < 3; cursor++ ) {
				bufCursor = -1;
				
				// Llega a la palabra clave.
				lseek( fdGlobalFile, strlen( keywords[cursor] ), SEEK_CUR );
				
				// # Lectura de datos útiles #
				do {
					bufCursor++;	// Empieza en -1, pasa a 0.
					nBytesRead = read( fdGlobalFile, buf + bufCursor, sizeof (char) );
				} while ( (buf[bufCursor] != '\n') && (nBytesRead != 0) );
				buf[bufCursor] = '\0';
				
				printf( "[ Leído: %s ]\n", buf );
				
				switch ( cursor ) {
					case 0:	// PORT
						outputData.port = atoi( buf );
						printf( "[ Puerto: %d ]\n\n", outputData.port );
					break;
					
					case 1:	// BACKLOG
						outputData.backLog = atoi( buf );
						printf( "[ Backlog: %d ]\n\n", outputData.backLog );
					break;
					
					case 2:	// ARCHIVOS
						// # Separación en array de varios archivos (por ',') #
						bufCursor = 0;
						cursorArchStr = 0;
						numberArch = 1;
						
						outputData.archStr = (char **) malloc( numberArch * sizeof (char *) );	// Inicializa el array.
						outputData.archStr[0] = (char *) malloc( ARCH_LIST_SIZE * sizeof (char) );  // Inicializa el primer string.
						
						do {
							if ( buf[bufCursor] != archSep ) {	// Delimitador entre archivos.
								// Copia caracter a caracter.
								outputData.archStr[numberArch - 1][cursorArchStr] = buf[bufCursor];
								cursorArchStr++;
								
							} else {		// Se detectó coincidencia.
								outputData.archStr[numberArch - 1][cursorArchStr] = '\0';
								cursorArchStr = 0;	// Vuelve al inicio.
								
								printf( "* Archivo N° %d:   %s\n", numberArch, outputData.archStr[numberArch - 1] );
								
								numberArch++;		// Pasa al siguiente string (un archivo más).

								outputData.archStr = (char **) realloc( outputData.archStr, numberArch * sizeof (char *) );
								outputData.archStr[numberArch - 1] = (char *) malloc( ARCH_LIST_SIZE * sizeof (char) );  
							}
							
							bufCursor++;
						} while ( buf[bufCursor] != '\0' );
						printf( "* Archivo N° %d:   %s\n", numberArch, outputData.archStr[numberArch - 1] );
						
						numberArch++;
						outputData.archStr = (char **) realloc( outputData.archStr, numberArch * sizeof (char *) );
						outputData.archStr[numberArch - 1] = NULL;	// Último apunta a NULL por seguridad.
					break;
				}	// Switch...
			}	// End FOR.
			
			close( fdGlobalFile );
		}	// Archivo válido.
	}	// Nombre de archivo no vacío.
	
	
	return outputData;
}

