/*
	Escribir una función que reciba como argumentos dos punteros a char “t” y “s”,
	que apunta cada uno a una secuencia de bytes terminados en '/0', y realice la
	concatenación de la secuencia “s” a continuación de la secuencia “t”, terminando
	la secuencia de bytes resultante con el caracter '\0' (Función strcat() de la
	biblioteca <string.h>).
	
	El prototipo de la función pedida es:
	
	void my_strcat (char *t, const char *s) ;
*/

#include "my_strcat.h"

void writeStr(char *string);

int main(){
	char strS[tamStr];
	char strT[tamStr];
	
	system("clear");
	
	printf("\nIngrese el mensaje S:\n\t\t\t");
	writeStr(strS);
	
	printf("\nIngrese el mensaje T:\n\t\t\t");
	writeStr(strT);
	
	my_strcat(strT, strS); // Concatena "s" con "t".
	
	printf(
	"\nMensaje original:\t\t%s\
	\nMensaje concatenado:\t\t%s\n", strS, strT);
	
	return 1;
}


void writeStr(char *string){
	if(fgets(string, tamStr, stdin) == NULL);	// ERROR
	
	if(string[strlen(string) - 1] != '\n'){
		int ch = 0;
		while((ch = getchar()) != '\n' && ch != EOF);
	}
	if(string[strlen(string) - 1] == '\n')
		string[strlen(string) - 1] = '\0';
}

// Compilar + linkear:
// gcc -Wall main.c my_strcat.c -o 4.07