#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct_Alum.h"
#include "Lib_Alum.h"
#include "Print_Alum.h"


int main(){
	struct Alumno alumno1;
	
	// Inicializa los valores del struct:
	Init_Alumno(&alumno1);
	
	// Los imprime en pantalla:
	Print_Alumno(&alumno1);
	
	return 0;
}

