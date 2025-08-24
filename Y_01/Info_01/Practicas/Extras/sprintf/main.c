#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int i = 8;
	char string[50] = "Pepe: ";
	
	system("clear");
	
	// Guarda el valor de "i" en "string" como octal (8dec = 10oct).
	sprintf(string, "%o", i);
	
	// Imprime el valor convertido.
	printf("%s\n", string + strlen(string) - 1);
	return 1;
}