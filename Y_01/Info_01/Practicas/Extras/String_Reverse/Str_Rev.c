#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMString 50

void strRev(char *);


int main(){
	int i = 0;
	system("clear");
	
	char string[TAMString];
	
	// Inicializar el string:
	printf("\nIngrese el Mensaje: \n");
	
	// Código para poder obtener el array y evitar doble enter:
	if(fgets(string, TAMString, stdin) == NULL){
		printf("\n# ERROR #\n");
	    // Error.
	}
	if(string[strlen(string)-1] != '\n' && fgets(string, TAMString, stdin) != NULL){
		/* buffer wasn't big enough */
		while((i = getchar()) != '\n' && i != EOF); // Flush the input buffer
		/* now print an error message or something, */
		/* and ask the user to try again with shorter input */
	}
	
	// Llega al '\n' (salto de línea) y lo reemplaza por el NULL.
	for(i = 0; string[i] != '\n' && string[i] != EOF; i++);
	//Pone el '\n' como '\0'.
	string[i] = '\0';
	
	
	printf("\nTamaño String: %ld", strlen(string));
	
	strRev(string);
	printf("\nEl string resultó como: %s\n\n", string);
	
	return 0;
}


void strRev(char *stringInput){
	int j = 0;
	char aux = 0;
	int tamString = strlen(stringInput) - 1;
	
	for(j = 0; j < tamString; j++, tamString--){
		aux = stringInput[j];
		stringInput[j] = stringInput[tamString];
		stringInput[tamString] = aux;
	}
}

