/*
	Realizar un programa que reciba un número en FLOAT como argumento (del main) y lo imprime en binario.
	Asumir Ca2 para la parte entera, y una magnitud para la parte decimal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void floatBin( float numFloat, unsigned char numBin[] );

void Ca2( unsigned char arrBin[], const float numFloat );


int main( int argc, char *argv[] ){
	
	// system( "clear" );
	
	if( argc < 2 ){
		
		printf( "### ERROR: Falta argumento de número FLOTANTE. ###\n" );
	}else{
		
		unsigned char numBin[ 100 ];	// Numero a guardar en binario (string).
		float numFloat = atof( argv[ 1 ] );	// Guarda el flotante leído como input.
		// Mostrar en binario CON COMA.
		
		printf( "\nEl número flotante es: \t\t%f\n", numFloat );
		
		// printf( "\nMódulo con negativos?\t\t%d\n\n", (- 8) % 3 );	// FUNCIONA.
		
		floatBin( numFloat, numBin );	// Guarda el valor convertido a binario.
		
		printf( "\nEl valor en binario es:\t\t%s\n\n", numBin );
	}
	
	return 1;
}

/*
	1) A la parte entera del flotante, aplicar método de las divisiones.
	2) Al resto obtenido, aplicarle Ca2.
	3) Agregarle el punto "." al final para indicar inicio de parte decimal.
	3) A la parte decimal del flotante, aplicar método de las divisiones común.
*/
void floatBin( float numFloat, unsigned char numBin[] ){
	// int cocienteEntero = (int) numFloat;	// N° a ser divido (PARTE ENTERA).
	// float multiploDecimal = numFloat - cocienteEntero;	// N° a ser multiplicado (PARTE DECIMAL).
	int cocienteEntero = 0;	// N° a ser divido (PARTE ENTERA).
	float multiploDecimal = 0;	// N° a ser multiplicado (PARTE DECIMAL).
	// int i = 0, l = 0;		// Recorre array "numBin".
	int i = 1, l = 0;		// Recorre array "numBin".
	
	
	
	if( numFloat == 0 ){
		
		numBin[ 0 ] = '0'; 
		numBin[ 1 ] = '\0';
	}else{
		
		// PARTE ENTERA.
		if( numFloat < 0 ){
		
			// numBin[ 0 ] = '1';	// Pone bit de signo.
		
			cocienteEntero = (int) ( (- 1) * numFloat );	
			
			multiploDecimal = ( (- 1) * numFloat ) - cocienteEntero;	
		}else{
			
			// numBin[ 0 ] = '0';	// Pone bit de signo.
			
			cocienteEntero = (int) numFloat;	
			
			multiploDecimal = numFloat - (float) cocienteEntero;	
		}
		
		if( cocienteEntero == 0 ){
			
			numBin[ 1 ] = '0';
			
			i++;	// Para no sobreescribir el 0 de "parte entera".
		}
		
		while( cocienteEntero != 0 ){	// Método de las divisiones.
		
			numBin[ i ] = cocienteEntero % 2 + '0';
			
			cocienteEntero = cocienteEntero / 2;
			
			i++;
		}	// Termina de guardar los restos (orden inverso).
		
		numBin[ i ] = '.';	// "i" se pasa en la última iteración, ahí guarda el PUNTO DECIMAL.
		
		
		// ###########
		// APLICAR CA2.
		// ###########
		
		Ca2( numBin, numFloat );
		
		if( numBin[ i ] != '.' ){
			
			i++;
		}
		
		// Da vuelta el string "numBin" (el resto).
		// No pasa por pos. 0 (omite el bit de signo).
		for( int j = 1, h = i - 1; j < h; j++, h-- ){
			
			unsigned char temp = numBin[ j ];
			
			numBin[ j ] = numBin[ h ];
			
			numBin[ h ] = temp;
		}
		
		// PARTE DECIMAL.
		/*
			Agarra 8 bits.
			
			Guarda la parte decimal en "multiploDecimal".
			
			Si se pasa del 1: 
				
				Le resta 1 (toma parte decimal).
			
			Multiplica "multiploDecimal" por 2. Registra resultado en "numBin" redondeado, en caracter. 
			Depende si fue mayor o menor que 1 registra o no un 0 o 1.
		*/
		
		// l = 0;
		l = 1;
		// while( ( multiploDecimal != 1 ) && ( l <= 8 ) ){	// Método de las MULTIPLICACIONES.
		while( ( l <= 8 ) ){	// Método de las MULTIPLICACIONES.
			
			if( multiploDecimal != 1 ){	
				
				if( multiploDecimal > 1 ){	// Si se pasa de "rango", vuelve a los decimales.
					
					// multiploDecimal = ( int ) multiploDecimal;
					multiploDecimal--;	// Le resta 1.
				}

				multiploDecimal = multiploDecimal * 2;	// Multiplica por 2.
				numBin[ i + l ] = (int)( multiploDecimal ) + '0';	// Guarda el número ya multiplicado como caracter (0 si es menor a 1; 1 si es mayor o igual a 1).
			}else{
				// Si llega a terminar de antemano, completa con 0s.
				numBin[ i + l ] = '0';
			}
			
			l++;			
		}

		
		numBin[ i + l ] = '\0';
		
	}
	
	return;
}


void Ca2( unsigned char arrBin[], const float numFloat ){
	int tamEnt = 0, posicion = 0;
	
	// # Ca1 #
	// Escanear desde posición 0 hasta el '.'.
	// Intercambiar cada 1 por 0 y viceversa.
	for( tamEnt = 0; arrBin[ tamEnt ] != '.'; tamEnt++ ){
		
		switch( arrBin[ tamEnt ] ){
			
			case '0':
				arrBin[ tamEnt ] = '1';
				break;
				
			case '1':
				arrBin[ tamEnt ] = '0';
				break;
		}
	}
	
	// tamEnt--;	// Llega al anterior del '.'.
	
	// # Sumar 1 #
	/*
		Variable "posicion" entera.
		
		Contar hasta el '.' y guardar el número de la posición anterior en "posicion".
	
		Si el dígito en "posicion" es '0':

			Reemplazarlo por '1'.
		
		Sinó:
		
			Reemplazarlo por un '0'.
			
			Mientras el dígito en "posicion" sea '1' y "posicion" sea mayor o igual que 0:
				
				Reemplazar por '0'.
				
				Restar "posicion" en 1.
				
	*/
	
	
	// for( tamEnt = 0; arrBin[ tamEnt ] != '.'; tamEnt ++ ){  }	// Contó HASTA el '.'.
	
	if( arrBin[ 0 ] == '0' ){
		
		arrBin[ 0 ] = '1';	// Suma 1.
	}else{
		
		for( posicion = 0; ( arrBin[ posicion ] == '1' ) && ( posicion < tamEnt ); posicion++ ){
			// Puede sobreescribir el punto decimal.
			arrBin[ posicion ] = '0';
		}
		
		arrBin[ posicion ] = '1';		

		if( arrBin[ posicion ] == '.' ){
			// Si genera un nuevo dígito, desplaza el punto decimal.
			arrBin[ posicion + 1 ] = '.';

			arrBin[ posicion + 2 ] = '\0';
		}else{
		
			arrBin[ tamEnt + 1 ] = '\0';
		}
	}
	
	
	// # Bit de signo #
	
	// Primero copia el string entero 1 a la derecha para poner el bit sin problemas.
	strncpy( arrBin, arrBin + 1, strlen( arrBin ) );

	if( numFloat > 0 ){
		
		arrBin[ 0 ] = '0';
	}else{
		
		arrBin[ 0 ] = '1';
	}
}


