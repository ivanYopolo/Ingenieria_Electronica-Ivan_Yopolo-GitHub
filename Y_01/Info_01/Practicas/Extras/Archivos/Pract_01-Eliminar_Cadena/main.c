/*
	Abrir un archivo y copiarlo en otro con la cadena (sin comillas):
	"nosuid,"
	eliminada. El resto del archivo se deja igual.
	Después, se imprime en pantalla.
	Trabajar byte a byte.
    
    # CORRECCIÓN FINAL #
    El problema principal fue que, al terminar de leer una coincidencia
    exitosa, el cursor en el archivo "input" quedaba adelantado 1
    posición, por lo que tenía que volver para atrás. Sinó, se comía
    el caracter siguiente.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define TAM 1
#define B_READ 1    // Bytes a leer por ciclo.

int deteccionString( char buf[], const char msg[], const int fd1, const int fd2 );

int main(){
	int cant = 0, out;
	char buf[ TAM ];
	const char msg[ 8 ] = "nosuid,";
    const int fdI = open( "textoInput.txt", O_RDONLY );
	const int fdO = open( "textoOutput.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR );
	
	do{
		cant = read( fdI, ( void * ) buf, B_READ );	// Bytes leídos.
		
		if( cant > 0 ){	 
			if( *buf != msg[ 0 ] ){
				// Se copia tal cual, byte a byte, entre archivos.
				out = write( fdO, ( const void * ) buf, B_READ );
			}else{	// Se detectó 'n'.
				deteccionString( buf, msg, fdI, fdO );
			}   // Se terminó de decidir si era positivo o falso positivo.
		}
	}while( cant > 0 && out > 0);
	
	close( fdI );
	close( fdO );
}


/*
Se setea una "cursor1".
WHILE mientras "buf" sea igual al caracter de "msg" en la posicion "contador1":
	Incrementa "cursor1" en 1.
	Lee archivo de entrada con "buf" (solamente cuenta, no hace nada).
IF "cursor1" es MENOR a la longitud del string "msg" (sin contar '\0'):
	Mover cursor con un offset (negativo) de "-cursor1".
	FOR un nuevo contador "cursor2" en 0 sea distinto de "cursor1":
		Escribe en el archivo de salida lo leído por "buf".
		Lee un byte en "buf".
ELSE (ES string válido):
	Escribe "buf" en el archivo de salida "fd2".
FIN.
*/

int deteccionString( char buf[], const char msg[], const int fd1, const int fd2 ){
	int cant = 1, out = 1;
	int cursor1 = 0; // Para moverse por el texto.
	
    while( ( *buf == msg[ cursor1 ] ) && ( msg[ cursor1 ] != '\0' ) && ( cant > 0 ) ){
        cursor1++;  // Entra con una detección 'n'.
        cant = read( fd1, ( void * ) buf, B_READ );	// Bytes leídos.
    }
    
    if( msg[ cursor1 ] != '\0' ){   // Falso positivo.
        // Mover cursor con un offset de "cursor1" (negativo -> va a la izquierda).
        lseek( fd1, -cursor1 - B_READ, SEEK_CUR );
        
        printf( "# Falso positivo: cursor1 = %d #\n\n", cursor1 );
        
        do{ // Escribe desde el falso positivo hasta el actual.
            cant = read( fd1, ( void * ) buf, B_READ );	// Bytes leídos.
            out = write( fd2, ( const void * ) buf, B_READ );
            printf( "# Caracter \'%c\' en cursor1 = %d #\n\n", *buf, cursor1 );
            cursor1--;
        }while( ( cursor1 != 0 ) && ( cant > 0 ) && ( out > 0 ) );
    }else{
        if( msg[ cursor1 ] == '\0' ){	// Detectó el string igual.
            printf( "[ COINCIDENCIA ]\n\n" );
            lseek( fd1, -B_READ, SEEK_CUR ); // Llegó al final y se pasó por 1 caracter.
            cursor1 = 0;
        }
    }
		
	return 1;
}

