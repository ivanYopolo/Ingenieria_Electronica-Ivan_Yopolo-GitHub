#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "structRocket.h"
#include "rocketCalc.h"

#define M_PI 3.14159265358979323846	// Pi.
#define grav 9.81	// Gravedad [m/s^2].

typedef char bool;

void rocketCalc(int minVel, int minH, int numRocket, int *rocketSucc, struct Rocket *rockTemp){
	float rendTemp = 0;	// Temporal del rendimiento.
	int flaw = 0;		// Penalización.
	int i = 0;
	
	/*
	// ### CONSTANTES ENTRE INTENTOS ###
	
	// minVel, minH, numRocket
	int rocketMass = 0;	// Masa del cohete [kg].
	// success
	
	
	// ### VARIABLES ENTRE INTENTOS ###
	
	// score
	int randForce = 0;	// Fuerza aleatoria [N].
	int randAngle = 0;	// Ángulo aleatorio [DEG].
	float cosAngleDeg = 0;	// Coseno del ángulo [DEG].
	float sinAngleDeg = 0;	// Seno del ángulo [DEG].
	int velocity = 0;	// Velocidad calculada [m/s].
	int height = 0;		// Altura calculada [m].
	float eC = 0;		// Energía Cinética.
	float eP = 0;		// Energía Potencial.
	float rendTemp = 0;	// Temporal del rendimiento.
	char rendMes[3][12]={
		{'\0'},
		{'\0'},
		{'\0'}
	};// Mensaje del rendimiento (1/intento).
	int i = 0;			// Intentos.
	*/
	
	
	srand(rockTemp -> Current);	// Semilla para el "número pseudo-random".
	
	printf(
		"\n\n\nMasa [kg] del cohete [ %d ]:    ", numRocket);
	scanf("%d", &(rockTemp -> Mass));
	
	// Máximo 3 intentos:
	for(i = 0; i < 3; i++){
		// rand() % (ValorMáximo-ValorMínimo+1) + (ValorMínimo);
		// rand() devuelve valores entre 0 y una constante grande. Con % se puede sacar el "resto"
		// del resultado, obteniendo efectivamente el rango deseado.
		rockTemp -> RandForce[i] = rand() % 1001 + 500;	// 500 <= F <= 1500.
		rockTemp -> RandAngle[i] = rand() % 61 + 30;	// 30 <= ángulo <= 90.
		
		// Como math.h calcula en radianes, se transforman a [DEG]:
		rockTemp -> CosAngleDeg = (float) cos(rockTemp -> RandForce[i]) * 90 / M_PI;
		rockTemp -> SinAngleDeg = (float) sin(rockTemp -> RandForce[i]) * 90 / M_PI;
		
		// Cálculo de velocidad y altura:
		// ### REVISAR FÓRMULAS ###
		rockTemp -> Velocity[i] = (rockTemp -> CosAngleDeg) * (float) (rockTemp -> RandForce[i]) / (float) (rockTemp -> Mass);
		rockTemp -> Height[i] = (rockTemp -> CosAngleDeg) * (float) (rockTemp -> RandForce[i]) / (float) (rockTemp -> Mass);
		
		// Cálculo de Ep y Ec:
		rockTemp -> eC[i] = 0.5 * (float) (rockTemp -> Mass) * (float) (rockTemp -> Velocity[i]) * (float) (rockTemp -> Velocity[i]);
		rockTemp -> eP[i] = (float) (rockTemp -> Mass) * grav * (float) (rockTemp -> Height[i]);
		
		// Cálculo Rendimiento (eC/eM) [%]:
		rendTemp = flaw + 100 * rockTemp -> eC[i] / (rockTemp -> eC[i] + rockTemp -> eP[i]);
		
		// Clasificación Rendimiento:
		if(80 < rendTemp){						// 80% eM < eC <= 100% eM
			strcpy(rockTemp -> PerfMes[i], "Excelente");
			/*
			switch(i){
				case 1:
					strcpy(rendMes[1], "Excelente");
					break;
				case 2:
					strcpy(rendMes[2], "Excelente");
					break;
				case 3:
					strcpy(rendMes[3], "Excelente");
					break;
			}
			*/
		}
		if(50 < rendTemp && rendTemp <= 80){	// 50% eM < eC <= 80% eM
			strcpy(rockTemp -> PerfMes[i], "Bueno");
			/*
			switch(i){
				case 1:
					strcpy(rendMes[1], "Bueno");
					break;
				case 2:
					strcpy(rendMes[2], "Bueno");
					break;
				case 3:
					strcpy(rendMes[3], "Bueno");
					break;
			}
			*/
		}
		if(20 < rendTemp && rendTemp <= 50){	// 20% eM < eC <= 50% eM
			strcpy(rockTemp -> PerfMes[i], "Regular");
			/*
			switch(i){
				case 1:
					strcpy(rendMes[1], "Regular");
					break;
				case 2:
					strcpy(rendMes[2], "Regular");
					break;
				case 3:
					strcpy(rendMes[3], "Regular");
					break;
			}
			*/
		}
		if(rendTemp <= 20){						// 0 < eC <= 20% eM
			strcpy(rockTemp -> PerfMes[i], "Deficiente");
			/*
			switch(i){
				case 1:
					strcpy(rendMes[1], "Deficiente");
					break;
				case 2:
					strcpy(rendMes[2], "Deficiente");
					break;
				case 3:
					strcpy(rendMes[3], "Deficiente");
					break;
			}
			*/
		}
		
		rockTemp -> Attempt = i + 1;
		
		// Si alcanzó los valores mínimos, para de hacer intentos:
		if(rockTemp -> Velocity[i] >= minVel && rockTemp -> Height[i] >= minH){
			rockTemp -> Success = 1;	// Intento exitoso (mínimo 1 exitoso).
			// Incrementar número de cohetes exitosos:
			(*rocketSucc)++;
			break;
		}
		
		// Si no llegó a la altura mínima, aplicar penalización del 5% al rendimiento:
		if(rockTemp -> Height[i] < minH){
			flaw += 5;
		}
		
		// Si no llegó a los 3 intentos, es FALLIDO:
		rockTemp -> Success = 0;	// Intento fallido (3 lanzamientos fallidos).
	}
	
	// Mostrar datos por cohete, al finalizar los 3 intentos:
	showData(*rockTemp);
}


