/*
a)Escribir 3 funciones que, recibiendo una cadena de caracteres como
argumento, permitan determinar si la cadena es válida como dirección IP, como
dirección de correo electrónico, y como número de tarjeta de crédito.

b) Escribir una función denominada validate_string() que recibiendo una cadena
de caracteres y una función de validación (pasada por puntero), determine si la
cadena es válida conforme al criterio de validación indicado, retornando en
consecuencia true o false por su nombre.
*/

#include "validate_string.h"

// Array de 3 function-pointers según selección.
// int (*validations[3])(char *string) = {stringIP, stringMail, stringCreditCard};


// Retorna "int" según si es válido (1) o inválido (-1).
int validate_string(char *string, int (*validation)(char *string)){
/*
	Pasar el string a una función, retornar TRUE o FALSE dependiendo si es
	válido o no.
*/
	
	
}


