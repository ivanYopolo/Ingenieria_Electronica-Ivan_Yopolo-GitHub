#include "../inc/includes.h"


// ------------------------------------------------------
// main
// ------------------------------------------------------
int main( int argc, char *argv[] ) {
	
	if ( argc != 2 ) {
		printf( "\n[ USO: prog.bin archivo_01.dat ]\n\n" );
		exit(1);
	} else {
		load_conf( argv[1] );
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
	char					buf[ARCHSTR_SIZE];
	int					bufCursor = -1;
	Config_Data_t		outputData;
	
	
	memset( (void *) &outputData, 0, sizeof (Config_Data_t) );
	
	if ( fileName == NULL ) {
		printf( "\n[ VACÍO: NO LEYÓ NADA. ]\n\n" );
	} else {
		fdGlobalFile = open( fileName );
		
		if ( fdGlobalFile < 1 ) {
			printf( "\n[ ARCHIVO INVÁLIDO: NO LEYÓ NADA. ]\n\n" );
		} else {
			for ( int cursor = 0; cursor < 3; cursor++ ) {
				// Llega a la palabra clave.
				lseek( fdGlobalFile, strlen( keywords[cursor] ), SEEK_CUR );
				// nBytesRead = read( fdGlobalFile, buf, strlen( keywords[cursor] ) );	
				
				// # Lectura de datos útiles #
				do {
					bufCursor++;	// Empieza en -1, pasa a 0.
					nBytesRead = read( fdGlobalFile, buf[bufCursor], sizeof (char) );
				} while ( (buf[bufCursor] != '\n') && (nBytesRead != 0) );
				buf[bufCursor] = '\0';
				
				switch ( cursor ) {
					case 0:	// PORT
						outputData.port = atoi( buf + strlen( keywords[cursor] ) );
					break;
					
					case 1:	// BACKLOG
						outputData.backLog = atoi( buf + strlen( keywords[cursor] ) );
					break;
					
					case 2:	// ARCHIVOS
						strncpy( outputData.archStrm, buf + strlen( keywords[cursor] ), ARCHSTR_SIZE );
					break;
				}
			}	// End FOR.
		}
	}
	
	return outputData;
}


// ------------------------------------------------------
// conexion_tcp
// ------------------------------------------------------
/* 
 */
void conexion_tcp() {
	
}
