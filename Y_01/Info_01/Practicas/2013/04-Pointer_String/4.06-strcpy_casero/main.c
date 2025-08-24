/*
	Escribir una función que reciba un puntero a caracter "s" y un puntero a caracter
	"t", y copie la “s” en “t”, terminando la cadena con el caracter '\0' (Función
	strcpy () de la biblioteca <string.h>). 
	
	El prototipo de la función pedida es:
	
	void my_strcpy (char *t, const char *s);
*/

#include "my_strcpy.h"

void writeStr(char *string);

int main(){
	char strS[tamStr];	// String con contenido.
	char strT[tamStr];	// String donde copiar.
	
	system("clear");
	
	printf("\nIngrese el mensaje:\n\t\t\t");
	writeStr(strS);
	
	my_strcpy(strT, strS); // Copia "s" en "t".
	
	printf(
	"\nMensaje original:\t\t%s\
	\nMensaje copiado:\t\t%s\n", strS, strT);
	
	return 1;
}


void writeStr(char *string){
	if(fgets(string, tamStr, stdin) == NULL);	// ERROR
	
	if(string[strlen(string) - 1] != '\n'){
		int ch = 0;
		while((ch = getchar()) != '\n' && ch != EOF);
	}
	if(string[strlen(string) - 1] == '\n')
		string[strlen(string) - 1] = 0;
}

// Compilar + linkear:
// gcc -Wall main.c my_strcpy.c -o 4.06