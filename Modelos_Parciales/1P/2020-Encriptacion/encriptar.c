/*
Función que debe generar un desplazamiento alfabético de cada una de las letras del
string recibido como argumento, una cantidad aleatoria de posiciones (entre 1 y 25). En
caso de sobrepasar la ‘Z’, se deberá continuar con la ‘A’. Los números y espacios deben
permanecer invariables. La función debe retornar la cantidad de posiciones que se han
desplazado los caracteres.

Ej: “HOLA 54”. Si el numero aleatorio fue 3, debería quedar “KROD 54”.
*/

#include "encriptar.h"

int desplazar_letras( const char *strI, char *strO ){
	int desplazamiento = 0;
	// char newChar = 0;
	srand( time( NULL ) );
	// Genera N° random (1~24).
	desplazamiento = rand() % 24 + 1; 
	
	// Se copia para poner el '\0' correctamente.
	strcpy( strO, strI );
	
	for( int i = 0; i < strlen( strI ); i++ ){
		
		if( isalpha( strI[i] ) ){
			
			// Verificar que no se pase del 'Z'.
			if( ( strI[ i ] + desplazamiento ) > 'Z' ){
				
				// Se le suma el "resto" o "exceso", empezando desde 'A'.
				strO[ i ] = 'A' + ( strI[ i ] + desplazamiento - 'Z' );
			}else{
				
				strO[ i ] = strI[ i ] + desplazamiento;
			}
		}
	}
	return desplazamiento;
}



/*
Función que realiza el proceso inverso de la función anterior. Recibe un string y una
cantidad y debe desplazar en sentido inverso las letras para recuperar el texto original
*/

void desencriptar_texto( const char *strI, char *strO, const int desplazamiento ){
	// Se copia para poner el '\0' correctamente.
	strcpy( strO, strI );
	
	for( int i = 0; i < strlen( strI ); i++ ){ 
	
		if( isalpha( strI[ i ] ) ){
			
			// Checkear que la letra MENOS desplazamiento no de menor a 'A':
			if( ( strI[ i ] - desplazamiento ) < 'A' ){
				
				// Empezar desde 'Z' con el "resto" de strI[i] - 'A' (delta X):
				strO[ i ] = 'Z' - ( 'A' - ( strI[ i ] - desplazamiento ) );
			}else{
				
				strO[ i ] = strI[ i ] - desplazamiento;
			}
		}
	}
}



/*
Para encriptar los números del string el procedimiento será el siguiente: se debe
convertir el número en OCTAL (base 8), para luego reemplazar cada uno de sus 
dígitos por los siguientes caracteres:
0 $
1 %
2 &
3 *
4 @
5 !
6 +
7 =
Adicionalmente, se debe agregar el carácter # tanto al comienzo como al final del numero
encriptado.
*/

void decOct( char strO[] );	

void encriptar_numeros( const char *strI, char *strO ){
	// int sizeStrO = 0;		// Calcula tamaño del string luego de los cambios.
	
	strncpy( strO, strI, tamStr );	// Copia el string de entrada al de salida.
	
	decOct( strO );		// Agrega los '#' y convierte los números en octal.
	
	
	// /*
	// Calcula el tamaño del string luego de sufrir los cambios.
	for( int i = 0; *( strO + i ) != '\0'; i++ ){
		
		unsigned char caracter = *( strO + i );
		switch( caracter ){
			case '0':
				strO[ i ] = '$';
				break;
				
			case '1':
				strO[ i ] = '%';
				break;
				
			case '2':
				strO[ i ] = '&';
				break;
				
			case '3':
				strO[ i ] = '*';
				break;
				
			case '4':
				strO[ i ] = '@';
				break;
				
			case '5':
				strO[ i ] = '!';
				break;
				
			case '6':
				strO[ i ] = '+';
				break;
				
			case '7':
				strO[ i ] = '=';
				break;
		}
	}
	// */
}


void putHashTag( char * );	// Función para poner Hashtags.

void decOct( char *strO ){	
	int posF = 0, posI = 0;	// Cuenta cuantos caracteres numéricos hay.
	int intNum = 0;		// Número entero a extraer del strO.
	int despl = 0;		// Desplazamiento entre iteraciones.
	char scanning = 1;	// Variable para verificar si escanea o no.
	
	do{		// Repetir hasta alcanzar todos los números/secuencias numéricas.
	
		// Cuenta y PARA al llegar a un número (posición inicial).
		// En cada iteración, continúa desde el último número de la secuencia anterior.
		for( posI = despl; strO[ posI ] < '0' || strO[ posI ] > '9'; posI++ );
		
		// Cuenta el tamaño del string numérico (posición final).
		for( posF = posI; strO[ posF ] >= '0' && strO[ posF ] <= '9'; posF++ );
		
		// Condición para salir del bucle (terminó de registrar números).
		if( strO[ posF ] == '\0' ){
			
			scanning = 0;	// Verificar que termine si encuentra el NULO.
		}
		else{
			
			char strTemp[ 100 ];
			strTemp[ 99 ] = '\0';
			
			int diferencia = posF - posI;
			
			// "strtol" o "atoi" para convertir un string a entero.
			// Frena con el primer caracter no válido (espacio, letra si base no es hexa, etc).
			intNum = atoi( strO + posI );
			
			// Pone '#' al inicio.
			putHashTag( strTemp );
			
			// "sprintf" con "%o" (sobreescribe el string, por eso se toma otro índice).
			// El tamaño a imprimir es la diferencia porque:
				// 1) Si fuese 1 caracter la secuencia numérica, la diferencia es 0 y no imprime nada. Se suma 1.
			snprintf( strTemp + 1, diferencia + 10, "%o", intNum );
			
			// Pone '#' al final (ignora el '\0' del "snprintf").
			putHashTag( strTemp + strlen( strTemp ) );
			
			// "strcat" no sobreescribe, concatena.
			// Se pone el resto del string en el temporal:
			// strncat( strTemp, ( strO + posF ), strlen( strO ) );
			strcat( strTemp, ( strO + posF ) );
			
			// printf(
			// "\nstrTemp (octal):\t\t%s\n", strTemp );				
			snprintf( ( strO + posI ), tamStr - 1 - posF, "%s", strTemp );
			
			// Pone el desplazamiento en el siguiente a la terminación de la secuencia numérica.
			// Se suma 2 porque así cuenta desde los caracteres '#', sinó lo registra mal y lo pone 2 veces.
			despl = posF + 2;
		}
		
	}while( scanning ); // Se terminó 1 pasada.
}




void putHashTag( char *string ){
	// Agregar # antes y después del inicio del string numérico.
	strncat( string, "#", 2 );
}