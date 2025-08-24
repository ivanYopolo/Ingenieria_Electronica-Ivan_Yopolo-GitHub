/*
Función que realiza el proceso inverso de la función anterior. Recibe un string y una
cantidad y debe desplazar en sentido inverso las letras para recuperar el texto original
*/
#include "desplazar_letras.h"

void desencriptar_texto(char *strI, char *strO, int desplazamiento){
	// Se copia para poner el '\0' correctamente.
	strcpy(strO, strI);
	
	for(int i = 0; i < strlen(strI); i++){
		if(isalpha(strI[i])){
			// Checkear que la letra MENOS desplazamiento no de menor a 'A':
			if((strI[i] - desplazamiento) < 'A'){
				// Empezar desde 'Z' con el "resto" de strI[i] - 'A' (delta X):
				strO[i] = 'Z' - ('A' - (strI[i] - desplazamiento));
			}else{
				strO[i] = strI[i] - desplazamiento;
			}
		}
	}
}
