// gcc -Wall 1P_2020.c desplazar_letras.c desencriptar_numeros.c encriptar_numeros.c desencriptar_texto.c es_encriptable.c -o main

#include "desplazar_letras.h"
#define tamStr 50

int main(){
	char mensaje[tamStr];
	char mensajeDesp[tamStr];
	char mensajeDesE[tamStr];
	char mensajeEncrNum[tamStr];
	char mensajeDesENum[tamStr];
	
	
	system("clear");
	
	
	printf("\nIngrese el mensaje:\t\t\t\t");
	// fgets(mensaje, tamStr, stdin);
	
	// Por si es vacío o tira error (buffer suficiente):
	if(fgets(mensaje, tamStr, stdin) == NULL){
		printf("\n# ERROR #\n");
		// Error.
	}
	if(mensaje[tamStr-1] != '\n'){
	// Buffer chico, fgets() falló en leer la línea entera.
		int ch = 0;
		while((ch = getchar()) != '\n' && ch != EOF); // Flush the input buffer
		// now print an error message or something, 
		// and ask the user to try again with shorter input 
	}
	
	// printf("\nMensaje:\t\t%s\n", mensaje);
	
	int desplazamiento = desplazar_letras(mensaje, mensajeDesp);
	printf(
	"\nEl mensaje encriptado es:\t\t\t%s\
	\nDesplazamiento:\t\t%d\n", mensajeDesp, desplazamiento);
	
	desencriptar_texto(mensajeDesp, mensajeDesE, desplazamiento);
	printf(
	"\nEl mensaje DESencriptado es:\t\t\t%s\
	\nDesplazamiento:\t\t%d\n", mensajeDesE, desplazamiento);
	
	encriptar_numeros(mensajeDesp, mensajeEncrNum);
	printf(
	"\nEl mensaje encriptado (por numeros) es:\t\t%s\n", mensajeEncrNum);
	
	// desencriptar_numero(mensajeEncrNum, mensajeDesENum);
	// printf(
	// "\nEl mensaje DESencriptado (por numeros) es:\t%s\n", mensajeDesENum);
	
	// es_encriptable(mensaje);
	
	// Imprimir el mensaje encriptado.
	// printf("\nEl mensaje encriptado es: \t\t%s\n\n", mensajeEncrNum);
}

