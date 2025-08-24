
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

#include "rocketCalc.h"

int main(){
	
	int numRockets = 0; // N° de cohetes a lanzar.
	int minVel = 0;		// Velocidad mínima "V0".
	int minH = 0;		// Altura mínima "h0".
	int currentRocket = 1; // Cohete actual.
	int rocketSucc = 0;	// Cantidad de cohetes exitosos
	
	system("clear");
	
	printf(
	"\n### Bienvenida/o al simulador de lanzamientos de cohetes espaciales ###\n\
	\nPor favor, ingrese los datos correspondientes:\n");
	
	printf(
	"\nNúmero de cohetes a lanzar: ");
	scanf("%d", &numRockets);
	
	printf(
	"\nVelocidad mínima objetivo [m/s]:  ");
	scanf("%d", &minVel);
	
	printf(
	"\nAltura mínima objetivo [m]:       ");
	scanf("%d", &minH);
	
	for(currentRocket = 1; currentRocket <= numRockets; currentRocket++){
		// Pasar un struct temporal que se sobreescribe por cohete,
		// que se usa principalmente para mostrar datos.
		struct Rocket rocketTemp;	// Se borra cada vez que vuelve a empezar el for().
		
		rocketTemp.Current = currentRocket;
		
		// Función que testee y calcule lo pedido por cada cohete.
		rocketCalc(minVel, minH, currentRocket, &rocketSucc, &rocketTemp);
	}
	
	// Mostrar datos finales (como porcentaje de éxito):
	showResults(numRockets, rocketSucc);
	return 1;
}

/*
	Como linkear + compilar:
	
	gcc -Wall main.c rocketCalc.c structRocket.h -lm -o simulacionCohete
*/