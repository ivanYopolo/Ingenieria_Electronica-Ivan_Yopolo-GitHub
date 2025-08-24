#include "cambleCase.h"

/*
	1) Pasar a minus.
	2) Poner Mayus.
		a) Remover caracteres distintos de letras.
	3) Eliminar espacios.
*/


void cambleCase(char *str){
	int i = 0;
	// 1) Mayus.
	// 2) Minus.
	
	// Se pone todo a minúscula.
	for(i = 0; i < strlen(str); i++){
		if(isalpha(str[i]) && str[i] <= 'a')
			lowCase(str, i);
		
		if(!isalpha(str[i]))
			rmvNLet(str, i);
	}
	
	// Se ponen mayúsculas dsp de los espacios.
	// Se eliminan caraterres distintos de las letras.
	// Se eliminan espacios
	for(i = 0; i < strlen(str); i++){
		// Primera en mayúscula.
		if(i == 0){
			upCase(str, i);
			rmvSpace(str, i);
		}
		
		// Si se encuentra un espacio:
		if(str[i] == ' '){
			// Se cambia la siguiente letra por mayúscula.
			upCase(str, i+1);
			// Se elimina el espacio.
			rmvSpace(str, i);
		}
	}
}


// Se cambia la siguiente letra por mayúscula.
void upCase(char *str, int i){
	if(i < strlen(str) && str[i] >= 'a'){
		str[i] -= ('a' - 'A');	// Le resta el espacio entre mayus y minus (ASCII).
	}
}


// Se elimina el espacio.
void rmvSpace(char *str, int i){	
	// Usar "strcat()" o "strncpy()"
	// Concatenar el pointer con índice DEL espacio con el pointer CON siguiente índice.
	if(i < strlen(str))
		// Índice c/ espacio, siguiente al índice c/ espacio.
		strcpy(str+i, str+i+1);
}


void rmvNLet(char *str, int i){
	str[i] = ' ';	// Le escribe un espacio.
}


void lowCase(char *str, int i){
	str[i] += ('a'-'A');	// Le suma el espacio entre mayus y minus (ASCII).
}


