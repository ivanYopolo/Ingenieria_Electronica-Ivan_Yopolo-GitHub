#ifndef encriptar
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <time.h>
	
	#define tamStr 50
	
	// #include "encriptar.h"
	
	int desplazar_letras (const char *, char *);
	
	void desencriptar_texto(const char *, char *, const int);

	void encriptar_numeros(const char *, char *);
	
	void desencriptar_numero(const char *, char *);

	int es_encriptable(const char *);
#endif