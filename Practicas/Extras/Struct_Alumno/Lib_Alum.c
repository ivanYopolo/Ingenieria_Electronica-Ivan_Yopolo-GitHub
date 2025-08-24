#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct_Alum.h"


void Init_Alumno(struct Alumno *alum){
	system("clear");
	int aux;
	int i = 0;
	
	printf("\nIngrese los datos del alumno:\n");
	
	printf("\nNombre: ");
	// Código para poder obtener el array y evitar doble enter:
	if(fgets(alum->Nombre, tamString, stdin) == NULL){
		printf("\n# ERROR #\n");
	    // Error.
	}
	if(alum->Nombre[strlen(alum->Nombre)-1] != '\n' && fgets(alum->Nombre, tamString, stdin) != NULL){
		/* buffer wasn't big enough */
		while((i = getchar()) != '\n' && i != EOF); // Flush the input buffer
		/* now print an error message or something, */
		/* and ask the user to try again with shorter input */
	}
	
	// Llega al '\n' (salto de línea) y lo reemplaza por el NULL.
	for(i = 0; alum->Nombre[i] != '\n' && alum->Nombre[i] != EOF; i++);
	alum->Nombre[i] = '\0';
	
	printf("\nApellido: ");
	// Código para poder obtener el array y evitar doble enter:
	if(fgets(alum->Apellido, tamString, stdin) == NULL){
		printf("\n# ERROR #\n");
	    // Error.
	}
	if(alum->Apellido[strlen(alum->Apellido)-1] != '\n'){
		/* buffer wasn't big enough */
		while((i = getchar()) != '\n' && i != EOF); // Flush the input buffer
		/* now print an error message or something, */
		/* and ask the user to try again with shorter input */
	}
	
	
	// Llega al '\n' (salto de línea) y lo reemplaza por el NULL.
	for(i = 0; alum->Apellido[i] != '\n' && alum->Apellido[i] != EOF; i++);
	alum->Apellido[i] = '\0';
	
	printf("\nEdad: ");
	scanf("%d", &(alum->Edad));
	do{}while((aux = getchar()) != '\n' && aux != EOF);
	
	printf("\nLegajo: ");
	scanf("%lf",&(alum->Legajo));
	do{}while((aux = getchar()) != '\n' && aux != EOF);
	
	printf("\nNota del 1° parcial: ");
	scanf("%d",&(alum->P1));
	do{}while((aux = getchar()) != '\n' && aux != EOF);
	
	printf("\nNota del 2° parcial: ");
	scanf("%d",&(alum->P2));
	do{}while((aux = getchar()) != '\n' && aux != EOF);
	
	printf("\nNota final: ");
	scanf("%d",&(alum->Final));
	do{}while((aux = getchar()) != '\n' && aux != EOF);
}