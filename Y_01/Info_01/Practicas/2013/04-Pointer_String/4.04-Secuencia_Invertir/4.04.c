/*
	Escribir una función que reciba como argumento puntero a char, la asuma como
	una secuencia en ASCII terminada en '\0' (NULL) y devuelva la secuencia
	invertida.
*/

#ifndef stdio
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#define strSize 50
#endif


void string_reverse(char *);


void main(){
	system("clear");
	
	char string[strSize];
	
	printf("\n\nInserte mensaje: \n\t\t");
	
	// destination, size, standart_input (keyboard)
	// Por si es vacío o tira error (buffer suficiente):
	if(fgets(string, strSize, stdin) == NULL){
	    printf("\n# ERROR #\n");
	    // Error.
	}
	if(string[strlen(string)-1] != '\n'){
	// Buffer chico, fgets() falló en leer la línea entera.
	    int ch = 0;
	    while((ch = getchar()) != '\n' && ch != EOF); // Flush the input buffer
		//now print an error message or something,
	    // and ask the user to try again with shorter input
	}
	
	string_reverse(string);
	
	printf("\nEl mensaje invertido es: \n\t\t%s\n", string);
}


// Invertir secuencia:
void string_reverse(char *strI){
	char charTemp = 0;	// Temporal para desplazar caracteres.
	int posI = 0, posF = strlen(strI) - 2;	// Variables para escanear por extremos el string. 
	
	// Uno va de izquierda a derecha (posI), y el otro de derecha a izquierda (posF).
	// Como el último es el nulo '\0', empieza uno anterior (tamaño - 2).
	for(posI, posF; (posI <= (strlen(strI) - 2) / 2) && (posF >= (strlen(strI) - 2) / 2); posI++, posF--){
		// 1) Se copia en un caracter temporal el strI[posI].
		// 2) Se reemplaza strI[posI] por strI[posF].
		// 3) Se reemplaza strI[posF] por el caracter temporal.
		
		
		charTemp = strI[posI];
		strI[posI] = strI[posF];
		strI[posF] = charTemp;
	}
	
	strI[strlen(strI) - 1] = '\0';
}
