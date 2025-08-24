// Hacer un programa que devuelva el caracter
// inicial de un string usando uniones.

#include "FirstChar.h"

char FirstChar(char *string){
	union letters Mensj;
	strncpy(Mensj.mensaje, string, strlen(string));
	
	
	printf("Mensaje: \t\t%s\n", string);
	printf("1° caracter: \t\t%c\n", Mensj.letra);
	
	return Mensj.letra;
}
