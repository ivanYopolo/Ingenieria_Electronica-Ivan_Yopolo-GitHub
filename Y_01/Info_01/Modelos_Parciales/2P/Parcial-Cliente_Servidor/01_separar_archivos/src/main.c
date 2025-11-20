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
		printf( "* ARCHIVOS: %s\n", dataRd.archStr );
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
Config_Data_t load_conf( char *fileName ) {
	int					fdGlobalFile = 0;
	int					nBytesRead = 0;
	char					keywords[3][10] = { "PORT=", "BACKLOG=", "ARCHIVOS=" };
	char					buf[ARCH_STR_SIZE];
	int					bufCursor = -1;
	Config_Data_t		outputData;
	
	
	memset( (void *) &outputData, 0, sizeof (Config_Data_t) );
	
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
				// nBytesRead = read( fdGlobalFile, buf, strlen( keywords[cursor] ) );	
				
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
						strncpy( outputData.archStr, buf, ARCH_STR_SIZE );
						printf( "[ Archivos: %s ]\n\n", outputData.archStr );
					break;
				}
			}	// End FOR.
			
			close( fdGlobalFile );
		}	// Archivo válido.
	}	// Nombre de archivo no vacío.
	
	
	return outputData;
}

