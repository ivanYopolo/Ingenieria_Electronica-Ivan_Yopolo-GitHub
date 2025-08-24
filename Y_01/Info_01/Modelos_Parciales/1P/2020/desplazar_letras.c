/*
Función que debe generar un desplazamiento alfabético de cada una de las letras del
string recibido como argumento, una cantidad aleatoria de posiciones (entre 1 y 25). En
caso de sobrepasar la ‘Z’, se deberá continuar con la ‘A’. Los números y espacios deben
permanecer invariables. La función debe retornar la cantidad de posiciones que se han
desplazado los caracteres.

Ej: “HOLA 54”. Si el numero aleatorio fue 3, debería quedar “KROD 54”.
*/

#include "desplazar_letras.h"

int desplazar_letras(char *strI, char *strO){
	int desplazamiento = 0;
	// char newChar = 0;
	srand(time(NULL));
	// Genera N° random (1~24).
	desplazamiento = rand() % 24 + 1; 
	
	// Se copia para poner el '\0' correctamente.
	strcpy(strO, strI);
	
	for(int i = 0; i < strlen(strI); i++){
		if(isalpha(strI[i])){
			// Verificar que no se pase del 'Z'.
			if((strI[i] + desplazamiento) > 'Z'){
				// Se le suma el "resto" o "exceso", empezando desde 'A'.
				strO[i] = 'A' + (strI[i] + desplazamiento - 'Z');
			}else{
				strO[i] = strI[i] + desplazamiento;
			}
		}
	}
	return desplazamiento;
}

