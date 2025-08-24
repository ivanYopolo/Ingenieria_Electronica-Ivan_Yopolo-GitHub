#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct_Alum.h"

// #define tamString 40

// struct Alumno{
	// char Nombre[tamString];
	// char Apellido[tamString];
	// int Edad;
	// double Legajo;
	// int P1;
	// int P2;
	// int Final;
// };


void Print_Alumno(struct Alumno *alum){
	printf("\nNombre:         %s", alum->Nombre);
	printf("\nApellido:       %s", alum->Apellido);
	printf("\nEdad:           %d", alum->Edad);
	printf("\nLegajo:         %.6lf", alum->Legajo);  // 6 decimales después del punto.
	printf("\nNota Parcial 1: %d", alum->P1);
	printf("\nNota Parcial 2: %d", alum->P2);
	printf("\nNota Final:     %d\n\n", alum->Final);
}