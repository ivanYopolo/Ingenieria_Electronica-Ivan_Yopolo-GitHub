/*
*
*  Infomática I
*  Año: 2025
*  Nombre: Iván Yopolo
*  TP Nº 02 - Simulación interactiva de lanzamientos de cohetes espaciales  
*
*  Observaciones: ...
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structRocket.h"
#include "rocketCalc.h"

// typedef char bool;

int main(){
	struct Rocket rocketTemp;
	
	int numRockets = 0; // N° de cohetes a lanzar.
	int minVel = 0;		// Velocidad mínima "V0".
	int minH = 0;		// Altura mínima "h0".
	int currentRocket = 1; // Cohete actual.
	int rocketSucc = 0;	// Cantidad de cohetes exitosos
	
	printf(
	"\n### Bienvenida/o al simulador de lanzamientos de cohetes espaciales ###\n\
	\nPor favor, ingrese los datos correspondientes:\n");
	
	printf(
	"\nNúmero de cohetes a lanzar: ");
	scanf("%d", &numRockets);
	
	printf(
	"\nVelocidad mínima objetivo:  ");
	scanf("%d", &minVel);
	
	printf(
	"\nAltura mínima objetivo:     ");
	scanf("%d", &minH);
	
	for(currentRocket = 1; currentRocket <= numRockets; currentRocket++){
		// Pasar un struct temporal que se sobreescribe por cohete,
		// que se usa principalmente para mostrar datos.
		
		// Función que testee y calcule por cada cohete.
		rocketCalc(minVel, minH, currentRocket, &rocketSucc, &rocketTemp);
	}
	
	// Mostrar datos finales (como porcentaje de éxito):
	showResults(numRockets, rocketSucc);
	return 1;
}

/*
	Como linkear + compilar:
	
	gcc main.c rocketCalc.c structRocket.h -lm -o simulacionCohete
*/