// Mostrar datos por cohete:
void showData(struct Rocket rockData){
/*
	Mostrar:
		* N° intentos.
		* Ángulo de lanzamiento.
		* Fuerza.
		* Velocidad calculada.
		* Altura calculada.
		* Ec.
		* Ep.
		* Rendimiento del cohete.
*/
	printf(
	"\n\n### DATOS DEL COHETE N°          [ %d ] ###\n", rockData.Current);
	
	printf(
	"\nN° de Intentos:              [ %d ]\n", rockData.Attempt + 1);
	
	// Datos/intento:
	for(int i = 0; i < (rockData.Attempt); i++){
		printf(
	"\nIntento:						[ %d ]\n", rockData.Attempt + 1);
		printf(
	"\nÁngulo de lanzamiento %d:     [ %d ]", rockData.Attempt + 1, rockData.RandAngle[i]);
		printf(
	"\nFuerza de empuje %d:          [ %d ]", rockData.Attempt + 1, rockData.RandForce[i]);
		printf(                                                            
	"\nVelocidad inicial %d:         [ %d ]", rockData.Attempt + 1, rockData.Velocity[i]);
		printf(                                                            
	"\nAltura inicial %d:            [ %d ]", rockData.Attempt + 1, rockData.Height[i]);
		printf(
	"\nEnergía Cinética %d:          [ %.2f ]", rockData.Attempt + 1, rockData.eC[i]);
		printf(                                                              
	"\nEnergía Potencial %d:         [ %.2f ]", rockData.Attempt + 1, rockData.eP[i]);
		printf(                                                              
	"\nRendimiento %d:               [ %s ]\n", rockData.Attempt + 1, rockData.PerfMes[i]);	
	}
	
	printf(
	"\n¿Lanzamiento de cohete exitoso?     ");
	switch(rockData.Success){
		case 1:
			printf("[ SÍ ]");
			break;
		case 0:
			printf("[ NO ]");
			break;
	}
}


// Mostrar datos finales:
void showResults(int numRockets, int rocketSucc){
/*
	Mostrar:
		* Porcentaje de éxito de cuantos cohetes llegaron a órbita segura.
*/
	// 100 * rocketSucc / numRockets
	printf(
	"\n\n El porcentaje de éxito de cohetes lanzados que alcanzaron \n"
	"órbita segura fue de:                 ");
	printf("[ %.2d ]", 100 * rocketSucc / numRockets);
}


