/*
Función análoga a la anterior para desencriptar el número.
*/

#include "desplazar_letras.h"

void desencriptar_numero(char *mensajeEncrNum, char *mensajeDesENum){
	strcpy(mensajeDesENum, mensajeEncrNum);
	
	for(int i = 0; i < strlen(mensajeEncrNum); i++){
		switch(mensajeEncrNum[i]){
			case '1':
				mensajeDesENum[i] = '1';
				break;
		}
	}
}

