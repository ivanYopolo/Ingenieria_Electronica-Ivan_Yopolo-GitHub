#ifndef validate_string
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	// Valida o no string como dirección IP.
	int stringIP(char *string);

	// Valida o no string como E-Mail.
	int stringMail(char *string);

	// Valida o no string como Tarjeta de Crédito.
	int stringCreditCard(char *string);
	
	// En argumento de función hay puntero a función, con string en el argumento de esta última.
	void validate_string(char *, int (*)(char *));
#endif
